
def read():
    while True:
        try:
            bIncoming = serial_port.in_waiting
            print(bIncoming)
            data = serial_port.readline(serial_port.in_waiting)
            if data == b'':
                sleep(1) # be sure we don't try too often to request data
                continue
            if (bIncoming > 1 and len(data) < 66):
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