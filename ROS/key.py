import keyboard
import socket
import time


def sendMsg(ip, msg):
	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect((ip, 8008))
	client.send(msg)



while True:
	if keyboard.is_pressed('a'):
		data = 'a'
		print("a is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('s'):
		data = 's'
		print("s is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('d'):
		data = 'd'
		print("d is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('w'):
		data = 'w'
		print("w is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('q'):
		data = 'q'
		print("q is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('e'):
		data = 'e'
		print("e is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('r'):
		data = 'r'
		print("r is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('j'):
		data = 'j'
		print("j is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('k'):
		data = 'k'
		print("k is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('l'):
		data = 'l'
		print("l is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('i'):
		data = 'i'
		print("i is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('u'):
		data = 'u'
		print("u is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('o'):
		data = 'o'
		print("o is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('v'):
		data = 'v'
		print("v is pressed")
		sendMsg("192.168.100.12",data)
	elif keyboard.is_pressed('b'):
		data = 'b'
		print("b is pressed")
		sendMsg("192.168.100.12",data)
	else:
		data = 'S'
		print("S")
		sendMsg("192.168.100.12",data)
	time.sleep(0.01)
