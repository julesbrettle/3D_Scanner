# Code for creating the calibration_data.npy or calibration_data_1.npy files used by 3d_scanner_jupyter.ipynb
# to calibrate the distance sensor. Program asks for measured distance, finds the median of the next 5 senseVal
# 

import serial
# from mpl_toolkits import mplot3d
import numpy as np
# import matplotlib.pyplot as plt
import statistics

# Set to same port as Arduino
arduinoComPort = "COM5"
# Set the baud rate
baudRate = 9600
# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# create blank array for distances and senseVals to be stored in
numPoints = int(input("Enter number of datapoints: "))
dsDataZeros = [[0.0]*2] * numPoints
dsData = np.array(dsDataZeros)

# create a blank array for senseVals to be stored in before they are averaged
aveData = [0.0]*5


i = 0
while i < numPoints:
    print(i)
    dist = float(input("Enter distance (in): "))
    dist = dist*2.54 # convert from inches to cm
    # sensor datasheet is in cm, but we only had a inches tape measure availible

    # clear the serial port so that we get only the newest whole line
    serialPort.flushInput() 
    lineOfData = serialPort.readline().decode() # throw out this lineOfData immediately because it might be partially flushed
    lineOfData = serialPort.readline().decode() # get the real lineOfData to be recorded in the averaging array
    
    j=0
    while j < len(aveData): # fill the averaging array
        if len(lineOfData) > 3: # check that this isn't a single charactor line indicating that the 3D scan is done (we don't care rn, we just want the current senseVal)
            lineOfData = serialPort.readline().decode() # ask for a line of data from the serial port, the ".decode()" converts the data from an "array of bytes", to a string
            panPos, tiltPos, senseVal = (int(x) for x in lineOfData.split(','))
            print(senseVal)
            aveData[j] = float(senseVal)
            j=j+1
        else: # if it isn't a whole line, get the next line and try again
            lineOfData = serialPort.readline().decode()
    
    dsData[i,0] = dist # add the input measured distance to the final data array
    dsData[i,1] = float(statistics.median(aveData)) # find the median of the averaging array and put in the final data array
    print(dsData[i,:])

    i=i+1

print(dsData)
np.save("calibration_data", dsData) # modify this string to change where the array gets saved


