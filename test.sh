#!/bin/sh

make && ./jocho && sox -r 44100 -b 16 -e unsigned-integer --endian little /tmp/tst.raw tst.wav && mplayer tst.wav
