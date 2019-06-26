#pragma once

#include <stdio.h> /**< Cabecera necesaria para hacer los procedimientos de entrada y salida. */
#include <iostream> /**< Cabecera necesaria para operaciones de entrada y salida. */
#include <fstream> /**< Cabecera que provee facilidades en la entrada y salida basada en archivos. */
#include <set>  /**< Define las clases de conjunto. */
#include <algorithm> /**< Define una colección de funciones especialmente diseñadas para ser utilizadas en rangos de elementos. */
#include "colores.hpp"
#include "estado.hpp"
using namespace std;


/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	Clase que representa un NFA 
*/


class DFA {

// Atributos privados.

private:
    
    unsigned int Numero_Estados_;  /**< NÃºmero de estados en el NFA. */
    unsigned int Estado_Inicial_; /**< Estado de arranque del NFA. */
    //set <estado_t> Estados_;
    set <char> Alfabeto; /**< Set que contendrá a los símbolos del NFA. */
    set <int> Estados_aceptacion; /**< Set que contendrá a los estados de aceptación. */
    set <int> Estados_no_aceptacion; /**< Set que contendrá a los estados de no aceptación. */
    //set< set<estado_t> > Subconjuntos_;
    estado_t estado_activo; // 
  

// Atributos pÃºblicos.
   
public:
    
    
    
    /**    @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	Cpnstructor de la clase sin parámetros.

*/
    
    DFA();
    
    
    /**    @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	Cpnstructor de la clase

    * @param Fichero que introducimos para realizar sobre Ã©l las opciones del programa. 
    
*/
    
    DFA(char Nombre_Fichero[]);
    
        
 /**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles	Destructor de la clase  
*/


    ~DFA(void);
    
    
    
    set <estado_t> Estados_; /**< Set que contendrÃ¡ a los estados. */
    
    
    //Métodos de la clase:
    
    

    /**    @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que devuelve un conjunto de conjuntos de estados, usado para el proceso de minimizar. Se
	            encarga de recorrer el alfabeto y guardar los simbolos para luego llamar a descomponer.
	
	* @param   Conjunto de conjunto de estados viejo sobre el que voy a ir machacando.
	* @param   Booleano que nos indica si voy a enseñar la traza de minimizar o no junto a la exportación.
*/    
 
     
    set< set<estado_t> > nueva_particion( set< set<estado_t> > PI_viejo, bool ejec );
    
        /**    @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que muestra un conjunto de conjuntos de estados formado.
	
	* @param   Conjunto de conjunto de estados auxiliar.
*/    


    void Mostrar_Particion(set <set<estado_t> > set_aux);
    
    
    

    /**    @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo usaado para cargar un fichero nfa
	
	* @param    Nombre del fichero que se introduce para poder realizar las opciones del programa en base a ese archivo.
	
*/
    void Cargar_DFA(char Nombre_Fichero[]);
    
    
    
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que muestra todo el contenido deducible de un fichero.nfa
*/

    void Mostrar_infor_DFA(void);
 
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fehca 		22 de octubre de 2017

	@detalles 	MÃ©todo que se encarga de saber si una cadena introducida por teclado es aceptada o no.
*/
    void Analizar_Cadena(void);
    
    
        

    /** 
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que comprueba si los sÃ­mbolos de la cadena estÃ¡ dentro del set alfabeto.
	
	
	* @return Resultado de realizar la comparaciÃ³n.
	* @retval TRUE  Indica que el sÃ­mbolo sÃ­ coincide con los sÃ­mbolos del alfabeto.
	* @retval FALSE  Indica que el sÃ­mbolo no coincide con los sÃ­mbolos del alfabeto.
	
	* @param Cadena que se introduce por teclado y con la que comprobaremos si los sÃ­mbolos pertenecen al conjunto alfabeto.
	 
*/
    bool verificar_simbolos(char *Cadena);
    
    /**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que muestra el contenido del set alfabeto
*/

    void mostrar_alfabeto();
    
        
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que comprueba con la ayuda de la funciÃ³n "estado_muerte" si el estado es un estado de muerte.
*/
    void detectar_muerte(void);
    
    
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que inserta en un set los sÃ­mbolos del alfabeto
*/

    void alfabetizando();

    
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que exporta los datos nuevos de minimizar en un fichero.
*/

    void Exportar_DFA();
    
        
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	Método que divide el conjunto de estados en 2: Estados de aceptacion 
	y Estados de no aceptacion. Luego llama a nueva partición para realizar las demás particiones segun el comportamiento de las transiciones.
    
    @param Booleano que modificaremos para mostrar la traza o no mostrarla.

*/

    DFA Minimizar_DFA(bool muestra_Ejecucion);
    
    
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que inserta en un set los sÃ­mbolos del alfabeto
	@param 
*/

    set< set<estado_t> > reconstruir_Dfa(set< set<estado_t> > Subconjuntos);
    
    
       
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	MÃ©todo que se encarga de recorrer el subconjunto y llamar a particionar para guardar el resultado en Temp
    @param Conjunto de conjunto de estados principal que contiene a todos los conjuntos.
    @param Char que contiene el caracter que vamos a evaluar para ver si la transición se dirige hacia otro conjunto.
*/

    
    set< set<estado_t> > descomponer(set< set<estado_t> > Subconjuntos, char a);
    
/**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		22 de octubre de 2017

	@detalles 	Método que se encarga de comprobar si las transiciones de un estado de un conjunto se dirige con un simbolo a otro estado de otro conjunto.
	            Si esto es así, se introduce en otro conjunto.
	            
    @param Conjunto de estados a los que voy a enumerar y a comprobar
    @param Char que contiene el caracter que vamos a evaluar para ver si la transición se dirige hacia otro conjunto.
    @param Conjunto de conjunto de estados principal que contiene a todos los conjuntos
*/

    
    set< set<estado_t> > particionar(set<estado_t> G, char symbol, set< set<estado_t> > Subconjuntos );
   
   
   /**
        @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		22 de octubre de 2017

	@detalles 	Método que se encarga de colocar bien el resultado una vez hecho la traza.
	            
    @param Conjunto de conjunto de estados principal que contiene a todos los conjuntos
*/

   
   
    DFA reconstruir_DFA(set< set<estado_t> > Subconjuntos);
    

    
    
};