CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second -Wshadow
EXEC = $(shell basename $(CURDIR)).out
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

