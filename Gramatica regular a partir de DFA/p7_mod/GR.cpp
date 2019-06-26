#include "GR.hpp"
#include "Producciones.hpp"


Gramatica::Gramatica(set<char> alfa, char x){
	   alfabeto=alfa;
    inicial=x;
}

////////////////////////////////////////////////////////////////////////////////

Gramatica::Gramatica(){
}


////////////////////////////////////////////////////////////////////////////////

Gramatica::~Gramatica(){
}

////////////////////////////////////////////////////////////////////////////////

void Gramatica::anadir_production(Produccion prod){
	production.push_back(prod); //Introduzco el prod en el vector
}


////////////////////////////////////////////////////////////////////////////////

void Gramatica::set_nt(set<char> n){
 no_terminal = n; // Igualar un no terminal a otro
}

////////////////////////////////////////////////////////////////////////////////

void Gramatica::exportar(){

   char fich[50];
   cout << "Intrduzca el fichero a exportar (.grm): " << endl;
   cin >> fich; //Fichero en donde guardo la gramática
 
   ofstream file; 
   file.open(fich); //Abrimos el fichero
 
   if (file.is_open()){ //Si el fichero se abre
      file << alfabeto.size() << endl; // Introducimos primera linea al fichero: Línea 1: número total de símbolos terminales que posee la gramática.
  
     	set<char>::iterator alfa; // Iterador para recorrer el alfabeto y meterlo en el fichero.
    
     	for (alfa=alfabeto.begin(); alfa!=alfabeto.end(); alfa++){ //Recorremos el alfabeto y metemos cada simbolo
     		   file << (*alfa) << " "; // Introducimos segunda línea al fichero. Línea 2: lista de todos los símbolos terminales de la gramática,
     	                            //separados por espacios en blanco. Cada terminal se representa mediante un caracter ASCII.
    
     	}
     	
     	file << endl; 
     	file << no_terminal.size() << endl; //Línea 3: número total de símbolos no terminales que posee la gramática.
     	
     	set<char>::iterator NT; // Iterador para recorrer el set de los no terminales
     	for (NT=no_terminal.begin(); NT!=no_terminal.end(); NT++){
     		   file << (*NT) << " "; //Línea 4: lista de todos los símbolos no terminales de la gramática, separados por espacios en blanco.
     		                        //Cada símbolo no terminal vendrá representado también mediante un caracter ASCII, preferiblemente letras 
     		                        //mayúsculas de nuestro abecedario. Se tomará como símbolo de arranque de la gramática aquel símbolo no 
     		                        //terminal que aparezca primero en esta lista.
     }
     
      file << endl;
    
      for(int i=0; i<production.size(); i++){ 
         	file << production[i].get_part_izq() << " " << "->"; //De la línea 5 en adelante el fichero tendrá una línea para cada uno
         	                                                     //de los símbolos no terminales de la gramática. En cada línea se especificarán
         	                                                     //las reglas de producción de un determinado símbolo no terminal. 
         	vector<string> dummy=production[i].get_part_derech();
         	
         	cout << "Dummy size " << dummy.size();
      	for(int i=0; i<dummy.size(); i++){
      		  file << dummy[i] << " " << "|";
      	}
      	
      	file << endl;
      	}
      	
      	file << endl;
      	file.close();
      	
  } 	
}
    