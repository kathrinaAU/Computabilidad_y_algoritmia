# Variables.
BIN = bin
SOURCE = src
INC = include

#Nombre del fichero ejecutable.
TARGET = muro

# Flags para el compilador.
CXXFLAGS = -std=c++11 -I$(INC)

# Definición del compilador.
CXX = g++ -Ofast

# Definición de ficheros fuente.
SRC = $(SOURCE)/main.cpp $(SOURCE)/bloque.cpp $(SOURCE)/fila.cpp $(SOURCE)/pared.cpp

# Orden que se ejecutará por defecto.
all: clean $(TARGET)

# Regla de ejecución.
$(TARGET):
	@echo "Generando ejecutable."
	@$(CXX) -o $(BIN)/$@ $(CXXFLAGS) $(SRC)

# Regla para limpiar el archivo.
.PHONY:clean
	clean:
	@echo "Eliminando ejecuatble."
	@rm -f $(BIN)/$(TARGET)
