#!/usr/bin/python

import sys
import serial
from xmodem import XMODEM
from time import sleep


def getc(size, timeout=1):
    return port.read(size);

def putc(data, timeout=1):
    #print "Type {} Length: {}".format(type(data).__name__, len(data));
    #print format(hex(ord(data)));
    port.write(data);
    sleep(0.001);


if len(sys.argv) != 3:
    print "Usage: XModem.py /path/to/file /dev/tty.usbserial-A7005FYx";
else:
    port = serial.Serial(port=sys.argv[2], parity=serial.PARITY_NONE, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, timeout=0, xonxoff=0, rtscts=0, dsrdtr=0, baudrate=115200)

    #for x in range(0, 300):
    #    port.write("a");
    #    sleep(0.1);

    modem = XMODEM(getc, putc);
    stream = open(sys.argv[1], 'rb');

    if modem.send(stream):
        print "RPI Successfully flashed";
    else:
        print "Error flashing RPI";
