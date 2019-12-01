import serial,time
import binascii

ser = serial.Serial(
    port='COM4',
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    xonxoff=False
)

if ser.isOpen():
    while True:
    # reading        
             max_packet = 60
             lines = 0
             byteData = ser.read_until('\r', max_packet)
             if byteData:
                 newdata=str(byteData)
                 print (newdata.strip())
                 if newdata == "Choose Rcal for measurement..1,2 or 3. //Debugging":
                    ser.write('1'.encode(utf-8))
                 ser.flushInput()
                 ser.flushOutput()
             else: 
                print("no data")


else:
    print ("cannot open serial port ")
    try: 
        ser.open()
    except Exception as e:
        print ("error open serial port: " + str(e))
        exit()