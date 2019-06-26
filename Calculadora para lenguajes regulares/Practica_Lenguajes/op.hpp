/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Clase op.*/


#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include "cadena.cpp"
using namespace std;



class OP{
    
    private:
    
    //Contadores
    int N = 1; 
    int M = 1;
    
    //Mis lenguajes
    string* l1;
    string* l2;
    
    //Conjuntos para las operaciones
	set <cadena> CjtoA;
	set <cadena> CjtoB;
	set <cadena> CjtoC;
	set <cadena> CjtoD;
    
    public:
    
    //Constructores
    OP(); // Operaciones que requieran 2 lenguajes
    OP(int numero); // Operaciones que requieran 1 lenguaje
    
    //Destructor
    ~OP(); 
    
    // Métodos:
    void calculo_n(string todo);
    void calculo_m(string todo2);
    void desglosar_contenido(string todo);
    void desglosar_contenido2(string todo2);
    void formar_conjunto1(void);
    void formar_conjunto2(void);
    void calculo_union(void);
    void calculo_diferencia(void);
    void calculo_interseccion(void);
    void calculo_concatenacion(void);
    void calculo_sublenguaje(void);
    void calculo_igualdad(void);
    void mostrar (set <cadena> Cjto);
    void calculo_potencia(void); // Potencia del lenguaje
    void calculo_inversa(void); // Inversa del lenguaje
    void calculo_cierre_kleene(void); // Cierre de kleene del lenguaje
    
};