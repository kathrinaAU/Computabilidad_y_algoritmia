#include "NFA.hpp"
#include <cstring>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"
#define NAME_SIZE 50


//Necesitamos cargar cada uno de los datos ddel fichero .nfa
NFA::NFA(char Nombre_Fichero[]){
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
        
            //Recorremos los estados y vamos a ir obteniendo los datos del NFA
            for (int i = 0; i < Numero_Estados_; i++){
                in >> Identificador >> Estado_Aceptacion >> Transiciones; 
            
                // simbolo y destino serán arrays de x tamaño en función de las transiciones asi que para ello previamente necesito conocer el numero de transiciones.
                Simbolo = new char[Transiciones]; 
                Destino = new int[Transiciones]; 
                // Ahora le damos el valor que tienen en el .NFA
                for (int j = 0; j < Transiciones; j++){
                    in >> Simbolo[j] >> Destino[j]; 
                }
                // Como es un set no hay push_back como en vectores, asi que creo un estado_t llamado tmp en el que meteré 
                //el comportamiento de cada estado y lo iré insertando en Estados_. Se meten ya ordenados y sin repetirse
                
                estado_t tmp(Identificador, Estado_Aceptacion, Transiciones, Simbolo, Destino); // Set que contiene todo
                Estados_.insert(tmp);
                
            }
            if (Transiciones <= 2){
                cout <<endl<< " NFA CORRECTO." <<endl;
            }
            else{
                cout <<endl<< "No se trata de un NFA." <<endl;
            }
        }
        
        
        //Comprobamos si el archivo todo está correcto
        if (Estados_.size() == Numero_Estados_){ //
            cout <<endl<< "Perfecto, NFA cargado. " <<endl<< endl;
            cout << "Alfabetizando:" <<endl;
		    alfabetizando();
			mostrar_alfabeto();
        }
        
        else{
            cout <<endl<< "No se puede cargar el archivo"<<endl;
            exit(1);
            }
         in.close();
         
         

}


// Método que se emplea para cargar otro archivo por lo que es el mismo que el anterior 
void NFA::Cargar_NFA(char Nombre_Fichero[]){
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
        cout <<endl<< "Correcto" << endl;
    }
    in.close();
    } else{
        cout <<endl<< "No se puede cargar el archivo."<<endl;
        exit(1);
    }

}


//Destructor
NFA::~NFA(void)
{}



// Método que nos sirve para poder ver los comportamientos de cada estado del NFA
void NFA::Mostrar_infor_NFA(void){
    
    cout << endl;
    cout<< "---------------------------------- NFA ------------------------------------" <<endl;
    cout << "Información básica del NFA:" << endl;
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

  
  
  void NFA::detectar_muerte(){
      
     int contador=0;
      cout << endl<< "Los estados de muerte son:" <<endl;
      
       for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        estado_t Aux;
        Aux = (*i);
    		if (Aux.estado_muerte()){
    			contador++;
    		}else{
    		    if (Aux.Aceptado_ == 1){
    		    cout<<"El estado "<< Aux.id_<< " es de aceptación por lo que no es de muerte."<<endl;
    		    }else{
    		        cout << "El estado " << Aux.id_ << " es de muerte." <<endl;
    		    }
    		}
    		
    		if(contador == Numero_Estados_){
    			cout<<"     Ninguno"<<endl;
    		}
      } 
    cout<<"---------------------------------------------------------------------------------------"<<endl;
    cout << endl; 
  }  
  





void NFA::Analizar_Cadena(void)
{
    char Cadena[50];
    char c;

    cout << "Introduzca la cadena a analizar: " <<endl;
    cin >> Cadena;


    bool correct = verificar_simbolos(Cadena);
    if(!correct){
        return;
    }
    
    vector<string>Camino;
    bool Aceptada=false;
    
    Analizar_Cadena_R(Cadena,Camino,Estado_Inicial_,0,Aceptada);
    
    cout << "Decisión Final: "; 
    if(Aceptada){
        cout << "Cadena ACEPTADA." << endl;
    }
    else{
        cout << "Cadena NO ACEPTADA." << endl;
    }
}




void NFA::Analizar_Cadena_R(char cadena[], vector<string> Camino, int Next_State,int num_cadena,bool &Aceptada){

    int Estado_actual=Next_State;
    
    if((num_cadena) == strlen(cadena) ){ // Si hemos acabado de recorrer la cadena
        
        cout << "Ha introducido la siguiente cadena: " << cadena << endl << endl;
        cout << "Estado actual   Entrada    Estado siguiente" <<endl ; // Mostramos caminos posibles con una tablita
        
        for(int i=0;i<Camino.size();i+=3) //El camino va a contener los datos: Estado actual, símbolo de entrada y estado siguiente.
            cout << Camino[i] << "\t\t" << Camino[i+1] << "\t\t" << Camino[i+2] << "\t" <<  endl; // Muestro los valores del camino para cada columna.
        
        for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
            estado_t Aux; // Iteramos por los estados.
            Aux = (*i);
            
            if(Aux.id_==Next_State){ // Para saber en que estado estamos
                if(Aux.Aceptado_){ // Comprobamos si es de aceptación
                    Aceptada=true;
                    cout << "Cadena ACEPTADA." << endl;
                }
                else{
                    cout << "Cadena NO ACEPTADA." << endl;
                }
            }
        }
        return;
    }
    
    else{ // Si todavía nos queda por recorrer simbolos de la cadena entonces:

        // Para cada cada uno de los estados del actual.
        for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
            estado_t Aux;
            Aux = (*i); // El estado de la iteracion actual

            // Mirar para cada una de las transiciones si se cumple que:
              // La transicion desde el estado actual, al siguiente mediante la consumicion de un elemento de la cinta es válida
              // O Transición del estado actual mediante la consumicion vacía (épsilon) es válida
            
            if (Aux.id_ == Estado_actual){ // PARA COMPROBAR EN QUÉ ESTADO ESTOY
                for(int k=0; k< Aux.Transiciones_; k++){ //RECORRO TRANSICIONES
                    char c = cadena[num_cadena];
                    
                    if((c == Aux.Simbolo_[k]) || (Aux.Simbolo_[k] == '~')){   // MIRO SI EN EL ESTADO QUE ESTOY COINCIDE UN SIMBOLO CON EL DE LA CADENA
                        Next_State = Aux.Destino_[k];
                        
                        
                        //char a string
                        string tmp,tmp2;
                        stringstream convert,convert2;
                        convert << (Estado_actual);
                        convert2 << (Next_State);
                        tmp = convert.str();
                        tmp2 = convert2.str();

                        
                        if(Aux.Simbolo_[k] == '~'){
                            
                            Camino.push_back(tmp);
                            Camino.push_back("~");
                            Camino.push_back(tmp2);
                            
                            Analizar_Cadena_R(cadena,Camino,Next_State,num_cadena,Aceptada);
                            Camino.pop_back(); //Para ir hacia las otras transiciones que me quedaron pendientes 
                            Camino.pop_back();
                            Camino.pop_back();
                            
                        }
                        else{
                            
                            Camino.push_back(tmp);
                            
                            stringstream ss;
                            string s;
                            ss << cadena[num_cadena];
                            ss >> s;
                            
                            Camino.push_back(s);
                            Camino.push_back(tmp2);
                            
                            Analizar_Cadena_R(cadena,Camino,Next_State,num_cadena+1,Aceptada);
                            
                            Camino.pop_back();
                            Camino.pop_back();
                            Camino.pop_back();
                        }
                    }
                }
             }
        }
    }
    return;
}









void NFA::alfabetizando(void){

  
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        
    	for (int j = 0; j<(*i).Transiciones_; j++){ // j+1 puesto que la j empieza en el for en 0
    	     
    	     Alfabeto.insert( (*i).Simbolo_[j] );
    	     
    	     
    	}    
    
    }
  
    
}





void NFA::mostrar_alfabeto(void){
  
  cout << "El alfabeto utilizado es -> ";
      
  for(set<char>::iterator i = Alfabeto.begin(); i != Alfabeto.end(); i++){
    cout << (*i) << " ";
  }
  
  cout << endl;
  
 
  
} 




    /*Hay que recordar que en un NFA decimos que un estado es importante si tiene al menos una 
    transición saliente etiquetada con uno de los símbolos del alfabeto, o bien, si es un estado
    de aceptación. Es decir, los estados no importantes serán aquellos que no son de aceptación 
    y sólo tienen transiciones salientes etiquetadas con epsilon.*/
    
    
void NFA::estados_importantes(void){
 
      for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){

           if( (*i).Aceptado_ == 1 ){
               
                Estados_importantes.insert( (*i).id_ );
           }   
    	
    	for (int j = 0; j<(*i).Transiciones_; j++){ // j+1 puesto que la j empieza en el for en 0
    	    

    	   if(  ( (*i).Destino_[j] != (*i).id_ ) &&  ( (*i).Simbolo_[j] != '~')  ){

    	         Estados_importantes.insert( (*i).id_ );
    	    }    

         }
    
      }
      
  cout << "El conjunto importante es -> ";
      
  for(set<int>::iterator i = Estados_importantes.begin(); i != Estados_importantes.end(); i++){
    cout << (*i) << " ";
  }

}

//los estados no importantes serán aquellos que no son de aceptación y sólo tienen transiciones salientes etiquetadas con epsilon.

void NFA::estados_no_importantes(void){
    

    
     for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
      
        if (Estados_importantes.find( (*i).id_ ) != Estados_importantes.end()){
          
        }else{
            Estados_no_importantes.insert( (*i).id_ );
        }
         
     }
    
    

    
    
  cout << "El conjunto no importante es -> ";
      
  for(set<int>::iterator i = Estados_no_importantes.begin(); i != Estados_no_importantes.end(); i++){
    cout << (*i) << " ";
  }
  
  
    
}


bool NFA::verificar_simbolos(char *Cadena){
    
    bool bien = true;
    
    
    for (int i = 0; i< strlen(Cadena); i++){
        
        char prueba = Cadena[i];
        
     
        
        //for(set<char>::iterator i = Alfabeto.begin(); i != Alfabeto.end(); i++){   
            
         if ( Alfabeto.find( prueba ) == Alfabeto.end() ){
            
            cout << " Se ha detectado un simbolo que no está incluido en el alfabeto" << endl;
             bien = false;

          }else{
           
          }
       // }
    }
    
    if(bien){
         cout << " Simbolos correctos" << endl;
    }

    return bien;
    
}


/*Es DFA: comprobar si el autómata finito cargado desde fichero es un DFA o no.
Tener en cuenta que los DFAs tienen una y sola una transición, desde cada estado, 
para cada uno de los símbolos del alfabeto. Hay que tener en cuenta que aunque el 
autómata finito leído desde fichero sea un DFA, se podrán aplicar el resto de
opciones del menú de la misma forma que si se hubiera tratado de un NFA que no es DFA.*/

void NFA::comprobar_nfa(void){
   
   // Variable local, desde fuera no se sabe qué valor tiene. cuando termina la ejecución de la función, esa variable se borra.
   bool salida = false;
    bool fin = false;
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        
        
        for (int j = 0; j<(*i).Transiciones_ && !fin; j++){
            
            cout << " TRANSICIONES " << (*i).Transiciones_ << endl;
            cout << " alfabeto size " << Alfabeto.size() << endl;
            cout << "simbolos: " <<  (*i).Simbolo_[j]<<endl;
            
            
            if( ( (*i).Simbolo_[j] == '~') || ( (*i).Transiciones_ > Alfabeto.size() ) || ( (*i).Transiciones_ < Alfabeto.size() ) ) {
                cout << "estoy en nfa caso" <<endl;
                salida = true;
                cout << boolalpha << salida << endl;
                fin = true;
    		
            }else{
                salida = false;
                
            }
    
        }
    }
    
    
    

	switch(salida){
		case 0: cout<<"El fichero es un DFA"<<endl;	break;
		case 1: cout<<"El fichero es un NFA"<<endl;	break;
	}

}