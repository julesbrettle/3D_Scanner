import serial
# from mpl_toolkits import mplot3d
import numpy as np
# import matplotlib.pyplot as plt
import statistics

arduinoComPort = "COM5"
# Set the baud rate
baudRate = 9600
# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)



numPoints = int(input("Enter number of datapoints: "))
dsDataZeros = [[0.0]*2] * numPoints
dsData = np.array(dsDataZeros)
aveData = [0.0]*5


i = 0
while i < numPoints:
    print(i)
    dist = float(input("Enter distance (in): "))
    dist = dist*2.54

    # ask for a line of data from the serial port, the ".decode()" converts the
    # data from an "array of bytes", to a string

    serialPort.flushInput()
    lineOfData = serialPort.readline().decode()
    j=0
    while j < len(aveData):
        if len(lineOfData) > 3:
            lineOfData = serialPort.readline().decode()
            panPos, tiltPos, senseVal = (int(x) for x in lineOfData.split(','))
            print(senseVal)
            aveData[j] = float(senseVal)
            j=j+1
        else:
            lineOfData = serialPort.readline().decode()
    
    dsData[i,0] = dist
    dsData[i,1] = float(statistics.median(aveData))
    print(dsData[i,:])
    i=i+1

print(dsData)
np.save("calibration_data_test", dsData)


