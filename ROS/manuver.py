#!/usr/bin/python
import rospy
import time
import json
from std_msgs.msg import String
from std_msgs.msg import UInt16



class PubSub(object):
    def __init__(self):
        rospy.init_node('pubsub')
	self.manuver = 0
	self.x = 0
	self.y = 0
	self.px = 0
	self.sudut = 0
	self.data = ''
	self.flag = 0
        self.socket_sub = rospy.Subscriber('tcptopic',String,self.readSocket)
	self.camera_sub = rospy.Subscriber('camera',String,self.readCam)
	self.sensor_sub = rospy.Subscriber('sensor',String,self.readSensor)
        self.motor_pub = rospy.Publisher('motor', UInt16,queue_size=1)
	self.drible_pub = rospy.Publisher('drible', UInt16,queue_size=1)
        
    def readSocket(self, data):
    	self.data = data.data
	if(self.data == "v"): self.flag = 0
	elif(self.data == "b"): self.flag = 1
	if(self.flag == 0):
		if(self.data == "a"): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Kiri")
		elif(self.data == "s"): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Mundur")
		elif(self.data == "d"): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Kanan")
		elif(self.data == "w"): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Maju")
		elif(self.data == "r"): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Rotasi")
		elif(self.data == "S" and self.flag == 0): 
			rospy.loginfo("Status : Mode Game Control")
			rospy.loginfo("Manuver : Diam")

    def readCam(self,data):
    	variabel = data.data
    	variabel_dict = json.loads(variabel)
    	self.x = variabel_dict['x']
    	self.y = variabel_dict['y']
	x = self.x
	y = self.y
	if(self.flag == 1): self.scanBall()
		
    def readSensor(self,data):
    	variabel = data.data
    	variabel_dict = json.loads(variabel)
    	self.cmps = variabel_dict['cmps']
    	self.px = variabel_dict['px']

    def scanBall(self):
	if(self.x == 0 and self.y == 0): 
		self.motor_pub.publish(12);
		rospy.loginfo("Status : Bola Tak Terdeteksi")
		rospy.loginfo("Manuver : Mencari Bola")
		return 0
	else : 
		rospy.loginfo("Status : Bola Terdeteksi")			
		self.getBall()	
		
    def getBall(self):	
	if(self.px == 0):
		self.drible_pub.publish(3);
		if(self.x<=270):
			if(self.y<=110):
				self.motor_pub.publish(1);
	   			rospy.loginfo("Manuver : Belok Kiri Pelan")
			elif(self.y>110 and self.y<430):
				self.motor_pub.publish(2);
	   			rospy.loginfo("Manuver : Belok Kiri Sedang")
			elif(self.y>=420):
				self.motor_pub.publish(3);
	   			rospy.loginfo("Manuver : Belok Kiri Cepat")
		elif(self.x>270 and self.x<=410):
			if(self.y<=110):
				self.motor_pub.publish(4);
	   			rospy.loginfo("Manuver : Maju Cepat")
			elif(self.y>110 and self.y<430):
				self.motor_pub.publish(5);
	   			rospy.loginfo("Manuver : Maju Sedang")
			elif(self.y>=420):
				self.motor_pub.publish(5);
	   			rospy.loginfo("Manuver : Maju Pelan")
		elif(self.x>410):
			if(self.y<=110):
				self.motor_pub.publish(7);
	   			rospy.loginfo("Manuver : Belok Kanan Pelan")
			elif(self.y>110 and self.y<430):
				self.motor_pub.publish(8);
	   			rospy.loginfo("Manuver : Belok Kanan Sedang")
			elif(self.y>=420):
				self.motor_pub.publish(9);
	   			rospy.loginfo("Manuver : Belok Kanan Cepat")
		return 0		
		
	else:
		self.drible_pub.publish(1);
		self.motor_pub.publish(6);
	   	rospy.loginfo("Manuver : Berhenti")
		return 1

if __name__ == '__main__':
	try:	
		a = PubSub()			 
		rospy.spin()

    	except rospy.ROSInterruptException: pass

