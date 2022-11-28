#main Python script

import time
import serial
import wmi
import os

os.startfile(os.getcwd()+"\OpenHardwareMonitor.exe")
time.sleep(10)
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1) #open serial port
def write_read(x): #function to send data to the arduino board
    arduino.write(bytes(x,'utf-8'))
    time.sleep(0.45)

while 1:
      w = wmi.WMI(namespace="root\OpenHardwareMonitor") #open Hardware Monitor
      temperature_infos = w.Sensor()
      for sensor in temperature_infos: #Searching for all data to show on screen. 
        if sensor.SensorType==u'Temperature' and sensor.Name==u'CPU Package':
          A = str(round(sensor.Value,2))
        elif sensor.SensorType==u'Load' and sensor.Name==u'CPU Total':
          B = str(round(sensor.Value,2))
        elif sensor.SensorType==u'Power' and sensor.Name==u'CPU Package':
          C = str(round(sensor.Value,2))
        elif sensor.SensorType==u'Temperature' and sensor.Name==u'GPU Core':
          D = str(round(sensor.Value,2))
        elif sensor.SensorType==u'Load' and sensor.Name==u'GPU Core':
          E = str(round(sensor.Value,2))
        elif sensor.SensorType==u'Power' and sensor.Name==u'GPU Power':
          F = str(round(sensor.Value,2))
          
      finalString = A + "," + B + "," + C + "," + D +"," + E + "," + F +"\n" #Create the String to send to arduino
      print(finalString)
      if arduino.isOpen():
        write_read(finalString) #calling the send function