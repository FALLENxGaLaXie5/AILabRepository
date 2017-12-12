import serial
import time
ser = serial.Serial('/dev/cu.usbserial-DM00L6FP', 9600)


ser.write('5')


#testing reading command
"""
while True:
	print (ser.readline())
	#time.sleep(1)
"""