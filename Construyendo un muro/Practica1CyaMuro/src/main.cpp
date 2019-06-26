/*
  Kathrina Arrocha Umpiérrez
  Programa principal:
*/

#include <iostream>
#include <chrono>
#include "pared.hpp"
#include "bloque.hpp"
#include "fila.hpp"

using namespace std;
using namespace std::chrono;

// Función de backtracking.
void backtracking(Pared muro, vector<Bloque> &ladrillos, Bloque &ladrillo, vector<Pared> &sol_encontradas, unsigned int filaActual){
  //cout << "Intentado introducir bloque de tamaño: " << ladrillo.getAnchura() << endl;

  // Comprobamos si no supera la longitud.
  if(muro.introducirBloque(filaActual, ladrillo)){
    //cout << "se puede introducir el bloque" << endl;
    if(filaActual > 0){
      //cout << "la fila actual es: " << filaActual << endl;
      //cout << "la longitud de la fila actual es: " << muro.getFila(filaActual).getLongActual() << endl;

      // Aux será una fila del muro que pasamos y aux2 la otra fila.
      Fila aux(muro.getFila(filaActual)), aux2(muro.getFila(filaActual-1));
      aux.insertarBloque(ladrillo); //inserta el bloque y sumo la anchura

      if( muro.checkFilas(aux, aux2) ){ // Si no coinciden las dos filas

        muro.insertarEnMuro(filaActual,ladrillo);
        if(muro.esSolucion()){ // Si llega a solución pues introduzco la solución en sol_encontradas
          sol_encontradas.push_back(muro);
        }else{ // Si acabé con la longitud de esa fila pues paso a la siguiente fila
          if(aux.finalAlcanzado())
            filaActual++;

          for(unsigned int i=0; i < ladrillos.size(); i++)
            backtracking(muro, ladrillos, ladrillos[i], sol_encontradas, filaActual);
        }
      }else{ // Si las filas coinciden pues me salgo
        //cout << "salgo" << endl;
        return;
      }

    }else{ // Si todavía no hay filas
      //cout << "Introducimos bloque en la primera fila" << endl;
      muro.insertarEnMuro(filaActual,ladrillo);

      //cout << "la longitud de la primera fila es: " << muro.getFila(filaActual).getLongActual() << endl;

      if(muro.getFila(filaActual).finalAlcanzado()){ //Si ya he llegado a la longitud de la fila pues paso a la sig.
        filaActual++;
        //cout << filaActual << endl;
      }

      for(unsigned int i=0; i < ladrillos.size(); i++)  //Llama 2 veces al backtracking
        backtracking(muro, ladrillos, ladrillos[i], sol_encontradas, filaActual);


    }
  }else{
    //cout << "salgo" << endl;
    return;
  }

}

// Función muro, para calcular todas las posibles soluciones de un muro de NxL dimensiones.
void M(unsigned int long_filas, unsigned int altura_muro, vector<Bloque> &tiposLadrillos, vector<Pared> &sol_encontradas){

  // Creamos el muro inicial, que solo contiene las dimensiones de sus filas. Y está vacío.
  Pared muro_inicial(altura_muro, long_filas);

  // Calculamos las posibles soluciones poniendo como primer bloque el tipoLadrillo[i].
  for(unsigned int i=0; i < tiposLadrillos.size(); i++)
    backtracking(muro_inicial, tiposLadrillos, tiposLadrillos[i], sol_encontradas, 0); // 0 Fila actual
}



int main(int argc, char const *argv[]) {

  cout << endl<<endl<< "     BIENVENIDO SEAS  " <<endl <<endl <<endl;
  unsigned int altura, longitud;
  vector<Pared> soluciones_totales;
  vector<Bloque> bricks;
  bricks.push_back(Bloque(2));
  bricks.push_back(Bloque(3));

  high_resolution_clock::time_point t1,t2;

  if(argc < 2) {

    cerr << "Introduzca dimensiones de la pared.\n" ;
    cerr << "Uso: muro [Longitud] [Altura]" ;
    exit(1);
  }

  longitud = atoi(argv[1]);
  altura = atoi(argv[2]);

  t1 = high_resolution_clock::now();
  M(longitud, altura, bricks, soluciones_totales);
  t2 = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << endl << "Las posibles soluciones para el muro son: " << soluciones_totales.size() << endl;
  cout << "El tiempo de ejecución es de: " << duration << " microsegundos" << endl;

  cout << endl << "Las soluciones del problema son: " << endl<<endl;
  for(auto i=0; i < soluciones_totales.size(); i++){
    soluciones_totales[i].mostrarMuro();
    cout << endl << endl;
  }

  return 0;
}
