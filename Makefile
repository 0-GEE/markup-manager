CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = tag.o controller.o main.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = markup

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
