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
   	
  
   		
   		do{
   			cout <<endl <<endl;
   			cout<< BOLD("        *********************** OPCIONES ************************") <<endl;
   			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*----->	1. Cargar otro dfa desde un fichero. -----------*" <<endl;
			cout << "\t" << "*----->	2. Mostrar informacion basica del dfa. ---------*"<<endl;
			cout << "\t" << "*----->	3. Identificar los estados de muerte. ----------*"<<endl;
			cout << "\t" << "*----->	4. Analizar cadena. ----------------------------*"<<endl;	
			cout << "\t" << "*----->	5. Salir. --------------------------------------*"<<endl;
			cout << BOLD ( "	*-----> Introduce la opción deseada: ---------------*") <<endl;
			cout << "\t" << "*-------------------------------------------------------*" <<endl;
			cout << "\t" << "*********************************************************" <<endl <<endl;;
			cin >> opcion;
			
			
			switch (opcion){
				
				
				case 1:
		        	cout << endl;
		        	cout << "Introduce el nombre del fichero" << endl;
		        	cin >> Nombre_Fichero;
		        	
		        	//DFA aux(nombre_fichero);
		        	Aux.Cargar_DFA(Nombre_Fichero);
		        	//primero = true;
		        break;
		      
		      
				case 2:
					//if (primero == true){
						cout << endl;
						Aux.Mostrar_infor_DFA();
					//}
					//else{
					//	cout << " Primero debe introducir un fichero." << endl;
					//}
				break;
				
				
				case 3:
					//if (primero == true){
						cout << endl;
						Aux.Estados_de_Muerte();
					//}
					//else{
					//	cout << " Primero debe introducir un fichero." << endl; 
					//}
				break;
					
					
				case 4:
					//if (primero == true){
						cout << endl;
						Aux.Analizar_Cadena();
					//}
					//else{
					//	cout << " Primero debe introducir un fichero." << endl; 
					//}
				break;
				
				
				default:
					cout <<endl << FRED("------> ERROR <------")<< " Opción incorrecta, saliendo del programa." << endl;
					opcion = 5;
				break;
					
			}
			
		}while(opcion!=5);
	
}
	   		
   		
   		
   	
				
