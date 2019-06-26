CXX=g++ -std=c++11
CXXFLAGS= -g

OBJS = DFA.o GR.o Producciones.o estado.o main.o 

all: ${OBJS}
	$(CXX) $(CXXFLAGS) -o grammar ${OBJS}

clean: 
	rm *.*~ *~ *.o grammar