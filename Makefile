CC = gcc
CFLAGS =  -Wall -g -MMD
LDLIBS = -l SDL2
EXEC = main
OBJECTS = ${EXEC}.o graph.o draw.o
DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
