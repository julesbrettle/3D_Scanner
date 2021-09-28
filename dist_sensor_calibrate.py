import serial
# from mpl_toolkits import mplot3d
import numpy as np
# import matplotlib.pyplot as plt

arduinoComPort = "COM5"
# Set the baud rate
baudRate = 9600
# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)



numPoints = int(input("Enter number of datapoints: "))
dsDataZeros = [[0]*2] * numPoints
dsData = np.array(dsDataZeros)


i = 0
while i < numPoints:
    dist = input("Enter distance: ")

    # ask for a line of data from the serial port, the ".decode()" converts the
    # data from an "array of bytes", to a string
    lineOfData = serialPort.readline().decode()

    # check if data was received
    if len(lineOfData) > 3:
        # print(lineOfData)
        # print(len(lineOfData))
        panPos, tiltPos, rotPos, senseVal = (int(x) for x in lineOfData.split(','))
        dsData[i,0] = dist
        dsData[i,1] = senseVal
        print(dsData[i,:])
        i=i+1
    else:
        print("senseVal recording failed. Please reenter distance.")

print(dsData)
np.save("calibration_data", dsData)


