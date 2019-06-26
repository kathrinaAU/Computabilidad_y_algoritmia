#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"

#include "DFA.hpp"
 
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

	animacion_inicio();
	cout << endl <<endl;
	
    int opcion = 0; //Variable para controlar opciones del menu 
    char Nombre_Fichero[100]; // variable para el fichero que nos pasan
	char cadena[100];
	
	cout <<endl;
	cout << "	¡Bienvenido!"<< endl;
	cout << "	Por favor, introduzca el nombre del fichero"; 
	cout << FGRN(" .dfa");
	cout << " que desea cargar: " <<endl;
	cin >> Nombre_Fichero;
	DFA Aux(Nombre_Fichero);
	bool primero=false;
	DFA resultado;
   	
  
   		
   		do{
   			cout <<endl <<endl;
   			cout<< BOLD("        *********************** OPCIONES ************************") <<endl;
   			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*----->	1. Cargar otro dfa desde un fichero. -----------*" <<endl;
			cout << "\t" << "*----->	2. Mostrar informacion basica del dfa. ---------*"<<endl;
			cout << "\t" << "*----->	3. Identificar los estados de muerte. ----------*"<<endl;
			cout << "\t" << "*----->	4. Analizar cadena. ----------------------------*"<<endl;
			cout << "\t" << "*----->	5. Exportar DFA  ----------------------------*"<<endl;
			cout << "\t" << "*----->	6. Minimizar DFA  ----------------------------*"<<endl;
			cout << "\t" << "*----->	7. Minimizar DFA y exportar --------------------------*"<<endl;
			cout << "\t" << "*----->	8. Salir. --------------------------------------*"<<endl;
			cout << BOLD ( "	*-----> Introduce la opción deseada: ---------------*") <<endl;
			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*********************************************************" <<endl <<endl;;
			cin >> opcion;
			
			
			switch (opcion){
				
				
				case 1:
		        	cout << endl;
		        	cout << "Introduce el nombre del fichero" << endl;
		        	cin >> Nombre_Fichero;
		        	
		        	Aux.Cargar_DFA(Nombre_Fichero);
		        	
		        break;
		      
		      
				case 2:
				
						cout << endl;
						Aux.Mostrar_infor_DFA();
					
				break;
				
				
				case 3:
					
						cout << endl;
						Aux.detectar_muerte();
				
				break;
					
					
				case 4:
					
						cout << endl;
						Aux.Analizar_Cadena();
				
				break;
				
				case 5:
						cout <<endl;
						Aux.Exportar_DFA();
				break;
				
				
				case 6:
					cout <<endl;
					Aux.Minimizar_DFA(true);   
				break;
					
				case 7:
    			    resultado = Aux.Minimizar_DFA(false);
    			    resultado.Exportar_DFA();
                break;
						//Aux.Minimizar_DFA();
				
				break;
				
				default:
					cout <<endl << FRED("------> ERROR <------")<< " Opción incorrecta, saliendo del programa." << endl;
					opcion = 8;
				break;
					
			}
			
		}while(opcion!=8);
	
}
	   		
   		
   		
   	
				
