#include "DFA.hpp"
#include <cstring>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"
#define NAME_SIZE 50


//Necesitamos cargar cada uno de los datos ddel fichero .dfa
DFA::DFA(char Nombre_Fichero[])
{
    fstream in; 
    
    //Declaramos los datos que podemos encontrar en el fichero
    int Identificador;
    int Transiciones;
    bool Estado_Aceptacion;
    int *Destino; //dinámicos
    char *Simbolo;
    
    //Abrimos el archivo
    in.open(Nombre_Fichero);
    
   
    
        if (in.is_open()){
            //Empezamos a guardar los datos de la primera y segunda fila
            in >> (int &) Numero_Estados_ >> (int &) Estado_Inicial_ ; //El (int &) es para que lo entienda como entero 
        
            //Recorremos los estados y vamos a ir obteniendo los datos del dfa
            for (int i = 0; i < Numero_Estados_; i++){
                in >> Identificador >> Estado_Aceptacion >> Transiciones; 
            
                // simbolo y destino serán arrays de x tamaño en función de las transiciones asi que para ello previamente necesito conocer el numero de transiciones.
                Simbolo = new char[Transiciones]; 
                Destino = new int[Transiciones]; 
                // Ahora le damos el valor que tienen en el .dfa
                for (int j = 0; j < Transiciones; j++){
                    in >> Simbolo[j] >> Destino[j]; 
                }
                // Como es un set no hay push_back como en vectores, asi que creo un estado_t llamado tmp en el que meteré 
                //el comportamiento de cada estado y lo iré insertando en Estados_. Se meten ya ordenados y sin repetirse
                
                estado_t tmp(Identificador, Estado_Aceptacion, Transiciones, Simbolo, Destino); // Set que contiene todo
                Estados_.insert(tmp);
                
            }
            if (Transiciones <= 2){
                cout << " DFA CORRECTO." <<endl;
            }
            else{
                cout << "No se trata de un DFA." <<endl;
            }
        }
        
        
        //Comprobamos si el archivo todo está correcto
        if (Estados_.size() == Numero_Estados_){ //
            cout << "Perfecto, DFA cargado. " << endl;
        }
        
        else{
            cout << "No se puede cargar el archivo"<<endl;
            exit(1);
            }
         in.close();

}


// Método que se emplea para cargar otro archivo por lo que es el mismo que el anterior 
void DFA::Cargar_DFA(char Nombre_Fichero[]){
    fstream in;
    
    int Identificador;
    int Transiciones;
    bool Estado_Aceptacion;
    int *Destino;
    char *Simbolo;
    
    in.open(Nombre_Fichero);
    
    if (in.is_open()){
        
        in >> (int &) Numero_Estados_ >> (int &) Estado_Inicial_;

        for (int i = 0; i < Numero_Estados_; i++){
            
            in >> Identificador >> Estado_Aceptacion >> Transiciones;
            
            Simbolo = new char[Transiciones];
            Destino = new int[Transiciones];
            
            for (int j = 0; j < Transiciones; j++){
                in >> Simbolo[j] >> Destino[j];
            }
            
            estado_t tmp(Identificador, Estado_Aceptacion, Transiciones, Simbolo, Destino);
            Estados_.insert(tmp);
        }
    
    if (Estados_.size() == Numero_Estados_)
    {
        cout << "Correcto" << endl;
    }
    in.close();
    } else{
        cout << "No se puede cargar el archivo."<<endl;
        exit(1);
    }

}


//Destructor
DFA::~DFA(void)
{}



// Método que nos sirve para poder ver los comportamientos de cada estado del DFA
void DFA::Mostrar_infor_DFA(void){
    
    cout << endl;
    cout<< "---------------------------------- DFA ------------------------------------" <<endl;
    cout << "Información básica del DFA:" << endl;
    cout << "El número de estados es: " << Numero_Estados_ << endl;
    cout << "El estado inicial es: " << Estado_Inicial_ << endl <<endl;

    
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        
     cout<< "El estado q"<< (*i).id_ <<" tiene "<< (*i).Transiciones_<<" transiciones"<< " y";
 
        if( (*i).Aceptado_ == 1 ){
    		cout<<" es un estado de aceptacion"<<endl;
    	}else{
    		cout<<" no es un estados de aceptacion"<<endl;
    	    }   
         
    			
    	for (int j = 0; j<(*i).Transiciones_; j++){ // j+1 puesto que la j empieza en el for en 0
    	     cout << "Transición " << j+1 << ": --> Se dirige al estado: " <<  (*i).Destino_[j] << " con el símbolo " << (*i).Simbolo_[j] << endl;
    	     
    	}    
    	cout<<"----------------------------------------------------------------------------"<<endl;
    	}
    }

    



// Método que nos sirve para comprobar si es un estado de muerte
void DFA::Estados_de_Muerte(void)
{
    bool Exist = false;
    //Iteramos por el conjunto de set
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        int Counter = 0;
        estado_t Aux;
        Aux = (*i); //Accedo a la pos
       
        for (int j = 0; j < Aux.Transiciones_; j++ ){ // Por cada transicion compruebo si coincide su destino con el identificador de estado
            if (Aux.Destino_[j] == Aux.id_){ // what
                Counter++;
            }
        }
        
        if (Counter == Aux.Transiciones_){ // Si coincide los valores es que es un estado de muerte
            cout << "El estado " << Aux.id_ << " es de muerte" << endl;
            Exist = true;
        }
    }
    
    if(!Exist){
        cout << "No existen estados de muerte" << endl; 
    }

}




void DFA::Analizar_Cadena(void)
{
    char Cadena[50];
    
    cout << "Introduzca la cadena a analizar: " <<endl;
    cin >> Cadena;
    //cin.ignore(); 
    int Estado_Actual = Estado_Inicial_;
    int Next_State = Estado_Inicial_;
    bool Estado_Aceptado;
    
    cout << "Ha introducido la siguiente cadena: " << Cadena << endl << endl;
    cout << "Estado actual   Entrada    Estado siguiente" <<endl ;
    
    for (int j = 0; j < strlen(Cadena); j++){
        Estado_Actual = Next_State;    
    
 
        for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
            estado_t Aux;
            Aux =(*i);
            
            if (Aux.id_ == Estado_Actual){ // pARA COMPROBAR EN QUÉ ESTADO ESTOY
                for(int k=0; k< Aux.Transiciones_; k++){ //RECORRO TRANSICIONES
                    if(Cadena[j] == Aux.Simbolo_[k]){   // MIRO SI EN EL ESTADO QUE ESTOY COINCIDE UN SIMBOLO CON EL DE LA CADENA
                        Next_State = Aux.Destino_[k];
                        //aceptado = aux.aceptado_;
                    }
                }
            }
        }
        
        
        cout << Estado_Actual << "\t\t" << Cadena[j] << "\t\t" << Next_State << "\t" <<  endl;
        
        //estado_actual = next_state;
    }
    
    // CUANDO YA ACABÉ DE RECORRER LA CADENA COMPRUEBO SI EN EL ESTADO QUE ME HE QUEDADO ES UNO DE ACEPTACIÓN
    
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++)
    {
        estado_t Aux;
        Aux = (*i);
        
        if (Aux.id_ == Next_State){
            Estado_Aceptado = Aux.Aceptado_;
        }
    }
    
    cout << endl;
    if(Estado_Aceptado == true){
        cout << "Cadena ACEPTADA." << endl;
    }
	else{
		cout << "Cadena NO ACEPTADA." << endl;
	}
	
	//cout << Estado_Actual << ' ' << Next_State;
    
}



	