#include <stdio.h>  /**< Cabecera necesaria para hacer los procedimientos de entrada y salida. */
#include <iostream> /**< Cabecera necesaria para operaciones de entrada y salida. */

using namespace std;

  /**      \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles	Clase que representa a estado. */


class estado_t {
    
    
    


    /**    \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Se utiliza para poder usar la sobrecarga del operador cout.
	
	    * @param    os Referencia del flujo de salida. 
	    * @param    x Referencia constante al estado.
	    * @return   Referencia del flujo de salida. */
 
 
    friend std::ostream &operator<<(std::ostream &, const estado_t &); 
    
    


// Atributos pÃºblicoss.

   
public:
    
    unsigned int id_;           /**< Entero que identifica al estado del NFA */
    bool Aceptado_;             /**< Booleano que identifica si el estado es de aceptaciÃ³n  */      
    unsigned int Transiciones_; /**< Entero sin signo que identifica el nÃºmero de transiciones por estado */
    char *Simbolo_;             /**< Char * que se utiliza para guardar los simbolos del NFA      */
    int *Destino_;              /**< Entero * que se utiliza para guardar el destino de los estados del NFA.    */



/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Constructor por defecto de la clase
*/   
  
    estado_t();
    


    /**    \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles   Constructor por parÃ¡metros de la clase
	
	* @param    int identificador
	* @param    bool aceptado
	* @param    int Transiciones_
	* @param    char * Simbolo_
	* @param    int * Destino_
	*/	

    
    estado_t(int, bool, int, char*, int*);
    
    
    
/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Constructor con parÃ¡metro de la clase*/

   
    estado_t(const estado_t &);
  
    

/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	FunciÃ³n que devuelve si el estado es un estado de muerte.
	
	* @return  Indica el resultado de la comparaciÃ³n
	* @retval TRUE Indica que es un estado de muerte
	* @retval FALSE Indica que no es un estado de muerte.

*/
  
    bool estado_muerte();
  
    

/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Destructor virtual de la clase
*/
  
    virtual ~estado_t(void);




      /**  \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha		16 de octubre de 2017

	\detalles 	Sobrecarga de operador igual (=) 
	
	* @param    x Referencia constante del estado.
	* @return   Referencia del estado llamante.
	
*/

    estado_t &operator=(const estado_t &rhs);
    


/**
        \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Sobrecarga del operador para comparar igualdad, que retorna un entero que indica si el
	            identificador del estado.
    
    * @param    rhs Entero constante que comparamos con el identificador del estado
    * @return   El resultado de la comparaciÃ³n.
    * @retval 1 El entero constante coincide con el identificador del estado.
    * @ retval 0 El entero constante no coincide con el identificador del estado.
    
*/
   
    int operator==(const estado_t &rhs) const;
    
    


   /**     \autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        \fecha 		16 de octubre de 2017

	\detalles 	Sobrecarga del operador para comparar si es menor, retorn un booleano que indica si el estado
	llamante constante es menor que el pasado por referencia constante.
	
	* @param x Referencia constante del estado.
    * @return 	El resultado de la comparaciÃƒÆ’Ã‚Â³n.
    * @retval  1  El estado llamante constante es menor que el estado pasado por referencia constante.
    * @retval  0  El estado llamante constante no es menor que el estado pasado por referencia constante.

	
*/

    int operator<(const estado_t &rhs) const;

};
