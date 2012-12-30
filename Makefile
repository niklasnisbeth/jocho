# Makefile for Synth1
# Niklas Nisbeth, 2012

COMPILER = gcc
CCFLAGS = -W -Wall -Werror -pedantic-errors -std=c90 
synth1: main.c osc.o env.o synth.o
	${COMPILER} ${CCFLAGS} main.c osc.o env.o synth.o

synth.o: synth.c
	${COMPILER} ${CCFLAGS} synth.c

env.o: env.c
	${COMPILER} ${CCFLAGS} env.c

osc.o: osc.c
	${COMPILER} ${CCFLAGS} osc.c synth.c
