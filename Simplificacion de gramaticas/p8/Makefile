CXX=g++ -std=c++11
CXXFLAGS= -g

OBJS = GR.o Producciones.o main.o 

all: clean ${OBJS}
	$(CXX) $(CXXFLAGS) -o grammar ${OBJS}

.PHONY:clean
	clean: 
	rm *.*~ *~ *.o grammar
