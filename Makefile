# Makefile for Synth1
# Niklas Nisbeth, 2012

COMPILER = gcc
CCFLAGS = -W -Wall -Werror -pedantic-errors -std=c99 
OBJECTS = main.o osc.o env.o synth.o
LIBS = -lm
synth1: ${OBJECTS}
	${COMPILER} ${CCFLAGS} ${OBJECTS} ${LIBS} -o synth

%.o: %.c
	${COMPILER} ${CCFLAGS} ${LIBS} -c $<

clean:
	rm *.o synth
