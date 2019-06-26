#ifndef MONEDAS_HPP
#define MONEDAS_HPP

#include <iostream>
#include <vector>
#include <list>


using namespace std;

class monedas{
    
    private: //Métodos privados
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
    
        const vector <int> monedero {50000,20000,10000,5000,2000,1000,500,200,100,50,20,10,5,2,1}; //Vector de enteros en donde tenemos guardadas las monedas disponibles
        list <int> S; //lista que contendrá el resultado
        vector <int> contador; //Vector que irá contando el numero de monedas por cada posicion
    
    public: //Métods públicos
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    
/**    
            @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		Miércoles 13 de Diciembre de 2017

	@detalles 	Constructor de la clase sin parámetros.

*/
        monedas();
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
        
/**
            @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		Miércoles 13 de Diciembre de 2017

	@detalles 	Método que comprueba si la cantidad del monedero en esa posicion es <= al dinero exigido.
    
    @param entero que nos ayuda a saber la posicion del vector monedero.
    @param entero que nos indica la cantidad que el usuario ha introducido por teclado.
    @param entero que nos ayuda a mantener la cuenta de las monedas que estamos usando para llegar a tener el a_devolver.

*/
        bool comprobar_devolucion(int pos, int a_devolver, int suma);
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

/**
            @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		Miércoles 13 de Diciembre de 2017

	@detalles 	Método que dado una cantidad de dinero introducido, convierte los euros en centimos y va sumando e 
	            introduciendo en la lista a aquellos con los que todavía no se sobrepase de la cantidad introducida. 
	            Para ello, se recorre el vector, se comprueba si suma es menor que a_devolver y luego se asegura de
	            que cantidad del monedero deberemos de utilizar ya que si se sobrepasa cogeremos la siguiente menor
	            que la primera y así con el resto de casos.
	
    @param flotante que indica la cantidad de dinero introducido por el usuario.
   
*/
        bool devolver_cambio(float cantidad);
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            
        
        
        
        bool devolver_cambio_mejorado(float cantidad);
        
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
               
/**
            @autor   	Kathrina Arrocha UmpiÃ©rrez (alu0100913293@ull.edu.es)
        
        @fecha 		Miércoles 13 de Diciembre de 2017

	@detalles 	Método que muestra por pantalla la cantidad de monedas a usar indicando si son euros o centimos
	
   
*/ 
        void mostrar_resultados();
    
};


#endif

