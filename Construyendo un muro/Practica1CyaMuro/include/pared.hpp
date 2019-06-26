/*
  Clase pared.
Kathrina Arrocha Umpiérrez
*/

#include <iostream>
#ifndef PARED_HPP
#define PARED_HPP

#include "fila.hpp"

class Pared{
private:
  // Atributos de la clase.
  vector<Fila> filas;
  unsigned int altura;
  bool estructura_correcta;

public:
  // Constructor de la clase.
  Pared();
  Pared(vector<Fila> &v_filas);
  Pared(const Pared &p);
  Pared(unsigned int alt);
  Pared(unsigned int alt, unsigned int longFila);

  const unsigned int getAltura();
  bool esSolucion(); // Devuelve si el muro está completo y no tiene errores.
  bool checkFilas( Fila &fila_actual, Fila &fila_anterior);
  const bool estadoActual();

  Fila getFila( const unsigned int posFila);

  // Funciones a implementar:
  bool introducirBloque(unsigned int fila, Bloque &brick);
  void insertarEnMuro(unsigned int fila, Bloque &brick);
  void mostrarMuro();

};

#endif
