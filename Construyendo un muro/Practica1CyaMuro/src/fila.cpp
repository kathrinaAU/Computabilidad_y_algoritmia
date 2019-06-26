// Métodos de la clase fila.
#include "fila.hpp"

// Constructor por defecto.
Fila::Fila(){
  long_actual = 0;
  longitud = 0;
}

// Constructor de copia.
Fila::Fila(vector<Bloque> &v_bloques)
  :fila(v_bloques){
    long_actual = 0;
    longitud = 0;
    cout << "hello" << endl;
}

// Constructor con argumentos.
Fila::Fila(unsigned int long_fila)
  :longitud(long_fila), long_actual(0){
}

Fila::Fila(const Fila & f)
:fila(f.fila), long_actual(f.long_actual), longitud(f.longitud){
}

const bool Fila::finalAlcanzado(){
  return long_actual == longitud;
}

void Fila::setLongitudMaxima(const unsigned int max_longitud){
  longitud = max_longitud;
}

// Método para consultar la longitud.
const unsigned int Fila::getLongitud(){
  return longitud;
}

const unsigned int Fila::getLongActual(){
  return long_actual;
}

const unsigned int Fila::size(){
  return fila.size();
}

Bloque Fila::getBrick(unsigned int pos) const{
  return  fila[pos];
}

void Fila::insertarBloque(Bloque &brick){
  fila.push_back(brick);
  long_actual += brick.getAnchura();
}
