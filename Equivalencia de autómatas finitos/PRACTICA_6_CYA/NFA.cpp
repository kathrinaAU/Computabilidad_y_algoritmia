#include "NFA.hpp"
#include <cstring>
#include <pthread.h>
#include <unistd.h>

#include "colores.hpp"
#define NAME_SIZE 50

NFA::NFA(void){
    
}

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

//////////////////////////////////////
//////////////////////////////////////

set<unsigned int> NFA::e_clausura( set<unsigned int> temp ){

    set<unsigned int> aux;
    aux = temp;

    
    for(set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){

    unsigned int numerito = (*i).id_;

   // cout << " El numerito es " << numerito << endl;

        if( temp.find( numerito ) != temp.end() ){
    
  //  cout << " El numerito pitas " << numerito << endl;
    
            for(int l=0; l < (*i).Transiciones_; l++){
                if((*i).Simbolo_[l] == '~'){
                    aux.insert( (*i).Destino_[l]  );
                    temp.insert( (*i).Destino_[l]  );
                }
            }
            
            temp.erase( numerito );
            e_clausura(temp);
           
  
        }
    }    
    return aux;
}


    
set<unsigned int> NFA:: trans_Simbolo( set<unsigned int> temp, char simbolito ){

  set<unsigned int> aux;
  //aux = temp; 
  
    for(set<estado_t>::iterator i = Estados_.begin(); i != Estados_.end(); i++){
//    cout << "Petas" << endl;
    unsigned int numerito = (*i).id_;

        if( temp.find( numerito ) != temp.end() ){
 //cout << "Petas 1" << endl;
            for(int l=0; l < (*i).Transiciones_; l++){
// cout << "Petas 2" << endl;
                if( (*i).Simbolo_[l] == simbolito ){
// cout << "Petas 3" << endl;
                    aux.insert( (*i).Destino_[l]   );
                    temp.insert( (*i).Destino_[l]  );

                }else if((*i).Simbolo_[l] == '~' ){
 //cout << "Petas 4" << endl;
                    set <unsigned int> patos;
                    set <unsigned int> coso;
                    
                    coso.insert( numerito );
                    patos = e_clausura( coso );
                    
                    for(set<unsigned int>::iterator iter = patos.begin(); iter != patos.end(); iter++){
                     //    cout << "Petas 5" << endl;
                        temp.insert( (*iter) );
                    }
                }
            }
            
            temp.erase( numerito );
            trans_Simbolo(temp , simbolito);
            
        }
    
    }

    return aux;
}


DFA NFA::convert2DFA(){
    
    
    set<char> Alfabetizate;

    Alfabetizate = Alfabeto;
    Alfabetizate.erase('~');

    
    DFA logic;
    
    //Variables
    set<unsigned int> inicio;
    set<unsigned int> nada;
    
    set<unsigned int> temp2;
    vector <int> conjuntitos;
    
    set<unsigned int> temp3;
    vector <unsigned int> conjuntitos2;

    
   unsigned int contador_id = 0;
   vector <int> contador_estados; 
   
///////////////////////////////
   
    inicio.insert( Estado_Inicial_ );

    temp2 = e_clausura( inicio );
    
    
     ///Mostrar
    ////////////////////////////////////////////////////////////////////////////////
      cout << "El conjunto e-clausura contiene:  " << endl;  
    
    for(set<unsigned int>::iterator lol = temp2.begin(); lol != temp2.end(); lol++){
        cout << (*lol) << " ";
    }
        cout << endl;
    ////////////////////////////////////////////////////////////////////////////////
    
    for(set<unsigned int>::iterator k = temp2.begin(); k != temp2.end(); k++){   
        conjuntitos.push_back( (*k) );
    }
    
    for(int o = 0; o < conjuntitos.size(); o++){
        nada.insert( conjuntitos[o] );
    }

    conjuntitos.push_back( -1 );
    contador_estados.push_back( 0 );
    
    
    // for (int h = 0; h <= )
    // int counter = conjuntitos.size();
    // counter = counter * (alfabeto.size()-1);
    
    int sub_contador = 1;
    int contador2 = 0;
    
    do{
    
    for(set<char>::iterator z = Alfabeto.begin(); z != Alfabeto.end(); z++){
        
        set<unsigned int> temp4;  
        //Eliminamos los epsilon
        if( (*z) != '~' ){
             cout << "Haciendo trans " << endl;
            for(set<unsigned int>::iterator w = nada.begin(); w != nada.end(); w++){
                cout << "Nada contiene: " << (*w) <<endl;
            }
            cout << "Zeta contiene: " << (*z) <<endl;
            
            temp4 = trans_Simbolo(nada, (*z) );
            cout << "Finaliza trans" << endl;  
    
            cout << "El conjunto trans contiene:  " << endl;  
    
            for(set<unsigned int>::iterator k = temp4.begin(); k != temp4.end(); k++){
                cout << (*k) << " ";
            }
            cout << endl;
    
            for(set<unsigned int>::iterator l = temp4.begin(); l != temp4.end(); l++){   
                conjuntitos2.push_back( (*l) );
            }
            
        
        
    
    ////////////////////////////////////////////////////////
    //FOR o NO FOR??
        
            //Variables
    /////////////////////////////////////////////////////
    set<unsigned int> temp5;
    nada.clear();
    temp5 = e_clausura( temp4 );
    
    //Comparar que no exista el conjunto ya
    vector <int> temporal1;
    vector <int> temporal2;
    int diferente = 0;
    ///////////////////////////////////////////////////////
    
    
    ///Mostrar
    //////////////////////////////////////////////////////////////////////////////////
    cout << "El conjunto e-clausura contiene:  " << endl;  
    
    for(set<unsigned int>::iterator lol = temp5.begin(); lol != temp5.end(); lol++){
        cout << (*lol) << " ";
    }
    cout << endl;
    //////////////////////////////////////////////////////////////////////////////////
    
    
    for(set<unsigned int>::iterator k = temp5.begin(); k != temp5.end(); k++){   
       temporal2.push_back( (*k) );
    }


    for(int u = 0; u < conjuntitos.size(); u++){
        
   //     cout << "Se hace un nuevo conjunto" << endl;
       // cout << conjuntitos[u] <<endl;
        
        if( conjuntitos[u] != -1 ){
            temporal1.push_back( conjuntitos[u] );
            //for (int y=0; y<temporal1.size(); y++){
               // cout << "TEMPORAL 1: " << temporal1[y] <<endl;
            //}
        }else{
            if( temporal1 != temporal2 ){
                diferente++;
                //cout << "diferente: " << endl;
                temporal1.clear();
            }
        }
    }
    
    
    
    
    if( diferente == contador_estados.size() ){
        
          cout << "Nuevo conjunto" << endl;
        conjuntitos.push_back( -1 );
        contador_estados.push_back( sub_contador );
        
        //for (int y=0; y<contador_estados.size(); y++){
        //    cout << "contador_estados: " <<contador_estados[y] <<endl;
        //} 
            
        for(set<unsigned int>::iterator k = temp5.begin(); k != temp5.end(); k++){  
            //cout << "Nuevos estados del conjunto: " << (*k) <<endl;
            conjuntitos.push_back( (*k) );
        }
        cout << "flipa 1 " <<endl;
        
         contador_id++;
         sub_contador++;
        cout << "flipa 2 " <<endl;
    }
    
    //for(int o = 0; o < conjuntitos.size(); o++){
    //    nada.insert( conjuntitos[o] );
    //}

    nada = temp5;
    cout << "flipa 3 " <<endl;
        ////////////////////////////////////////////////////////////////////
        //CIERRE FOR o NO FOR?
        ////////////////////////////////////////////////////////
        }
    }

    
    
    
    contador2++;
    cout << "flipa 4 " <<endl;
    getchar();
   
    }while( 1);//contador2 < ( contador_id * Alfabetizate.size() ) );
   
   return logic;
}

























































































 ////////////////////////////////////////////////////////////////////////////////////////////////7
 /////////////////////////////////////////////////////////////////////////////////////////////////
 /*
set<estado_t>::iterator NFA::buscarEstado(const unsigned int id){
    auto ini=Estados_.begin();
    auto fin=Estados_.end();
    auto resultado=fin;
    bool encontrado=false;
    
    for(ini; ini != fin and encontrado; ini++){
        if(ini->id_ == id){
            resultado = ini;
            encontrado = true;
        }
    }
    
    return resultado;
}


set<unsigned int> NFA::e_clausura(set<unsigned int> &est){
    set<unsigned int> resultado,aux;
    
    for(auto i=est.begin(); i != est.end(); i++){
        auto estado = buscarEstado((*i));
        if(estado != Estados_.end()){
            aux = e_clausura(*estado);
            resultado.insert(aux.begin(),aux.end());
        }
        
        aux.clear();
    }
    
    return resultado;
    
}



set<unsigned int> NFA::e_clausura(const estado_t &e){
    set<unsigned int> resultado, aux2;
    set<estado_t> aux;
    resultado.insert(e.id_);
    
    for(auto i=0; i < e.Transiciones_;i++){
        if(e.Simbolo_[i] == '~')
            aux.insert(*buscarEstado(e.Destino_[i]) );
    }
    
    for(auto i=aux.begin(); i != aux.end() ;i++){
        aux2 = e_clausura(*i);
        resultado.insert(aux2.begin(), aux2.end());
    }
    
    
   return resultado;
}


set<unsigned int> NFA:: trans_Simbolo( set<unsigned int> temp, char simbolito ){
    set<unsigned int> resultado;
    
    for(auto i=temp.begin(); i != temp.end(); i++){
        auto est = (*buscarEstado(*i));
        
        for(auto j=0; j < est.Transiciones_; j++){
            if(est.Simbolo_[j] == simbolito)
                resultado.insert(est.Destino_[j]);
        }
    }
    
    return resultado;
}



DFA NFA::convert2DFA(){
    DFA dfa_resultado;
    vector<pair<estado_t,bool> >estadosDFA;
    set<pair<unsigned int, set<unsigned int> > >aux;
    id_ini = 0;
    int *trans;
    char *simb;
    bool existe = false;
    
    auto primerEstado = e_clausura( *Estados_.begin() ); // set unsigned int.
    estado_t e(id_ini,false,0,-1,-1);
    estadosDFA.push_back(std::pair<estado_t,bool>(e,true));
    aux.insert(pair<unsigned int,set<unsigned int> >(id_ini,primerEstado) );
    
    
    for(auto i=estadosDFA.begin(); i != estadosDFA.end(); i++){
        if(i->second){
            for(auto j=Alfabeto.begin(); j != Alfabeto.end(); j++){
                auto h = e_clausura(trans_Simbolo(primerEstado,(*j)));
                // Comprobación de que no esté incluido.
                for(auto k=aux.begin(); k != aux.end() and !existe; k++){
                    if(k->second == h ){
                        existe = true;
                    }
                }
                
                if(!existe){
                    id_ini ++;
                    // Insertar nuevo en estados.
                }
                
                // Aumentar trans y simb.
                
            }
        }
    }
    
}  */
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
    
   