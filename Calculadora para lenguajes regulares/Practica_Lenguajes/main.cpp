/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Programa principal.
*/


#include <iostream>
#include <unistd.h>
#include "interfaz.cpp"
#include "op.cpp"
//#include "op_2.cpp"

#include <stdlib.h>



using namespace std;

int main(void) {
    
    int opcion = -1;
    INTERFAZ menu;
 
do{
    opcion = menu.principal();
    
    switch( opcion ){
        
        case 1: {
            OP opera=OP(1);  
            opera.calculo_potencia();  
            menu.presionar_intro();  
            break; 
        }
        
        case 2: {
            OP opera=OP(1);   
            opera.calculo_inversa(); 
            menu.presionar_intro();    
            break; 
        }
        
        case 3: { 
            OP opera_2; 
            opera_2.calculo_concatenacion();   
            menu.presionar_intro();     
            break; 
        }
        
        case 4: { 
            OP opera_2;  
            opera_2.calculo_union();   
            menu.presionar_intro();    
            break; 
        }
        
        case 5: { 
            OP opera_2;   
            opera_2.calculo_interseccion(); 
            menu.presionar_intro();      
            break;
        }
        
        case 6: { 
            OP opera_2; 
            opera_2.calculo_diferencia();   
            menu.presionar_intro(); 
            break;
        }
        
        case 7: { 
            OP opera_2;   
            opera_2.calculo_sublenguaje();  
            menu.presionar_intro();     
            break;
        }
        
        case 8: { 
            OP opera_2;   
            opera_2.calculo_igualdad();     
            menu.presionar_intro();     
            break; 
        }
        
        case 9: { 
            OP opera=OP(1);  
            opera.calculo_cierre_kleene();  
            menu.presionar_intro();     
            break; 
        }
        case 10:   
            break;
        
        default: {
            cout << endl;
            cout << " ******************************************************************************************** " << endl;
            cout << " ----------->>>> No hay ninguna opción que coincida con la que ha seleccionado. <<<<--------- " << endl;
            cout << " ******************************************************************************************** " << endl;
            
        } 
        
    }
   
}while( opcion != 10);
   
	return 0;
}

