/*
 Clase fila.
 Kathrina Arrocha Umpiérrez
*/

#ifndef FILA_HPP
#define FILA_HPP

#include <vector>
#include "bloque.hpp"
#include <iostream>

using namespace std;

class Fila{
private:
  // Atributos de la clase fila.
  vector<Bloque> fila;
  unsigned int longitud;
  unsigned int long_actual;
public:
  // Constructores de la clase.
  Fila();
  Fila(vector<Bloque> &v_bloques);
  Fila(unsigned int long_fila);
  Fila(const Fila &f);


  const unsigned int getLongitud();
  const unsigned int getLongActual();
  const unsigned int size();
  void setLongitudMaxima(const unsigned int max_longitud);

  const bool finalAlcanzado();

  Bloque getBrick(unsigned int pos) const;
  void insertarBloque( Bloque &brick);

};

#endif
