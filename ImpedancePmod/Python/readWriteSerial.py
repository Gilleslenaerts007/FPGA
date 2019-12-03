import serial
import threading
from time import sleep
import binascii

serial_port = serial.Serial()

GAP_DeviceInit  = \
                "\x01\x00\xfe\x26\x08\x03\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
                \x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"

def read():
    while True:
        try:
            data = serial_port.read(9999);
            if len(data) > 0:
                print ('Got:', data)
            sleep(0.5)
			#print ('not blocked')
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
            if (command == "1"):
                serial_port.write(command.encode())
        except KeyboardInterrupt:
            break
    serial_port.close()	

while True:
	main()