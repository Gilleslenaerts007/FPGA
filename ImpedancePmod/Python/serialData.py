import serial
import threading
import time
from time import sleep
import binascii

serial_port = serial.Serial()

lock = threading.Lock()
GAP_DeviceInit  = \
                "\x01\x00\xfe\x26\x08\x03\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"

def getTimestamp():
    date_now = time.strftime('%d/%m/%y ')
    time_now = time.strftime('%H:%M:%S ')
    return date_now+time_now

def read():
    file2 = open("data.txt","a")
    file1 = open("log.txt","a")
    file1.close()
    file2.close()
    while True:
        string = ''
        try:
            #line = serial_port.readline()
            dataSize = serial_port.in_waiting      
            if (dataSize > 0):
                file2 = open("data.txt","a")
                file1 = open("log.txt","a")
                while True:
                    line = serial_port.readline()
                    #print(line)
                    if( len(line) > 0 and len(line) < 70):
                        line = line.decode()
                        timestamp = getTimestamp() + '... '
                        line = timestamp + (line)
                        file1.write(line)
                        print(line)
                    if(len(line) > 70):
                        line = line.decode()
                        file2.write(line)
                    if (len(line) <= 0):
                        #sleep(2) # be sure we don't try too often to request data
                        #print("exit loop")
                        break
                            
                    sleep(0.2)
                file1.close()
                file2.close()
                serial_port.flush()
                serial_port.flushInput()
        except KeyboardInterrupt:
            break

def main():	
    serial_port.baudrate = 115200
    serial_port.port = 'COM6' #com6 on laptop. COM4 on PC
    serial_port.timeout = 0.05
    if serial_port.isOpen(): serial_port.close()
    serial_port.open()
    serial_port.flushInput()
    serial_port.flush()
    serial_port.flushOutput()
    t1 = threading.Thread(target=read, args=())
    t1.start()
    while True:
        try:
            command = input('Enter a command to MiniZed: \n')
            if (command == "1" or command == "2" or command == "3" or command == "y" or command == "n" or command== "m"):
                serial_port.write(command.encode())
                #sleep(5)
        except KeyboardInterrupt:
            break
        #sleep(10)
    serial_port.close()	

while True:
	main()