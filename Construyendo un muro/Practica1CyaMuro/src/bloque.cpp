#include "bloque.hpp"

// Constructor de la clase.
Bloque::Bloque(){
  ancho = 2;
}

// Constructor con parámetros.
Bloque::Bloque(int ancho_){
  ancho = ancho_;
}


const unsigned int Bloque::getAnchura(){
  return ancho;
}

//Bloque::~Bloque(){
  //std::cout << "Hello" << std::endl;
//}
