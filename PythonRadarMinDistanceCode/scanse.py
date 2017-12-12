import time
from sweeppy import Sweep

with Sweep('/dev/cu.usbserial-DM00L6FP') as sweep:
    sweep.start_scanning()
    angle = 0
    angleAtMinDistance = 0

    minDistanceQuadrant = 0
    minDistance = 50
    minDistanceCopy = minDistance
    distance = 0

    rotationalScan = 4
    currentRotation = 0

	# def resultsOfScan():
	#     currentRotation = 0
	#     minDistance = minDistanceCopy
	#     print "Min Angle : {}, Distance : {}, In Quadrant: {}".format(angleAtMinDistance, minDistance, minDistanceQuadrant)
	#     #print("Min Angle: ")

    for scan in sweep.get_scans():
        #print('{}\n'.format(scan))
        for s in scan.samples:
        	# print "Angle : {}, Distance : {}".format(s.angle/1000,s.distance)
        	angle = s.angle/1000
        	distance = s.distance

        	#check if in quadrant 1

        	if angle >= 0 and angle < 45:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 1
        	elif angle >= 45 and angle < 90:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 2
        	elif angle >= 90 and angle < 135:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 3
        	elif angle >= 135 and angle < 180:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 4
        	elif angle >= 180 and angle < 225:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 5
        	elif angle >= 225 and angle < 270:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 6
        	elif angle >= 270 and angle < 315:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 7
        	elif angle >= 315 and angle < 360:
        		if distance < minDistance:
        			minDistance = distance
        			angleAtMinDistance = angle
        			minDistanceQuadrant = 8
        currentRotation = currentRotation + 1
       	if currentRotation >= rotationalScan:
       		currentRotation = 0
       		#minDistance = minDistanceCopy
       		print ("Min Angle : {}, Distance : {}, In Quadrant: {}".format(angleAtMinDistance, minDistance, minDistanceQuadrant))
       		#resultsOfScan()
       		time.sleep(1)
       		minDistance = minDistanceCopy



    