#!/usr/bin/python3

from picamera import PiCamera
from sys import stdout

RES = (640, 480)
FPS = 30

STREAM = stdout.buffer

with PiCamera(resolution=RES, framerate=FPS) as cam:
    cam.start_recording(STREAM, format='rgb')

    try:
        while True: pass
    except KeyboardInterrupt:
        cam.stop_recording()
        exit(0)

