/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Clase op.*/

using namespace std;
#include <cstdio>
#include <cstring>
#include "op.hpp"


//______________________________________________________________________________
//CONSTRUCTORES:
//------------------------------------------------------------------------------

//Constructor para 2 lenguajes:
OP::OP(){

	cout << "Introduzca el lenguaje L1:" << endl;
	cout << "L1 --> ";
   
	string lenguaje_1;
	getline(cin, lenguaje_1);
	getline(cin, lenguaje_1);
   
	calculo_n(lenguaje_1);

	l1 = new string[N];

	desglosar_contenido(lenguaje_1);
   	
   	
// _____________________________________________________________________________
   	
	cout << "Introduzca el lenguaje L2:" << endl;
	cout << "L2 --> ";
   
	string lenguaje_2;
	getline(cin, lenguaje_2);


	calculo_m(lenguaje_2);

	l2 = new string[M];

	desglosar_contenido2(lenguaje_2);	


//______________________________________________________________________________

	 // Inicializamos y mostramos el conjunto A
    formar_conjunto1();

    // Inicializamos y contramos el conjunto B
	formar_conjunto2();

}

//______________________________________________________________________________
// Constructor para 1 lenguaje: 
OP::OP(int numero){

	cout << "Introduzca el lenguaje L1:" << endl;
	cout << "L1 --> ";
   
	string lenguaje_1;
	getline(cin, lenguaje_1);
	getline(cin, lenguaje_1);
   
	calculo_n(lenguaje_1);

	l1 = new string[N];

	desglosar_contenido(lenguaje_1);
   	
	 // Inicializamos y mostramos el conjunto A
    formar_conjunto1();
}


// _____________________________________________________________________________
// DESTRUCTOR

OP::~OP(){
    
    cout << "Destruyendo L1..."<<endl;
    mostrar(CjtoA);
    cout << endl;
    
    cout << "Destruyendo L2..."<<endl;
    mostrar(CjtoB);
    cout << endl;
    
}


//______________________________________________________________________________
// Método para calcular N

void OP::calculo_n(string lenguaje_1){
	
	for (int i = 0; i<lenguaje_1.size(); i++){
		if (( lenguaje_1[i] == ',') || (lenguaje_1[i] == '|')){
			N++;
		}
	}
}


//______________________________________________________________________________
// Método para calcular M

void OP::calculo_m(string lenguaje_2){
	
	for (int i = 0; i<lenguaje_2.size(); i++){
		if (( lenguaje_2[i] == ',') || (lenguaje_2[i] == '|')){
			M++;
		}
	}
}


//______________________________________________________________________________
// Método para formar conjunto 1

void OP::formar_conjunto1(void){

	cout << endl;
	cout << "Lenguaje L1 formado por:" << endl;
	for (int i=0; i<N;i++){
		cadena tmp(l1[i]);
		CjtoA.insert(tmp);
		CjtoC.insert(tmp);
	}
	cout << "L1 { ";
	mostrar(CjtoA);
	cout << "}"<<endl;
	cout << endl;
	
}


//______________________________________________________________________________
// Método para formar conjunto 2

void OP::formar_conjunto2(void){
	
	cout << endl;
	cout << "Lenguaje L2 formado por: " << endl;
	for (int i=0; i<M; i++){
		cadena tmp(l2[i]);
		CjtoB.insert(tmp);
	}
	cout << "L2 { ";
	mostrar(CjtoB);
	cout << "}" << endl;
	cout << endl;
	
}


//______________________________________________________________________________
// Método para separar contenido 1

void OP::desglosar_contenido(string lenguaje_1){

int posicion=0;
   int posicion2=0;
   
	
   while( posicion < lenguaje_1.length() ){
   		
   		if( (lenguaje_1[posicion] == '{') || (lenguaje_1[posicion] == '}') || (lenguaje_1[posicion] == ' ') ){
   		posicion++;
   		}else if(( lenguaje_1[posicion] == ',' ) || (lenguaje_1[posicion] == '|')){
   			posicion2++;
   			posicion++;
   		}else{
   			l1[posicion2] += lenguaje_1[posicion];
   					posicion++;
   		}
   }
}


//______________________________________________________________________________
// Método para separar contenido 2

void OP::desglosar_contenido2(string lenguaje_2){

	int posicion = 0;
	int posicion2 = 0;
   
	
    while( posicion < lenguaje_2.length() ){
   		if( (lenguaje_2[posicion] == '{') || (lenguaje_2[posicion] == '}') || (lenguaje_2[posicion] == ' ')) {
   			posicion++;
   		} else if (( lenguaje_2[posicion] == ',' ) || (lenguaje_2[posicion] == '|')) {
   			posicion2++;
   			posicion++;
   		} else {
   			l2[posicion2] += lenguaje_2[posicion];
   			posicion++;
   		}
    }
}


//______________________________________________________________________________
// Método para mostrar por pantalla

void OP::mostrar (set <cadena> Cjto){
	set<cadena>::iterator contador = Cjto.end();
	int aux = 0;
	for (set<cadena>::iterator i = Cjto.begin(); i != Cjto.end(); i++){
		
		if (aux > 0){
			cout << ", ";
		}
			cout << (*i);
			aux++;
	}
}


//______________________________________________________________________________
// Calculadora: Opción: Unión:

void OP::calculo_union(void){
	
	cout << " L1 U L2 { ";

	ostream_iterator< cadena > iter( cout, ", ");
	set_union(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(), iter);
	cout << "}" << endl;
    cout << endl;
	
}


//______________________________________________________________________________
// Calculadora: Opción: Intersección:
void OP::calculo_interseccion(void){
	
    cout<<" L1 ∩ L2 { ";
  
	ostream_iterator< cadena > iter( cout, "" );
	set_intersection(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(), iter);    
	cout << " }" << endl;
	cout << endl;
	
}


//______________________________________________________________________________
// Calculadora: Opción: Diferencia:

void OP::calculo_diferencia(void){

	ostream_iterator <cadena> iter( cout, "," );
    set <cadena> C;  
	set_difference(CjtoA.begin(), CjtoA.end(), CjtoB.begin(), CjtoB.end(),
    inserter(C, C.begin()));

	cout << "L1 - L2 { ";
	copy(C.begin(), C.end(), iter);

	cout << " }" << endl;
	cout << endl;	
	
	
}	


//______________________________________________________________________________
// Calculadora: Opción: Concatenación:

void OP::calculo_concatenacion(void){
	
	string l3 = "L3 { ";
	int contador = 0;
	int cantidad = N*M;
    
    cout << "La concatenacion es: ";
    
	for (set<cadena>::iterator i = CjtoA.begin(); i != CjtoA.end(); i++){
		for (set<cadena>::iterator j = CjtoB.begin(); j != CjtoB.end(); j++){
			l3+=(*i).cad_+(*j).cad_;
			if(contador < cantidad-1 ){
				l3+=", ";
				contador++;
			}	
		}
	}
	
	l3+=" }";
	cout << l3 << endl;
	
}


//______________________________________________________________________________
// Calculadora: Opción: Igualdad de lenguajes:

void OP::calculo_igualdad(void){
	
	ostream_iterator< cadena > iter( cout, "" );
    if(CjtoA == CjtoB){
        cout << "El lenguaje L1 y el lenguaje L2 son iguales." << endl;
    }else{
        cout << "Los lenguajes no son iguales." << endl;
	}
}


//______________________________________________________________________________
// Calculadora: Opción: Sublenguajes:
void OP::calculo_sublenguaje(void){
	
	bool contenido1 = false;
	int contador1 = 0;
	bool contenido2 = false;
	int contador2 = 0;

	for (set<cadena>::iterator i = CjtoA.begin(); i != CjtoA.end(); i++){
		for (set<cadena>::iterator j = CjtoB.begin(); j != CjtoB.end(); j++){
			if ((*i).cad_ == (*j).cad_){
				contador1++;
				break;				
			}
		}
	}

	if (contador1 == N){
		contenido1=true;
	}
	
	for (set<cadena>::iterator i = CjtoB.begin(); i != CjtoB.end(); i++){
		for (set<cadena>::iterator j = CjtoA.begin(); j != CjtoA.end(); j++){
			if ( (*i).cad_ == (*j).cad_){
				contador2++;
				break;				
			}
		}
	}
	
	if (contador2 == M){
		contenido2 = true;
	}
	
	switch(contenido1){
		case 1: cout << "L1 esta contenido en L2" << endl; break;
		case 0: cout << "L1 no esta contenido en L2" << endl; break;
	}
	switch(contenido2){
		case 1: cout << "L2 esta contenido en L1" << endl; break;
		case 0: cout << "L2 no esta contenido en L1" << endl; break;
	}
}

//______________________________________________________________________________
// Calculadora: Opción: Potencia:

void OP::calculo_potencia(void){
	
	int potencia;

	cout << "¿Que potencia desea calcular?"<<endl;
	cout << "L1^";
	cin >> potencia;
	cout << endl;
	
	switch(potencia){
		
		case 0: 
			cout << "L1^0-->{ & }" << endl;  
			break;

		case 1:
			cout << "L1^1-->{ ";
			mostrar(CjtoA);	
			cout << " }" << endl;  
			break;
		
		default: 
			cout << "L1^" << potencia << "-->{ ";
		
			potencia=potencia-1; 
			int cantidad=80;
			int cuenta = 0;
			int contador = 0;
			
			string *aux;
			aux = new string[cantidad];
			//Contador va a contar por la potencia que vamos
		    while(contador < potencia ){
		    	// Primero, inserto los símbolos normales del leguaje
		   		for (set<cadena>::iterator i = CjtoC.begin(); i != CjtoC.end(); i++){	  
					CjtoD.insert( (*i).cad_ );
				}	  
				// Luego, inserto la suma en plan a+b = ab
		   		for (set<cadena>::iterator i = CjtoA.begin(); i != CjtoA.end(); i++){
					for (set<cadena>::iterator j = CjtoC.begin(); j != CjtoC.end(); j++){
						aux[cuenta] =(*i).cad_+(*j).cad_;
						cuenta++;
					}
				}
				// A continuación, inserto los datos en un conjunto
				for (int i = 0; i < cuenta; i++){
					cadena tmp(aux[i]);
					CjtoC.insert(tmp);
				}
			
				contador++; 
		   }
			
			for (set<cadena>::iterator i = CjtoD.begin(); i != CjtoD.end(); i++){	
				//cout << "hoaaaaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
				//mostrar(CjtoC);
				//CjtoC.erase((*i).cad_);
			}	   
		 
			mostrar(CjtoC);
			cout << " }" << endl;  
			break;
		
	}

}


//______________________________________________________________________________
// Calculadora: Opción: Inversa:

void OP::calculo_inversa(void){

int contador = 0;	
string aux;
	
	cout <<"L1 {";
	
	for (set<cadena>::iterator i = CjtoA.begin(); i != CjtoA.end(); i++){
		aux = (*i).cad_;
		for (int j = aux.length(); j>=0; j--){
			cout << aux[j];
		}
		if(contador < aux.length() ){
			contador++;
		}	
		if (contador < aux.length()){
			cout << ", ";
			contador++;
		}
	}
	cout << "} " << endl;
	
}


//______________________________________________________________________________
// Calculadora: Opción: Cierre de Kleene:

void OP::calculo_cierre_kleene(void){
	
	int cantidad=60;
	int cadenas_max = 8;
	int counter = 0;
	int contador = 0;
	
	string *aux;
	aux = new string[cantidad];

    cout << "El cierre de Kleene es: ";

   do{
    
   /*A: aa bc de
   C: aab sw
   aux(1) aaaab*/
   
    	//Recorro los conjuntos y guardo la solución en aux e incremento counter
		for (set<cadena>::iterator i = CjtoA.begin(); i != CjtoA.end(); i++){
			for (set<cadena>::iterator j = CjtoC.begin(); j != CjtoC.end(); j++){
				aux[counter] =(*i).cad_+(*j).cad_;
				counter++;
				}
			}
			//Recorro el conjunto y voy guardando en tmp lo que antes obtuvimos en aux
			 for (int i = 0; i < counter; i++){
				cadena tmp(aux[i]);
				CjtoC.insert(tmp); //Lo metemos en el conjunto C
			}
		  
			contador = counter;
			counter = 0;

   }while(contador < cadenas_max );
 
  	cout << "L1* { &, ";
	mostrar(CjtoC);
	cout << "...}" << endl;
}



