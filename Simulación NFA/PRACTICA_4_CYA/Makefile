CXX=g++
CXXFLAGS= -g

OBJS = NFA.o estado.o main.o

all: ${OBJS}
	$(CXX) $(CXXFLAGS) -o nfa ${OBJS}

clean: 
	rm *.*~ *~ *.o nfa