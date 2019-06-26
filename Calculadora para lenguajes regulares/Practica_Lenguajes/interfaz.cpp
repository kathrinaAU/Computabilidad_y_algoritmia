/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Clase interfaz.*/
 
#include "interfaz.hpp"
using namespace std;


// CONSTRUCTOR
INTERFAZ::INTERFAZ(){
    
}


// DESTRUCTOR
INTERFAZ::~INTERFAZ(){
    
}


// Menú de inicio:

int INTERFAZ::principal(){
	
	int opcion;
	
	cout << endl;
	cout << " ************************************************************************************** " << endl;
	cout << " ----------------------------  CALCULADORA DE LENGUAJES  ------------------------------   " << endl;
	cout << " ************************************************************************************** "<< endl << endl << endl;	
	cout << "La calculadora es capaz de realizar las siguientes operaciones: " <<endl<<endl;
	cout << "  1. Potencia.  " << endl;
	cout << "  2. Inversa. " << endl;
	cout << "  3. Concatenacion. " << endl;
	cout << "  4. Union. " << endl;
	cout << "  5. Intersección." << endl;
    cout << "  6. Diferencia. " << endl;
    cout << "  7. Sublenguajes. " << endl;
    cout << "  8. Igualdad de lenguajes. " << endl;
    cout << "  9. Cierre de Kleene. " << endl;
	cout << " 10. Salir. " << endl << endl << endl;
	
	cout << "Introduzca una de las opciones anteriores: ";
	cin >> opcion;
	return opcion;
}


void INTERFAZ::presionar_intro(void){
	
	cout << endl << endl;
	cout << "Presiona la tecla intro para continuar"; 
    cin.ignore().get();
}

