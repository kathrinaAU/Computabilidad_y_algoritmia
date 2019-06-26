#include <cstdio>
#include <iostream>
#include <stdlib.h>
//#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"

#include "Producciones.hpp"
#include "GR.hpp"

 
using namespace std;



void animacion_inicio(void){

	system("clear");

	int contador=1;
	
	do{	
	
		cout <<endl<<endl;
		cout<<FCYN("			AUTÓMATA FINITO DETERMINISTA (DFA):");
		cout<<endl;
		sleep(2);
		system("clear");
		
	
		cout <<endl<<endl;
		cout<<FGRN("					CARGANDO.");
		cout<<endl;
		sleep(1);
		system("clear");
		
	
		cout <<endl<<endl;
		cout<<FGRN("					CARGANDO..");
		cout<<endl;
		sleep(1);
		system("clear");
		
		cout <<endl<<endl;
		cout<<FGRN("					CARGANDO...");
		cout<<endl;
    	sleep(1);
		system("clear");
		
		
		contador++;
	
	}while(contador<=1);
}

int main(void){

	//animacion_inicio();
	cout << endl <<endl;
	
    int opcion = 0; //Variable para controlar opciones del menu 
    char Nombre_Fichero[100]; // variable para el fichero que nos pasan
	char cadena[100];
	char Nombre_Fichero_grammar[100];
	
	cout <<endl;
	cout << "	¡Bienvenido!"<< endl;
	cout << "	Por favor, introduzca el nombre del fichero"; 
	cout << FGRN(" .grammar");
	cout << " que desea cargar: " <<endl;
	cin >> Nombre_Fichero;
	Gramatica grammar1(Nombre_Fichero);
	//DFA Aux(Nombre_Fichero);
	bool primero=false;
	//DFA resultado;
   	Gramatica grammar;
  
   		
   		do{
   			cout <<endl <<endl;
   			cout<< BOLD("        *********************** OPCIONES ************************") <<endl;
   			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*----->	1. Simplificar gramatica -----------*" <<endl;
			cout << "\t" << "*----->	2. Simplificar gramática, eliminando producciones vacias. ---------*"<<endl;
			cout << "\t" << "*----->	3. Simplificar gramáticas, eliminando producciones unitarias ----------*"<<endl;
			cout << "\t" << "*----->	4. Exportar fichero. ----------------------------*"<<endl;
			cout << "\t" << "*----->	5. Salir  ----------------------------*"<<endl;
			cout << BOLD ( "*-----> Introduce la opción deseada: ---------------*") <<endl;
			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*********************************************************" <<endl <<endl;;
			cin >> opcion;
			
			
			switch (opcion){
				
				
				case 1:
					cout << endl;
					grammar1.eliminarVacios();
					grammar1.encontrandoParejas();
					grammar1.exportar();
					
		        	
		        	break;
		      
		      
				case 2:

					grammar1.eliminarVacios();
					grammar1.exportar();
						cout << endl;
										
				break;
				
				
				case 3:
					grammar1.encontrandoParejas();
					grammar1.exportar();
						cout << endl;
					
				break;
					
					
				case 4:
					
						cout << endl;
						cout << endl;
						grammar1.exportar();

				break;
				
				case 5:
						cout <<endl << "Saliendo..."<<endl;;
					
				break;
				
				
				
				default:
					cout <<endl << FRED("------> ERROR <------")<< " Opción incorrecta, saliendo del programa." << endl;
					opcion = 5;
				break;
					
			}
			
		}while(opcion!=10);
	
}
	   		
   		
   		
   	
				
