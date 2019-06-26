#include "DFA.hpp"
#include <cstring>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"
#define NAME_SIZE 50


DFA::DFA(){}

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
                //cout << "No se trata de un DFA." <<endl;
            }
        }
        
        
        
        //Comprobamos si el archivo todo está correcto
        if (Estados_.size() == Numero_Estados_){ //
            cout <<endl<< "Perfecto, DFA cargado. " <<endl<< endl;
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
        cout <<endl<< "Correcto" << endl;
    }
    in.close();
    } else{
        cout <<endl<< "No se puede cargar el archivo."<<endl;
        exit(1);
    }

}



//Destructor
DFA::~DFA(void)
{}



void DFA::alfabetizando(void){

  
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        
    	for (int j = 0; j<(*i).Transiciones_; j++){ // j+1 puesto que la j empieza en el for en 0
    	     
    	     Alfabeto.insert( (*i).Simbolo_[j] );
    	     
    	     
    	}    
    
    }
  
    
}



void DFA::mostrar_alfabeto(void){
  
  cout << "El alfabeto utilizado es -> ";
      
  for(set<char>::iterator i = Alfabeto.begin(); i != Alfabeto.end(); i++){
    cout << (*i) << " ";
  }
  
  cout << endl;
  
 
  
} 





bool DFA::verificar_simbolos(char *Cadena){
    
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


 
  
  void DFA::detectar_muerte(){
      
      int contador=0;
      cout << endl<< "Los estados de muerte son:" <<endl;
      
       for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        estado_t Aux;
        Aux = (*i);
    		if (Aux.estado_muerte()){
    			cout<<"El estado "<< Aux.id_<<endl;
    		}else{
    			contador++;
    		}
    		
    		if(contador == Numero_Estados_){
    			cout<<"     Ninguno"<<endl;
    		}
      } 
    cout<<"---------------------------------------------------------------------------------------"<<endl;
    cout << endl; 
  }  




void DFA::Analizar_Cadena(void){


    char Cadena[50];
    
    cout << "Introduzca la cadena a analizar: " <<endl;
    cin >> Cadena;
    
    
    bool correct = verificar_simbolos(Cadena);
    if(!correct){
        return;
    }else{
        
    }
    
    bool comprueba = false;
    //cin.ignore(); 
    int Estado_Actual = Estado_Inicial_;
    int Next_State = Estado_Inicial_;
    bool Estado_Aceptado;
    //bool encontrado=false;
    
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
                    }else{
                        comprueba=true;
                    }
                        //aceptado = aux.aceptado_;
                    }
                 }
            }
            
 
        cout << Estado_Actual << "\t\t" << Cadena[j] << "\t\t" << Next_State << "\t" <<  endl;
        
        //estado_actual = next_state;
    }
    
    // CUANDO YA ACABÉ DE RECORRER LA CADENA COMPRUEBO SI EN EL ESTADO QUE ME HE QUEDADO ES UNO DE ACEPTACIÓN
    
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        estado_t Aux;
        Aux = (*i);
        
        if (Aux.id_ == Next_State){
            Estado_Aceptado = Aux.Aceptado_;
        }
    }
    
    
   // && (comprueba == false)
   
      if( (Estado_Aceptado == true) ){
        cout << "Cadena ACEPTADA." << endl;
    }
	else{
		cout << "Cadena NO ACEPTADA." << endl;
	}
    
   
 
   
    
}


void DFA::Exportar_DFA(){
    
    char nombre[80];
    cout << "Introduzca el nombre del fichero .dfa a exportar: "; 
    cin >> nombre;
    ofstream salida(nombre); 

   salida << Estados_.size() << endl;
   salida << estado_activo.id_ << endl;
   for(set <estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
	    estado_t aux;
	    aux = (*i);
	    salida << aux.id_<< " " << aux.Aceptado_ << " " << aux.Transiciones_ << " ";
	    for (int i= 0; i < aux.Transiciones_; i++){
	        salida  <<  aux.Simbolo_[i] << " " << aux.Destino_[i] << " ";
	   }
	    salida << endl;
    }
   
}






DFA DFA::Minimizar_DFA(bool muestra_Ejecucion){
    
    set< set<estado_t> > Subconjuntos;
    set< set<estado_t> > PI_viejo;
    set<estado_t> aceptacion;
    set<estado_t> no_aceptacion;
    
    for (set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
        estado_t Aux;
        Aux = (*i);
        if(Aux.Aceptado_){
            aceptacion.insert( Aux );
           // Estados_aceptacion.insert( (*i).id_ );
        }
        else{
            no_aceptacion.insert( Aux ); 
            //Estados_no_aceptacion.insert((*i).id_);
        }
            
    }
    
    Subconjuntos.insert(aceptacion);
    Subconjuntos.insert(no_aceptacion);
   
   
    
    if (muestra_Ejecucion){
        Mostrar_Particion(Subconjuntos);
    }

    do{
    
        PI_viejo = Subconjuntos;
        Subconjuntos = nueva_particion(PI_viejo, muestra_Ejecucion);
     
    }while(Subconjuntos != PI_viejo);

    return reconstruir_DFA(Subconjuntos);

}




void DFA::Mostrar_Particion( set <set<estado_t> > set_aux){
    
    cout<<"Particion: {";
  
    
    for (set< set< estado_t> >::iterator i = set_aux.begin(); i!=set_aux.end(); i++){
        cout << "{";
        
        for(set<estado_t>::iterator j = (*i).begin(); j!= (*i).end(); j++){
            
            cout << (*j).id_ << " ";
        }
        cout << "} ";
    }
    cout << "}" <<endl;
}



 set< set<estado_t> > DFA::nueva_particion( set< set<estado_t> > PI_viejo, bool ejec ){
     set <char>::iterator simbolos;
     
     for(simbolos=Alfabeto.begin(); (simbolos)!=Alfabeto.end(); simbolos++){
         char letra = (*simbolos);
         
         PI_viejo = descomponer(PI_viejo, letra);
         
         if(ejec==true){
            cout << " Con el símbolo " << (*simbolos) << ": " <<endl;
            Mostrar_Particion(PI_viejo);
         }
     }
     return PI_viejo;
 }



    set< set<estado_t> > DFA::descomponer(set< set<estado_t> > Subconjuntos, char a){
        set< set<estado_t> > Subconjunto_Nuevo;
        set< set<estado_t> >::iterator i;
        
        for(i = Subconjuntos.begin(); i!=Subconjuntos.end(); i++){
            set< set<estado_t> > Temp = particionar ((*i), a, Subconjuntos);
            //cout <<"Mostrando::::::: "<< Temp <<endl;
            Subconjunto_Nuevo.insert(Temp.begin(), Temp.end());
            
        }
        
        return Subconjunto_Nuevo;
    }




set< set<estado_t> > DFA::particionar(set<estado_t> G, char symbol, set< set<estado_t> > Subconjuntos){

    set< set<estado_t> > Particion;

    //Para los conjuntos de Subconjuntos
    //Recorro los conjuntos de conjuntos
    for(set< set<estado_t> >::iterator i = Subconjuntos.begin(); i!=Subconjuntos.end(); i++){
        set<estado_t> colector;
        /*estado_t Aux1;
        Aux1 = (*i);
*/
        //{{3}, {5, 6, 1, 2}}
        
        //Recorro cada subconjunto
            for(set<estado_t>::iterator j = G.begin(); j!=G.end(); j++){
                /*estado_t Aux2;
                Aux2 = (*j);*/
                estado_t auxIni = (*j); // Para el estado j
                estado_t auxNext = estado_t( auxIni.get_next(symbol), 0 , 0 ); //Creo un estado siguiente para ver si forma parte del conjunto
                //cout << "estado::::::: " << (*j) << endl;
                set<estado_t>::iterator find = (*i).find(auxNext); //Va a buscar si hay otra transicion que vaya a otros conjuntos
                if(find != (*i).end()){
                    colector.insert(auxIni);
                   // cout << "AUX INI?????" << auxIni <<endl;
                }
            }
        if( !colector.empty() ){
            Particion.insert(colector);
        }
    }
    return Particion;

}



DFA DFA::reconstruir_DFA(set< set<estado_t> > Subconjuntos){
    //cout << "Hola" <<endl;
    DFA Aux;
    Aux.Alfabeto = Alfabeto;
    Aux.estado_activo = estado_activo;
    
    int cont = 0; // Id del subconjunto
    //cout << " Depurando 1" <<endl;
   //{{}{}{}{}}
    set< set<estado_t> >::iterator G;
    
    // 1. Recorrer el conjunto de conjuntos
    for(G=Subconjuntos.begin(); G!=Subconjuntos.end(); G++){
        //cout << " Depurando 2" <<endl;
        set<estado_t>::iterator iter;
        //cout << " Depurando 3" <<endl; 
        iter = (*G).begin();
        estado_t dummy;
        //cout << " Depurando 3.2" <<endl; 
        dummy = (*iter);
    
        
        // cout << " Depurando 3.2" <<endl; 
        dummy.id_ = cont;
        
        transicion* trans = dummy.get_transicion();
        
        
          //cout << " Depurando 3" <<endl;   
          for(int i=0; i<dummy.Transiciones_; i++){
              
      //  cout << "TRANS SIGUIENTE " << trans[i].estado_siguiente << endl;
      //  cout << "TRANS Sub simbolo " << trans[i].simbolo<< endl;
              
            //   cout << " Depurando 4" <<endl;
            int next = trans[i].estado_siguiente;
            estado_t aux_next (next, 0, 0);
        
    //    cout << "AuxNext --> " << aux_next << endl;
        
        
             int sub_cont = 0;
             
            //Encontrar el conjunto al que pertenece
            set< set<estado_t> >::iterator j;
            //cout << " Depurando 5" <<endl;
            for(j=Subconjuntos.begin(); j!=Subconjuntos.end(); j++){
                //cout << " Depurando 6" <<endl;
                set<estado_t>::iterator iterSet = (*j).find(aux_next);
                
                
                if(iterSet != (*j).end() ){
                    // cout << " Depurando 7" <<endl;
                     //cout << "PROBANDO PROBANDO 1 2 SE ME ESCUCHA? "<< trans[i].estado_siguiente << " SIMBOLO "<< trans[i].simbolo << endl;
            //        cout << "SIGUIENTE " << trans[i].estado_siguiente << endl;
            //        cout << "Sub cont " << sub_cont << endl;
                    
                    trans[i].estado_siguiente = sub_cont;
                }
                // cout << " Depurando 8" <<endl;
                sub_cont++;
            }
       
        //for (int k = 0; k< dummy.Transiciones_; k++){
             //cout << " Depurando 9" <<endl;
            dummy.setTrans(trans);
            
       //     cout << "DUMMY setrans simb-> " << trans[i].simbolo << endl;
	//		cout << "DUMMY setrans est-> " << trans[i].estado_siguiente << endl;
            
       // }
        
          }
           //cout << " Depurando 10" <<endl;
            Aux.Estados_.insert(dummy);
            
         //   cout << "DUMMY" << dummy << endl;
            
            cont++;
        }
          //cout << " Depurando 11" <<endl;   
    return Aux;
    
}            


estado_t DFA::to_estado(int nombre){
    set<estado_t>::iterator iter1;
    for (iter1=Estados_.begin(); iter1!=Estados_.end(); iter1++){
        estado_t aux=(*iter1);
        if(aux.id_ == nombre)
            return aux;
    }
 return estado_t();
}


Gramatica DFA::Crear_Gramatica(){
    
   
    char estadete_arranque = (Estado_Inicial_+ 65);
    Gramatica pepe(Alfabeto, estadete_arranque); //Introduzco el alfabeto y el primer estado del dfa a la gramática 
    
    set <char> nterminal;
    set<estado_t>:: iterator iter;
    
    
    for( iter = Estados_.begin(); iter != Estados_.end(); iter++){
        //cout << "ENTRA:  " << (*iter) <<endl;
        if(!(*iter).estado_muerte()){
            // Lineal por la derecha primero pongo la S payuscula y luego la a
            nterminal.insert(((*iter).id_) + 65);
            
            Produccion produc;
            produc.set_part_izq(((*iter).id_) + 65);

            produc.get_part_izq(); //Primero miro la parte izquierda

            if((*iter).get_aceptacion() ){
                produc.anadir_part_derech("~"); //cadena vacia por ser de aceptacion
            }
        
            transicion *peter = (*iter).get_transicion();
            for(int i=0; i <(*iter).Transiciones_; i++){ //Recorro las transiciones del estado
                estado_t auxt;
                auxt = to_estado(peter[i].estado_siguiente); //aux es igual al id del estado destino y mas adelante el simbolo
                
                if( !auxt.estado_muerte() ){
                    char simbolito = peter[i].simbolo; 
                    char notter=(65 + (auxt.id_)); //Concateno parte izquierda con parte derecha aS|bA
                    string espacio= " ";
                    espacio += simbolito;
                    espacio+=notter;
                    cout << espacio << endl;
                    produc.anadir_part_derech(espacio);
                }
            }
            pepe.anadir_production(produc); //guardo en el vector
        }
    }
    
    pepe.set_nt(nterminal); //añado los no terminales al acabar para mostrarlo en la linea 4 en exportar
    return pepe;
    
    
}
 