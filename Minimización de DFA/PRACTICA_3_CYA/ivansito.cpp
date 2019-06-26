Dfa Dfa::minimizar(bool salida_pantalla){
    set< set<Estado> > PI;
    set< set<Estado> > PI_old;

    //Particion inicial
    set<Estado> acept;
    set<Estado> no_acept;

    for(set<Estado>::iterator i=conjunto_estados.begin(); i!=conjunto_estados.end(); i++){

        if( (i).aceptacion ){
            acept.insert( (i) );
        }else{
            no_acept.insert( (i) );
        }
    }

    PI.insert(acept);
    PI.insert(no_acept);

    if ( salida_pantalla==true ){
    mostrar_Particion(PI);
    }

    do{
        PI_old = PI;
        PI = nueva_particion(PI_old, salida_pantalla);

    }while(PI != PI_old);

    return reconstruir_Dfa(PI);


}

//////////////////////////////
//////////////

//Mostrar particion
void Dfa::mostrar_Particion(set <set<Estado> > sety){
    cout<<"Particion: {";

    for (set< set<Estado> >::iterator iter1 = sety.begin(); iter1!=sety.end(); iter1++){

        cout<<"{";

        for(set<Estado>::iterator iter2 = (iter1).begin(); iter2!=(iter1).end(); iter2++){
            cout << (iter2).numero_estado << " ";
        }

        cout << "} ";
    }
    cout << "}" <<endl;
}


//////////////////////////////
//////////////
//Particionar para todos los simbolos del alfabeto, generando nuevas particiones
set< set<Estado> > Dfa::nueva_particion( set< set<Estado> > PI_old, bool muestra){

    set<char>::iterator itera_Chars;

    for (itera_Chars=alfabeto.begin(); itera_Chars!=alfabeto.end(); itera_Chars++){
        char simbolo = (itera_Chars);

        PI_old = descomponer(PI_old, simbolo);

        if(muestra==true){
            cout<< "Con el simbolo "<<(itera_Chars) << ":" <<endl;
            mostrar_Particion(PI_old);
        }
    }
    return PI_old;
}


//////////////////////////////////
////////////

//Particionar todos los conjuntos de la particion en base a un simbolo
set< set<Estado> > Dfa::descomponer(set< set<Estado> > PI, char a){

    set< set<Estado> > PInew;
    set< set<Estado> >::iterator iter;

        //{{3}, {5, 6, 1, 2}}
    for(iter=PI.begin(); iter!=PI.end(); iter++){

        set< set<Estado> > T = particionar((iter), a, PI);
        PInew.insert(T.begin(), T_.end()); // Voy a meter todos los conjuntos distinguibles que he sacado de particionar

    }
    return PI_new;
}

/////////////////////////////
///////////////

//Particionar un conjunto mediante un simbolo, segun la particion
set< set<Estado> > Dfa::particionar(set<Estado> G, char symbol, set< set<Estado> > PI){
    set< set<Estado> > Particion;


    //Para los conjuntos de PI
    for(set< set<Estado> >::iterator iter1 = PI.begin(); iter1!=PI.end(); iter1++){
        set<Estado> collector;

        //{{3}, {5, 6, 1, 2}}
        
        //Para los estados de G
        for(set<Estado>::iterator iter2 = G.begin(); iter2!=G.end(); iter2++){
            Estado auxIni = (iter2);
            Estado auxNext = Estado( auxIni.get_siguiente(symbol), 0 , 0 );

            set<Estado>::iterator finder = (iter1).find(auxNext); //Va a buscar si hay otra transicion que vaya a otros conjuntos
            if(finder != (iter1).end()){
                collector.insert(auxIni);
            }
        }
        if( !collector.empty() )
            Particion.insert(collector);

    }
    return Particion;

}

////////////////////////////
///////////////


Dfa Dfa::reconstruir_Dfa(set< set<Estado> > PI){
    Dfa aux;
    aux.alfabeto = alfabeto;
    aux.estado_activo = estado_activo;

    int cont = 0; //cont y subcont sirven para cambiarle el nombre a los estados
    //Asi, "numeran" los conjuntos de PI


    set< set<Estado> >::iterator G;
    for(G=PI.begin(); G!=PI.end(); G++){

        set<Estado>::iterator iter;
        //Tomar estado representativo por subconjunto
        iter = (G).begin();
        Estado dummy = (iter);
        dummy.numero_estado = cont;
/*

typedef struct {
  int estado_siguiente;
  char simbolo;
} transicion;
*/
      //Arreglar las transiciones
        transicion* trans = dummy.get_transicion();


        for(int i=0; i<dummy.n_transiciones; i++){
            int next = trans[i].estado_siguiente;
            Estado aux_next (next, 0, 0);

            int sub_cont = 0;
            //Encontrar el conjunto al que pertenece
            set< set<Estado> >::iterator j;
            for(j=PI.begin(); j!=PI.end(); j++){
                set<Estado>::iterator iterSet = (j).find(aux_next);
                if(iterSet != (j).end() ){
                    trans[i].estado_siguiente = sub_cont;
                }
                sub_cont++;
            }

            dummy.setTrans(trans);
        }

        aux.conjunto_estados.insert(dummy);
        cont++;

    }

    return aux;

}