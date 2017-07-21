CXX = gcc
CXXFLAGS =  -Wall -g #-DTEST
EXEC = main.x
OBJECTS = main.o graph.o display.o
DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -l SDL2

main.o: main.c graph.h
	${CXX} ${CXXFLAGS} -c main.c

graph.o: graph.c graph.h
	${CXX} ${CXXFLAGS} -c graph.c

display.o: display.h display.c
	${CXX} ${CXXFLAGS} -c display.c


clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
