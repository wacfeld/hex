CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second -Wshadow -lSDL2main -lSDL2 -lSDL2_image `sdl2-config --cflags --libs`
EXEC = $(shell basename $(CURDIR)).out
OBJECTS = main.o drawer.o hex.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

