#!/usr/bin/env python

import rospy
from std_msgs.msg import String
import time
import socket

#Set server ip address, port, buffer capacity
HOST='192.168.43.175'
PORT=8008
BUFFER=4096

def talker():
    pub = rospy.Publisher('motor', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
    	soc=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    	soc.connect((HOST,PORT))
    	soc.send('hello ros')
    	buf=soc.recv(BUFFER)
    	print(buf)
	soc.close()
        hello_str = buf
        rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
