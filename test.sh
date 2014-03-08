#!/bin/sh

make && ./jocho && sox -r 44100 -b 32 -e signed-integer --endian little tst.raw tst.wav && mplayer tst.wav
