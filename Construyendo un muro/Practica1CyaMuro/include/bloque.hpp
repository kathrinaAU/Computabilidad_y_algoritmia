/*
 Clase bloque.
 Kathrina Arrocha Umpiérrez
*/
#include <iostream>
#ifndef BLOQUE_HPP
#define BLOQUE_HPP

class Bloque{
private:
  // Atributos de la clase.
  unsigned int ancho;
public:
  // Constructores.
  Bloque();
  Bloque(int ancho_);
  //~Bloque();

  const unsigned int getAnchura();


};

#endif
