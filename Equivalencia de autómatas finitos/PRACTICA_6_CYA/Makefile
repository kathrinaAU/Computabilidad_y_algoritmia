CXX=g++
CXXFLAGS= -g

OBJS = DFA.o NFA.o estado.o main.o

all: ${OBJS}
	$(CXX) $(CXXFLAGS) -o compareFA ${OBJS}

clean: 
	rm *.*~ *~ *.o compareFA