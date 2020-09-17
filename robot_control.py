import msvcrt
import serial
ser = serial.Serial('COM6', 38400)
while 1:
    # Poll keyboard
    if msvcrt.kbhit():
        key = msvcrt.getch()
        #key = key.decode('ascii')
        if key == b'w':
            print('w')
            ser.write(b'C21FE')
        elif key == b'a':
            ser.write(b'C21LE')
        elif key == b'd':
            ser.write(b'C21RE')
        elif key == b's':
            ser.write(b'C21BE')
        elif key == b'q':
            ser.write(b'C21SE')
        elif key == b't':
        	ser.write(b'C21SE')
        	message = input();
        	message = 'C' + str(len(message)+1)+'2'+message+'E'
        	print(message)
        	message_bytes = message.encode('utf-8')
        	ser.write(message_bytes)

        else:
        	print(str(chr(key[0])))