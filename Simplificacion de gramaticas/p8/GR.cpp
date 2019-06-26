#include "GR.hpp"

#define S 83
#define A 65
#define B 66

////////////////////////////////////////////////////////////////////////////////

Gramatica::Gramatica(char Nombre_Fichero_grammar[])
{
    cargar_gramatica(Nombre_Fichero_grammar);
}


//////////////////////////////////////////////////////////////////////////////////////


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



void Gramatica::cargar_gramatica(char Nombre_Fichero_grammar[]){
    ifstream in;

    //Declaramos los datos que podemos encontrar en el fichero
    int simbolos_terminales;
    set <char> alfabeto_no_terminales;
    set <char> set_simbolos_terminales;
    int num_no_terminales;
    char letra;
    string produccion;
    string p_dch;
    Produccion aux;
    int pos_i, pos_f;

    cout << Nombre_Fichero_grammar << endl;


    in.open(Nombre_Fichero_grammar, std::fstream::in );
    cout << "Abriendo el archivo" << endl;

    if (in.is_open()){

        in >> (int &) simbolos_terminales;

        for (int i=0; i < simbolos_terminales; i++){
            in >> letra;
            set_simbolos_terminales.insert(letra);
        }

        terminal = set_simbolos_terminales;

        cout << "sÃ­mbolos no terminales leidos" << endl;

        in >> (int &) num_no_terminales;

        for (int i=0; i < num_no_terminales; i++){
            in >> letra;
            alfabeto_no_terminales.insert(letra);
        }

        no_terminal = alfabeto_no_terminales;

        cout << "sÃ­mbolos terminales leidos" << endl;

        in.ignore();


        // Leer producciones.
        while(std::getline(in,produccion) and !produccion.empty()){
            letra = produccion[0];
            cout << "Produccion: " << produccion << endl;

            aux.set_part_izq(letra);

            pos_i = pos_f = 6;

            for(auto i=6; i < produccion.size() ; i++){
                cout << produccion[i] << ' ' << i << endl;
                if(produccion[i] == '|'){
                    cout << "encontrado | en pos" << i << endl;
                    cout << pos_i << ' ' << i << endl;
                    cout << produccion.substr(pos_i, i-pos_i) << endl;
					cout << i-pos_i << endl;
                    p_dch.append(produccion,pos_i,i-pos_i);
                    aux.anadir_part_derech(p_dch);
                    p_dch.clear();

                    pos_i = i+1;
                }
            }

            cout << pos_i << pos_f << endl;

            p_dch.append(produccion,pos_i,produccion.size());
            aux.anadir_part_derech(p_dch);
            p_dch.clear();
            production.push_back(aux);


            aux.limpiarParteDerecha();

        }

        cout << production.size() << endl;


    }else{
        cout << "No se ha podido abrir el archivo " << endl;
        exit(-1);
    }
    in.close();

    cout << "producciones leidas" << endl;
}



void Gramatica::anadir_production(Produccion prod){
	production.push_back(prod); //Introduzco el prod en el vector
}


////////////////////////////////////////////////////////////////////////////////

void Gramatica::set_nt(set<char> n){
 no_terminal = n; // Igualar un no terminal a otro
}

////////////////////////////////////////////////////////////////////////////////

void Gramatica::exportar(){

   char fich[50] = "tmp2.grm";
 //  cout << "Intrduzca el fichero a exportar (.grm): " << endl;
 //  cin >> fich; //Fichero en donde guardo la gramÃ¡tica

   ofstream file;
   file.open(fich); //Abrimos el fichero

   if (file.is_open()){ //Si el fichero se abre
      file << terminal.size() << endl; // Introducimos primera linea al fichero: LÃ­nea 1: nÃºmero total de sÃ­mbolos terminales que posee la gramÃ¡tica.

     	set<char>::iterator alfa; // Iterador para recorrer el alfabeto y meterlo en el fichero.

     	for (alfa=terminal.begin(); alfa!=terminal.end(); alfa++){ //Recorremos el alfabeto y metemos cada simbolo
     		   file << (*alfa) << " "; // Introducimos segunda lÃ­nea al fichero. LÃ­nea 2: lista de todos los sÃ­mbolos terminales de la gramÃ¡tica,
     	                            //separados por espacios en blanco. Cada terminal se representa mediante un caracter ASCII.

     	}

     	file << endl;
     	file << no_terminal.size() << endl; //LÃ­nea 3: nÃºmero total de sÃ­mbolos no terminales que posee la gramÃ¡tica.


     	set<char>::iterator NT; // Iterador para recorrer el set de los no terminales
     	NT=no_terminal.end();
     	--NT;
     	file << (*NT) << ' ';
     	for (NT=no_terminal.begin(); NT!=--no_terminal.end(); NT++){
     		   file << (*NT) << " "; //LÃ­nea 4: lista de todos los sÃ­mbolos no terminales de la gramÃ¡tica, separados por espacios en blanco.
     		                        //Cada sÃ­mbolo no terminal vendrÃ¡ representado tambiÃ©n mediante un caracter ASCII, preferiblemente letras
     		                        //mayÃºsculas de nuestro abecedario. Se tomarÃ¡ como sÃ­mbolo de arranque de la gramÃ¡tica aquel sÃ­mbolo no
     		                        //terminal que aparezca primero en esta lista.
     }

      file << endl;

      for(int i=0; i<production.size(); i++){
            cout << production[i].get_part_izq() << endl;
         	file << production[i].get_part_izq() << " " << "-> "; //De la lÃ­nea 5 en adelante el fichero tendrÃ¡ una lÃ­nea para cada uno
         	                                                     //de los sÃ­mbolos no terminales de la gramÃ¡tica. En cada lÃ­nea se especificarÃ¡n
         	                                                     //las reglas de producciÃ³n de un determinado sÃ­mbolo no terminal.
         	set<string> dummy=production[i].get_part_derech();


      	for(auto i=dummy.begin() ; i != dummy.end() ; i++){
      	    cout << (*i) << " " ;
      		  file << (*i);
      		  if(i != --dummy.end() )
      		    file << "|";

      	}
      	cout << endl;

      	file << endl;
      	}

      	file << endl;
      	file.close();

  }

}

/////////////////////////////////////////////////////////////////////////////
    void Gramatica::busqueda_eps(set<char> &eps){

        for (int i = 0; i < production.size(); i++){
            set<string> p_dch = production[i].get_part_derech();
            if(p_dch.find("~") != p_dch.end() )
                eps.insert(production[i].get_part_izq() );
        }
    }



////////////////////////////////////////////////////////////////////////////////
void Gramatica::busqueda_anulables(set<char> &anull) {

    bool anadido_nuevo = true;
    bool anadir = true;
    bool anadido = false;
	  set<char> anadidos;
    while(anadido_nuevo){
        anadido_nuevo = false;

        for (auto i = 0; i < production.size(); i++) { //Recorro las producciones
            auto prods = production[i].get_part_derech(); //Me quedo con la parte derecha
            anadido = false;

            for (auto j = prods.begin(); j != prods.end() and !anadido; j++) { //Recorro las partes derechas
                string cadena = (*j);
                anadir = true;

                for(auto k=anull.begin(); k != anull.end() ; k++){ //Recorro el set que me pasan por parametro
                    if(cadena.find((*k)) == string::npos ){ // Si no la encuentra a anull en las pates derechas
                        anadir = false;
					          }
                }

        				if(anadidos.find(production[i].get_part_izq() ) != anadidos.end() ){ // Si encuentra la parte izquierda en los añadidos
        					anadir = false;
        				}

                if(anadir){ // SI encuentra la part izquierda
                    anadidos.insert(production[i].get_part_izq()); //Inserto la parte izquierda
                    anadido = true;
                    anadido_nuevo = true;
				         }
            }
        }
    }
	anull.insert(anadidos.begin(), anadidos.end()); // Inserto anadidos en anul
}


////////////////////////////////////////////////////////////////////////////////
void Gramatica::eliminarVacios() {
    // Detectamos aquella variables que son anulables.
    set<char> anulables;
    busqueda_eps(anulables);

    // Eliminamos producciones que van a lambda directamente.
    for (auto i=anulables.begin(); i != anulables.end(); i++) {
          auto prod = searchProduction(*i);
  		    auto pd = prod->get_part_derech();
		      pd.erase("~");
		      prod->set_part_derech(pd);
    }

    busqueda_anulables(anulables);

    // Por cada uno de los elementos del set, eliminamos esas transiciones y metemos transiciones nuevas equivalentes.
    set<string> nuevas;
    for(auto anulable=anulables.begin(); anulable != anulables.end(); anulable++){ //Recorro el set de anulables
         auto parteDerecha = searchProduction(*anulable)->get_part_derech();
		     string p_izq(1,searchProduction(*anulable)->get_part_izq()); //busca las posibilidades de cada una de las producciones
         // que están afectadas por los anulables
         for(auto simbolos=parteDerecha.begin(); simbolos != parteDerecha.end(); simbolos++ ){
              addPosibilities((*simbolos),anulables,nuevas,p_izq );
			        cout << "Posibilidades encontrada" << endl;
         }
		     parteDerecha.insert(nuevas.begin(), nuevas.end());
         searchProduction((*anulable))->set_part_derech(parteDerecha);
    }
}
////////////////////////////////////////////////////////////////////////////////
Produccion * Gramatica::searchProduction(char p_izq) {

    // Recorremos las producciones hasta que la encontremos.
    for(auto i=0; i < production.size(); i++)
        if(production[i].get_part_izq() == p_izq)
            return &production[i];

}

//////////////////////////////////////////////////////////////////////////////////////////////
void Gramatica::addPosibilities(string p_dcha, set<char> &anull, set<string> &nuevas, string p_izq) {
    string nueva;
    int pos = 0;
	  //cout << "Size " << p_dcha.size() << endl;
    // Recorremos los valores anulables.
    for(auto an = anull.begin(); an != anull.end(); an++){ //Recorro el set de anull
  		pos = 0;
  		//cout << "buscando letra: " << *an <<endl;
  		//cout << "nuestra parte derecha es: " << p_dcha << endl;
  		//cout << pos << endl;
  		if(p_dcha.size() > 1){
  			pos = posicionEnProduccion(p_dcha,pos,*an); //posicion de an
  			//cout << "Posicin encontrada:" << pos << endl;
  		    if( pos != -1 ){
  				cout << "comprobando si es un simbolo no terminal" << endl;

  				if(p_dcha[pos] >=65 and p_dcha[pos] <= 91 ){
  					//cout << "letra encontrada, eliminandola para crear nueva produccin" << endl;
  				    nueva = p_dcha;
  				    nueva.erase(pos,1); //  void erase (iterator first, iterator last);
  					  nuevas.insert(nueva);
  				    addPosibilities(nueva, anull, nuevas, p_izq); //Vuelvo a llamar al metodo para que lo haga con la siguiente no terminal
				  }
  		    }else{
  				//cout << "letra no encontrada" << endl;
  			}
  		}else{
            if(p_dcha[0] == (*an) ){
				         if(p_izq == "S" )
					            nuevas.insert("~");
			     }
		   }

    }
}

////////////////////////////////////////////////////////////////////////7
int Gramatica::posicionEnProduccion(string prod, unsigned int pos, char letra){
	int pos_R = -1;

	for(auto i=pos; i < prod.size(); i++){ //Recorro lasproducciones
		if(prod[i] == letra)
			pos_R = i;
	}

	return pos_R;
}



////////////////////////////////////////////////////////////////////////////////
//Producciones unitarias
void Gramatica::encontrandoParejas() {
    set<pair<char,char> > parejas;
     //Tengo que coger la produccion entera y buscar si en la parte derecha hay un solo no terminal en su produccion.
    for (int i = 0; i < production.size(); i++){

        for(auto j = no_terminal.begin(); j !=  no_terminal.end(); j++){
            set<string> p_dch = production[i].get_part_derech();
            string n_t(1,*j);
			cout << n_t << endl;
            if( p_dch.find(n_t)  != p_dch.end()  ){

                parejas.insert(pair<char,char>(production[i].get_part_izq(),*j));

            }
        }
    }


    bool cambio = true;

    while(cambio) {
        cambio = false;
        for (auto k = parejas.begin(); k != parejas.end(); k++) {
            //Recorro el set de parejas y busco si tengo guardada alguna pareja en la que el segundo sea igual al primero de otra pareja.
            for (auto j = parejas.begin(); j != parejas.end(); j++){

                if (k->second == j->first) {
                    auto r = parejas.insert(pair<char, char>(k->first, j->second));
                    if(r.second){cambio = true;}
                }
			}
        }
    }


    //Intercambiar en las parejas,en la parte izquierda inserto las producciones de la parte derecha
	bool uni = false;
    for(auto i= parejas.begin(); i != parejas.end(); i++){

        auto prodDerecha = searchProduction(i->second);
        auto prodIzquierda = searchProduction(i->first);

        auto parteDerecha = prodIzquierda->get_part_derech();
		auto pDD = prodDerecha->get_part_derech();
		cout << "fallo" << endl;
		for(auto i=pDD.begin(); i != pDD.end() ; i++){
			cout << *i << endl;
			uni = false;
			for(auto j=no_terminal.begin(); j != no_terminal.end() and !uni; j++){			cout << *j << endl;
				string aux(1,*j);
				cout << aux << endl;
				if( aux == *i){
					uni = true;
					cout << "es unitario" << endl;
				}
			}

			if(!uni)
				parteDerecha.insert(*i);
		}


		cout << "fallo 2" << endl;

        prodIzquierda->set_part_derech(parteDerecha);
    }

}



////////////////////////////////////////////////////////////////////////
    void Gramatica::exportar_renombrar (void){

        char fich[30];
        string nombre = "tmp.grm";

        fstream file;
        file.open(nombre);

        cout << endl<< "Introduzca el fichero a exportar (.grm): " << endl;
        cin >> fich; //Fichero en donde guardo la gramÃ¡tica

        ofstream file2;
        file2.open(fich);

        char aux, letra, letra2, inicial;



        if ( ( file.is_open() ) && ( file2.is_open() ) ){

        do{
            file >> aux;
            int cont = 0;
            letra = 66; //B
            letra2 = 65; //A

                for ( int i = 0; i < 25 ; i++){

                    if (aux == 'A'){
                        file2 << 'S'<<' ';
                        break;
                    }else if( aux == letra ){
                        file2 << letra2<<' ';
                        break;
                    }else{
                        cont++;
                    }

                    letra++;
                    letra2++;
                }

                if(cont == 25){
                    file2 << aux<<' ';
                }

            }while( !file.eof() );
        }

        file.close();
        file2.close();
       // system("rm tmp.grm");

    }
