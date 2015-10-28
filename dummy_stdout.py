#!/usr/bin/python3.4

from sys import stdout

STREAM = stdout.buffer

try:
    while True:
        STREAM.write(bytes([0x00, 0xFF]))
except KeyboardInterrupt:
    exit(0)

