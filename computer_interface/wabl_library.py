#!/usr/bin/python3

import sys
import serial
import struct
import os


#ports to try to find WABL on...
ports = ["/dev/ttyUSB0", "COM1", "/dev/ttyUSB1", "COM2", "/dev/ttyUSB2", "COM3", "COM4"]

ser = serial.Serial()
header = b'\x45\xC2\x21'
id_command = b'\x01'
kp_command = b'\x02'
ki_command = b'\x03'
x_command = b'\x04'
x_dot_command = b'\x05'
phi_command = b'\x06'
phi_dot_command = b'\x07'

def wabl_serial_init():
    """Initializes serial interface with WABL. WABL must be powered and the XBEE
       Interface must be plugged into the computer.
    """

    ser.baudrate = 19200 
    ser.timeout = 0.25

    print("Searching for WABL...", end = "", flush = True)

    tries = 0
    while (tries < 40 and (ser.isOpen() == False)):
        print(".", end = "", flush = True)
        for port in ports:
            try:
                ser.port = port
                ser.open()
                id = wabl_get_id()
                if (id == b'WABL'):
                    #return success
                    return 0
            except:
                pass

        tries += 1
    #return falure
    return 1

    print ("WABL opened on port ", ser.port)

def wabl_get_id():
    """Sends command to acquire WABL id. WABL will respond with b'WABL'.
       This allows the computer to identify WABL on a given port.
    """

    ser.write(header)
    ser.write(id_command)
    ser.write(b'\x00\x00\x00\x00')
    id = ser.read(4)
    return id

def wabl_set_motor_kp(new_kp):
    #pack float as byte array
    new_kp_bytes = struct.pack('f', new_kp)

    ser.write(header)
    ser.write(kp_command)
    for byte in new_kp_bytes:
        ser.write(bytes(byte))

def wabl_set_motor_ki(new_ki):
    #pack float as byte array
    new_ki_bytes = struct.pack('f', new_ki)

    ser.write(header)
    ser.write(ki_command)
    for byte in new_ki_bytes:
        ser.write(bytes(byte))

def wabl_set_lqr_x(new_kx):
    #pack float as byte array
    new_kx_bytes = struct.pack('f', new_kx)

    ser.write(header)
    ser.write(x_command)
    for byte in new_kx_bytes:
        ser.write(bytes(byte))

def wabl_set_lqr_x_dot(new_kx_dot):
    #pack float as byte array
    new_kx_dot_bytes = struct.pack('f', new_kx_dot)

    ser.write(header)
    ser.write(x_dot_command)
    for byte in new_kx_dot_bytes:
        ser.write(bytes(byte))

def wabl_set_lqr_phi(new_kphi):
    #pack float as byte array
    new_kphi_bytes = struct.pack('f', new_kphi)

    ser.write(header)
    ser.write(phi_command)
    for byte in new_kphi_bytes:
        ser.write(bytes(byte))

def wabl_set_lqr_phi_dot(new_kphi_dot):
    #pack float as byte array
    new_kphi_dot_bytes = struct.pack('f', new_kphi_dot)

    ser.write(header)
    ser.write(phi_dot_command)
    for byte in new_kphi_dot_bytes:
        ser.write(bytes(byte))

def clear_screen():
    try:
        os.system('cls')
    except:
        pass
    try:
        os.system('clear')
    except:
        pass

def menu_set_lqr():
    correct = False

    while (correct == False):
        new_kx = float(input("New kx: "))
        new_kxdot = float(input("New kx_dot: "))
        new_kphi = float(input("New kphi: "))
        new_kphidot = float(input("New kphi_dot: "))

        correct_response = input("Values correct? (y/n) ")
        if (correct_response != "" and correct_response[0].lower() == "y"):
            correct = True

    wabl_set_lqr_x(new_kx)
    wabl_set_lqr_x_dot(new_kxdot)
    wabl_set_lqr_phi(new_kphi)
    wabl_set_lqr_phi_dot(new_kphidot)


if __name__ == "__main__":
    #test code
    if (wabl_serial_init() == 0):
        print("WABL found on port ", ser.port)

        alive = True
        while (alive):
            clear_screen()

            print("1. Set motor kp\n2. Set motor ki\n3. Set lqr constants\n4. Exit")
            menu_answer = input()
            if (menu_answer == "1"):
                new_kp = float(input("Enter new kp value: "))
                wabl_set_motor_kp(new_kp)

            elif (menu_answer == "2"):
                new_ki = float(input("Enter new ki value: "))
                wabl_set_motor_ki(new_ki)

            elif (menu_answer == "3"):
                menu_set_lqr()
            elif (menu_answer == "4"):
                alive = False
            else:
                print("Invalid option. Please try again.")

            #wabl_set_motor_kp(3.4)
            #wabl_set_motor_ki(3.4)
            #wabl_set_lqr_x(1.2)
            #wabl_set_lqr_x_dot(1.2)
            #wabl_set_lqr_phi(3.2)
            #wabl_set_lqr_phi_dot(-3.7)
    else:
        print ("WABL could not be found on any ports")

