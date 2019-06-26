
#include "monedas.hpp"

monedas::monedas()
:contador(monedero.size(),0){
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

bool monedas::comprobar_devolucion(int pos, int a_devolver, int suma){
    suma += monedero[pos]; //Suma es igual a la cantidad del monedero en pos
    bool puede_devolver = false;
    
    if(suma <= a_devolver) // Si todavia sigue siendo menor el valor pues puede devolver
        puede_devolver=true;
        
    return puede_devolver;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

bool monedas::devolver_cambio(float cantidad){
    int a_devolver = cantidad*100; //Pasamos todo a centimos
    int suma = 0;
    bool final = true;
    
    for(int i=0; i < monedero.size(); i++){ //Recorremos nuestro vector monedero
        while(suma < a_devolver){ // La suma que llevo es menor que la cantidad que me exigen
            if(comprobar_devolucion(i, a_devolver, suma)){ //Si todavía no tengo la cantidad que me exigen
                suma += monedero[i]; //Sumo dicha cantidad y la guardo en suma
                S.push_back(monedero[i]); //Inserto en la lista el dinero que he usado
                contador[i]++; //Incremento el contador en esa posicion del vector
            }else{
                break;
            }
            cout << "Suma: " << suma;
            cout << "   A devolver" << a_devolver <<endl;
        }
    }
    
    if(suma != a_devolver)
        final=false;
    
    return final;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    


bool monedas::devolver_cambio_mejorado(float cantidad){
    int a_devolver = cantidad*100;  //Pasamos todo a centimos
    int suma = 0;
    int aux = a_devolver;
    bool final = true;
    
    for(int i=0; i < monedero.size(); i++){ //Recorremos el vector monedero
        int div = aux/monedero[i]; //Monedas/valor del monedero
            contador[i]=div;
            aux = aux%monedero[i];
    }
    if (aux!=0)
        final=false;
    
    return final;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

void monedas::mostrar_resultados(){
    
    int billetes = 0;
    int moneditas = 0;
    for(auto it=S.begin(); it != S.end(); it++){
        cout << *it << ' ';
    }
    cout << endl <<endl << "*********************************************************";
    cout << endl << "SOLUCION:" <<endl;
     cout << "*********************************************************" <<endl;
    for(int i=0; i < contador.size() ; i++){
       
        if(contador[i] != 0){
            if(monedero[i] >= 100){
                cout <<endl<< contador[i] << "x" << monedero[i]/100 << "€ ";
                billetes += contador[i];
            }else{
                cout <<endl <<contador[i] << "x" << monedero[i] << "cent ";
                moneditas+=contador[i];
            }
        }
    }
    cout <<endl <<endl<< "Se han empleado un total de " <<billetes+moneditas << " monedas/billetes, de los cuales, hay " << billetes << " billetes y " << moneditas << " monedas." <<endl;
}
