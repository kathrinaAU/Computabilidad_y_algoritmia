#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include "colores.hpp"
#include "estado.hpp"
using namespace std;
class DFA {

private:
    
    unsigned int Numero_Estados_;
    unsigned int Estado_Inicial_;
    set <estado_t> Estados_;
    

public:
    //Constructor:
    DFA(char Nombre_Fichero[]);
    //Destructor
    ~DFA(void);
    
    //Métodos de la clase:
    
    void Cargar_DFA(char Nombre_Fichero[]);
    void Mostrar_infor_DFA(void);
    void Estados_de_Muerte(void);
    void Analizar_Cadena(void);
    
};