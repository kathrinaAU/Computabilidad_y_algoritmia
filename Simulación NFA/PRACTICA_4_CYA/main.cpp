#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"

#include "NFA.hpp"
 
using namespace std;


void animacion_inicio(void){

	system("clear");

	int contador=1;
	
	do{	
	
		cout <<endl<<endl;
		cout<<FCYN("			AUTÓMATA FINITO DETERMINISTA (NFA):");
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
	cout << FGRN(" .NFA");
	cout << " que desea cargar: " <<endl<<endl;
	cin >> Nombre_Fichero;
	NFA Aux(Nombre_Fichero);
	bool primero=false;
   	
  
   		
   		do{
   			cout <<endl <<endl;
   			cout<< BOLD("	******************************* OPCIONES ******************************") <<endl;
   			cout << "\t" << "*---------------------------------------------------------------------*" <<endl;
			cout << "\t" << "*---------->	1. Cargar otro NFA desde un fichero. -----------------*" <<endl;
			cout << "\t" << "*---------->	2. Mostrar informacion basica del NFA. ---------------*"<<endl;
			cout << "\t" << "*---------->	3. Identificar los estados de muerte. ----------------*"<<endl;
			cout << "\t" << "*---------->	4. Analizar cadena. ----------------------------------*"<<endl;	
			cout << "\t" << "*---------->	5. Mostrar estados importantes y no importantes. -----*"<<endl;	 
			cout << "\t" << "*---------->	6. Comprobar si es un NFA ----------------------------*"<<endl;	
			cout << "\t" << "*---------->	7. Salir. --------------------------------------------*"<<endl;
			cout << BOLD ( "	*----->   Introduce la opción deseada: -------------------------------*") <<endl;
			cout << "\t" << "*---------------------------------------------------------------------*" <<endl;
			cout << "\t" << "***********************************************************************" <<endl <<endl;;
			cin >> opcion;
			
			
			switch (opcion){
				
				
				case 1:
		        	cout << endl;
		        	cout << "Introduce el nombre del fichero" << endl;
		        	cin >> Nombre_Fichero;
		        	
		        	Aux.Cargar_NFA(Nombre_Fichero);
		        break;
		      
		      
				case 2:
				
						cout << endl;
						Aux.Mostrar_infor_NFA();
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
					
					cout << "Detectando estados..." <<endl;
					cout << "Estados importantes:"<<endl;
					Aux.estados_importantes();
					cout <<endl<<"Estados no importantes"<<endl;
					Aux.estados_no_importantes();
				break;
				
				
				case 6:
				
					cout << "¿Es un dfa o un nfa?" << endl;
					Aux.comprobar_nfa();
				break;
				
				case 7:
				  	
				  	cout << "Saliendo del programa." << endl;
				break;
				
				default:
				
					cout <<endl << FRED("------> ERROR <------")<< " Opción incorrecta, saliendo del programa." << endl;
					opcion = 7;
				break;
					
			}
			
		}while(opcion!=7);
	
}
	   		
   		
   		
   	
				
