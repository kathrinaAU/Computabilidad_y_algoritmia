#include <iostream>
#include "monedas.hpp"

using namespace std;

int main(){
    float cantidad;
    cout << "Introduce la cantidad de dinero a calcular:" <<endl;
    cin >> cantidad;
    bool hay_cambio;
    
    cout << cantidad << endl;
    
    monedas mi_cambio;
    hay_cambio = mi_cambio.devolver_cambio_mejorado(cantidad);
    
    if(!hay_cambio){
        cerr << "ERROR: no hay cambio disponible" << endl;
    }else{
        mi_cambio.mostrar_resultados();
        cout << endl;
    }

}