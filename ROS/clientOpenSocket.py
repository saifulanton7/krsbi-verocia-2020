#!/usr/bin/python
 
import time
import socket
#Set server ip address, port, buffer capacity
HOST='192.168.100.12'
PORT=8008
BUFFER=4096
 
while 1:
         # Define socket communication type ipv4, tcp
    soc=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
         #connect to the server 
    soc.connect((HOST,PORT))
         #delay
    time.sleep(1)
         #Send a message 
    soc.send('hello ros')
         # accept message
    buf=soc.recv(BUFFER)
    print(buf)
         #interface is closed
    soc.close()
