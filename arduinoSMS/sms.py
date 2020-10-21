#!/usr/bin/python
import serial
import time
import pandas as pd

comport = input("Enter COM port (EG:COM1/COM5/.. etc.): ")
ard = serial.Serial(comport,9600,timeout=5)
time.sleep(2) # wait for Arduino



while (1):
    filename = input("Enter file name of numbers: ")
    message = input("Enter message to send: ")
    # filename="grade5"
    # message="dgfrga"
    messageNew = "msg:"+message

    ard.write(messageNew.encode())
    time.sleep(20)

    while (1):
        msg = ard.read(ard.inWaiting()) # read all characters in buffer
        print ("Message from arduino: ")
        if (msg):
            print (msg.decode().strip())

        if (msg.decode().strip()=="Message received"):
            try:
                df = pd.read_csv(filename+'.csv', 'r')
            except FileNotFoundError:
                print("Invalid filename")
                break
            else:
                for number in df['tp']:
                    print ('Sending message "'+message+'" to the number: '+str(number))
                    messageNum = "num:"+str(number)
                    ard.write(messageNum.encode())
                    time.sleep(10)

                    print("message sent to the number "+str(number))
        else:
            break



# with open(filename+'.csv', 'r') as file:
#     reader = csv.reader(file)
#     for row in reader:
#         print(row[0])

# while (i < 4):
#     # Serial write section
#
#     setTempCar1 = 63
#     setTempCar2 = 37
#     ard.flush()
#     setTemp1 = str(setTempCar1)
#     setTemp2 = str(setTempCar2)
#     print ("Python value sent: ")
#     print (setTemp1)
#     ard.write(setTemp1.encode())
#     time.sleep(1) # I shortened this to match the new value in your Arduino code
#
#     # Serial read section
#     msg = ard.read(ard.inWaiting()) # read all characters in buffer
#     print ("Message from arduino: ")
#     print (msg.decode("utf-8"))
#     i = i + 1
# else:
#     print ("Exiting")
# exit()
