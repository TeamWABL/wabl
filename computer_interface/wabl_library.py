#!/usr/bin/python3

import sys
import serial


#ports to try.../dev/ttyUSB0, /dev/ttyUSB1, etc... COM1, COM2...
ports = ["/dev/ttyUSB0", "COM1", "/dev/ttyUSB1", "COM2", "/dev/ttyUSB2", "COM3", "COM4"]
if __name__ == "__main__":
    #test code
    ser = serial.Serial()
    ser.baudrate = 19200 
    ser.timeout = 1

    for port in ports:
        try:
            ser.port = port
            ser.open()
            break
        except:
            print (port, endl = '')
            print (" failed...")
            
    print(ser)
