// Métodos de la clase Pared.

#include "pared.hpp"

// Constructor por defecto.
Pared::Pared()
  :estructura_correcta(true){
}

// Constructor de copia.
Pared::Pared(vector<Fila> &v_filas)
  :filas(v_filas), estructura_correcta(true) {
}

// Constructor con argumentos
Pared::Pared(unsigned int alt)
  :altura(alt), estructura_correcta(true){
}

Pared::Pared(unsigned int alt, unsigned int longFila)
  :altura(alt), filas(alt){
    for(unsigned int i = 0; i < filas.size(); i++)
      filas[i].setLongitudMaxima(longFila);
}

Pared::Pared(const Pared &p)
  :filas(p.filas){

}

// Método para consultar la altura.
const unsigned int Pared::getAltura(){
  return altura;
}

bool Pared::esSolucion(){
  return filas[filas.size()-1].finalAlcanzado() ;
}

const bool Pared::estadoActual(){
  return estructura_correcta;
}

bool Pared::checkFilas(Fila &fila_actual, Fila &fila_anterior){
  bool correcto = false;
  if(fila_actual.getLongActual() != fila_actual.getLongitud()){
    if(fila_actual.size() > 1 ){
      // Caso para varios bloques.
      if(((fila_actual.getBrick(fila_actual.size() -1) ).getAnchura() + (fila_actual.getBrick(fila_actual.size()-2) ).getAnchura() )
          != (fila_anterior.getBrick(fila_anterior.size()-1).getAnchura() + fila_anterior.getBrick(fila_anterior.size()-2).getAnchura() ) ){
            correcto = true;
          }
    }else{
      if(fila_actual.getBrick(0).getAnchura() != fila_anterior.getBrick(0).getAnchura() )
        correcto = true;
    }
  }else{
    correcto = true;
  }
  return correcto;
}

bool Pared::introducirBloque(unsigned int fila, Bloque &brick){
  bool correcto = false;
  if (filas[fila].getLongActual()+brick.getAnchura()  <= filas[fila].getLongitud() ){
      correcto = true;
  }

  return correcto;
}

Fila Pared::getFila( const unsigned int posFila){
  return filas[posFila];
}

void Pared::insertarEnMuro(unsigned int fila, Bloque &brick){
  filas[fila].insertarBloque(brick);
}

void Pared::mostrarMuro(){
  for(int i= (filas.size()-1) ; i >= 0 ; i--){
    cout << "|" ;

    for(int j=0; j < filas[i].size() ; j++ ){

        for(int k=0; k < filas[i].getBrick(j).getAnchura(); k++ ){
          cout << "X";
        }
        cout << "|";
    }
    cout << endl;
  }
}
