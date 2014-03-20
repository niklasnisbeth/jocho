# Makefile for Jocho
# Niklas Nisbeth, 2012-3

COMPILER = gcc
CCFLAGS = -W -Wall -Werror -pedantic-errors -std=c99 -ggdb
OBJECTS = main.o op.o env.o voice.o algorithms.o wt.o
LIBS = -lm
synth1: ${OBJECTS}
	${COMPILER} ${CCFLAGS} ${OBJECTS} ${LIBS} -o jocho

%.o: %.c
	${COMPILER} ${CCFLAGS} ${LIBS} -c $<

clean:
	rm *.o jocho
