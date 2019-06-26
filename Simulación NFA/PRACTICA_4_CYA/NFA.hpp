#pragma once

#include <stdio.h>  /**< Cabecera necesaria para hacer los procedimientos de entrada y salida. */
#include <iostream>  /**< Cabecera necesaria para operaciones de entrada y salida. */
#include <fstream>  /**< Cabecera que provee facilidades en la entrada y salida basada en archivos. */
#include <set>  /**< Define las clases de conjunto. */
#include <algorithm>  /**< Define una colección de funciones especialmente diseñadas para ser utilizadas en rangos de elementos. */
#include <vector>  /**< Cabecera para poder usar las funciones típicas de vectores */
#include <string> /**<Es un archivo de la Biblioteca estándar del lenguaje de programación C que contiene la definición de macros, constantes, funciones y tipos y algunas operaciones de manipulación de memoria.*/
#include <sstream> /** */

#include "colores.hpp" 
#include "estado.hpp"


using namespace std;


/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Clase que representa un NFA 
*/

class NFA {
    



// Atributos privados.


private:
    
    unsigned int Numero_Estados_; /**< NÃºmero de estados en el NFA. */
    unsigned int Estado_Inicial_; /**< Estado de arranque del NFA. */
    set <estado_t> Estados_; /**< Set que contendrÃ¡ a los estados. */
    set <char> Alfabeto; /**< Set que contendrÃ¡ a los sÃ­mbolos del NFA. */
    set <int> Estados_importantes; /**< Set que contendrÃ¡ los estados en los que cuyas transiciones sean distinto de ~ y que contendrÃ¡ estados de aceptaciÃ³n. */
    set <int> Estados_no_importantes; /**< Set que contendrÃ¡ a aquellos estados en las que sus transiciones salientes son ~ o se trata de un estado de aceptaciÃ³n. */




// Atributos pÃºblicos.



public:


    /**    \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Cpnstructor de la clase

    * @param Fichero que introducimos para realizar sobre Ã©l las opciones del programa. 
    
*/
    
    NFA(char Nombre_Fichero[]);
    
   
    
 /**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles	Destructor de la clase  
*/
    
    ~NFA(void);
    
    
 
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha		16 de octubre de 2017

	\detalles 	MÃ©todo que comprueba dado un NFA, si puede ser un dfa. Se basa en comprobar si el DFA tiene una y sola una transiciÃ³n, desde cada estado, 
para cada uno de los sÃ­mbolos del alfabeto. 
*/
    
        void comprobar_nfa(void);
    
    
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que comprueba que estados son importantes en base a los sÃ­mbolos de sus transiciones y los introduce en un set.  Decimos que 
	un estado es importante si tiene al menos una transiciÃ³n saliente etiquetada con uno de los sÃ­mbolos del alfabeto, o bien, si es un estado
    de aceptaciÃ³n. 
*/

    void estados_no_importantes(void);
    
   
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que comprueba que estados no son importantes en base a los sÃ­mbolos de sus transiciones. Es decir, los estados no importantes 
	serÃ¡n aquellos que no son de aceptaciÃ³n y sÃ³lo tienen transiciones salientes etiquetadas con epsilon
*/

    void estados_importantes(void);
    
   
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que inserta en un set los sÃ­mbolos del alfabeto
*/

    void alfabetizando();
    
    
    
/**
    /**    \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo usaado para cargar un fichero nfa
	
	* @param    Nombre del fichero que se introduce para poder realizar las opciones del programa en base a ese archivo.
	
*/

    void Cargar_NFA(char Nombre_Fichero[]);
    
    
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que muestra todo el contenido deducible de un fichero.nfa
*/
    void Mostrar_infor_NFA(void);
    
    
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que comprueba con la ayuda de la funciÃ³n "estado_muerte" si el estado es un estado de muerte.
*/

    void detectar_muerte(void);
   
   

/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fehca 		16 de octubre de 2017

	\detalles 	MÃ©todo que se encarga de saber si una cadena introducida por teclado es aceptada o no.
*/
   
    void Analizar_Cadena(void);
   
   
 /** 
	 		\autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
	        
	        \fehca 		16 de octubre de 2017
	
		\detalles 	MÃ©todo recursivo del analizar cadena para comprobar cada uno de los caminos posibles dadas las transiciones del estado.
		
		* @param	char cadena que introducimos por teclado.
		* @param	vector Guardaremos los caminos que hemos recorrido en el vector.
		* @param	int Entero que indica el siguiente estado.
		* @param	int Entero que nos indica la posición por la que vamos de la cadena.
		* @param	bool que nos indica si la cadena es aceptada o no.
 
 */ 
    
        
     void Analizar_Cadena_R(char cadena[], vector<string> Camino, int Next_State,int num_cadena, bool &Acepatda);
    

/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que muestra el contenido del set alfabeto
*/
   
    void mostrar_alfabeto();
   
    

    /** 
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	MÃ©todo que comprueba si los sÃ­mbolos de la cadena estÃ¡ dentro del set alfabeto.
	
	
	* @return Resultado de realizar la comparaciÃ³n.
	* @retval TRUE  Indica que el sÃ­mbolo sÃ­ coincide con los sÃ­mbolos del alfabeto.
	* @retval FALSE  Indica que el sÃ­mbolo no coincide con los sÃ­mbolos del alfabeto.
	
	* @param Cadena que se introduce por teclado y con la que comprobaremos si los sÃ­mbolos pertenecen al conjunto alfabeto.
	 
*/

    bool verificar_simbolos(char *Cadena);
    
    
    
};