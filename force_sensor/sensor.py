from signal import signal, SIGINT
from serial import Serial
from sys import exit

fd = open("force_sensor/output.txt", 'w+')


def handler(signal_received, frame):
    # Handle any cleanup here
    print('\nSIGINT or CTRL-C detected. Exiting gracefully')
    fd.truncate(0)
    fd.close()
    exit(0)


if __name__ == '__main__':
    signal(SIGINT, handler)     # Handle SIGNINT signal

    ser = Serial('/dev/ttyACM0', 9600)

    while 1:
        line = ser.readline()
        line += "\n"
        fd.write(line)
