CC = gcc
CFLAGS =  -Wall -g -MMD
LDLIBS = -lm -l SDL2
EXEC = main
OBJECTS = ${EXEC}.o graph.o draw.o cursor.o
DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
