import serial
import threading
import time
from time import sleep
import binascii

serial_port = serial.Serial()

GAP_DeviceInit  = \
                "\x01\x00\xfe\x26\x08\x03\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"

def getTimestamp():
    date_now = time.strftime('%d/%m/%y ')
    time_now = time.strftime('%H:%M:%S ')
    return date_now+time_now

def read():
    while True:
        try:
            data = serial_port.readline(serial_port.in_waiting)
            if data == b'':
                sleep(1) # be sure we don't try too often to request data
                continue
            if (len(data) > 1 and len(data) < 66):
                timestamp = getTimestamp() + '... '
                #print(len(data))
                data = timestamp + (data.decode())
                file1 = open("log.txt","a")
                file1.write(data)
                file1.close()
                print(data)
                #sleep(0.4)
                #print ('Got:', data)
            elif (len(data) > 1 and len(data) > 66):
                #timestamp = getTimestamp() + '... '
                #data = timestamp + (data.decode())
                data = data.decode()
                file2 = open("data.txt","a")
                file2.write(data)
                file2.close()
                #print(len(data))
                serial_port.flushInput()
            data = 0
            #sleep(0.2)
        except KeyboardInterrupt:
            break

def main():	
    serial_port.baudrate = 115200
    serial_port.port = 'COM4'
    serial_port.timeout = 0
    if serial_port.isOpen(): serial_port.close()
    serial_port.open()
    t1 = threading.Thread(target=read, args=())
    t1.start()
    while True:
        try:
            command = input('Enter a command to send to the Keyfob: \n\t')
            if (command == "1" or command == "2" or command == "3" or command == "y" or command == "n"):
                serial_port.write(command.encode())
        except KeyboardInterrupt:
            break
    serial_port.close()	

while True:
	main()