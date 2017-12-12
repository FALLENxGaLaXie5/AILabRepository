import time
import random
#Joshua Steward
#11/21/2017

import serial


#need a previous orientation variable, 1-4

validCommands = {"forward": b'f', "backward": b'b'}

commandForward = b'f'
commandTurn = b't'


# gridworld = GridMDP( [[0.0, 0.0, 0.0, 0.0, 0.0],
#                      [0.0, 0.0, 0.0, 0.0, 0.0],
#                      [0.0, 0.0, 0.0, 0.0, 0.0],
#                      [0.0, 0.0, 0.0, 0.0, 0.0]], terminals=[((4, 3),1,(1,0)), ((4, 2),-1,(1,0))] )

waiting = True


ser = serial.Serial('/dev/cu.usbmodem1421', 9600)
# serialcmd = '5'
# serialcmd2 = '6'
#
#
one = 1
#
ser.write(commandForward)
#
while True:
    if one == 1:
        ser.write(commandTurn)
        one = 2
    elif one == 2:
        ser.write(commandForward)
        one = 1

    time.sleep(0.5)