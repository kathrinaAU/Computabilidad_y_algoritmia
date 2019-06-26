#pragma once
#include "Producciones.hpp"
#include <set>
#include <iostream>
#include <fstream>

using namespace std;

/**
		@clase Gramatica
	@detalles Clase para analizar las posibles producciones de un autómata

 */

class Gramatica{

private:

	set<char> no_terminal; /* Set de caracteres para introducir los no terminales */
	char inicial;
	set<char> terminal; /* Set de caracteres terminales */
	vector<Produccion> production; /* Vector en el que se encuentran las producciones */


////////////////////////////////////////////////////////////////////////////////
	/**

			@detalles Conjunto de gets y sets necesarios para la utilización de la clase.

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017

	*/

////////////////////////////////////////////////////////////////////////////////

public:
	set<char> alfabeto; // Alfabeto letras no terminales mayúsculas

////////////////////////////////////////////////////////////////////////////////

		/**

			 @detalles Constructor vacío de la clase.

		 @Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017

	*/

	Gramatica();


////////////////////////////////////////////////////////////////////////////////

	/*
			@detalles Constructor de la clase con el fichero.

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017
	* @param	Caracter que se trata del fichero del que vamos a cargar los datos

	*/

	Gramatica(char Nombre_Fichero_grammar[]);

////////////////////////////////////////////////////////////////////////////////

	/*
			@detalles Constructor de la clase.

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017

	*/

	Gramatica(set<char>, char);


////////////////////////////////////////////////////////////////////////////////

	/**
			@detalles Destructor vacío de la clase.

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017

	*/

	~Gramatica();



////////////////////////////////////////////////////////////////////////////////

	/**

			@detalles Metodo para exportar los resultados a un archivo

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017

	*/

	void exportar();




////////////////////////////////////////////////////////////////////////////////

	/**

			@detalles  Metodo para ir añadiendo producciones al vector de producciones

		 @Autor Kathrina Arrocha Umpiérrez.

	 @fecha 14 de Noviembre de 2017
   * @param Vector de producciones

	*/

	void anadir_production(Produccion);



////////////////////////////////////////////////////////////////////////////////
	/**

			@detalles  Método para cambiar el valor del set de no terminal por el set pasado por parametros

		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 14 de Noviembre de 2017
	* @param set de caracteres
	*/


	void set_nt(set<char>);
  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Metodo con el que cambio el valor de las letras y las hago iniiciarse desde S en vez de desde A

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017

  	*/

	void exportar_renombrar();
  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Método que nos introduce cargar los datos del fichero de la gramática

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017
		* @param Nombre de fichero de gramatica

  	*/

	void cargar_gramatica(char Nombre_Fichero_grammar[]);
  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Método de la ETAPA 1 DE PRODUCCIONES NULAS. Se encarga de buscar aquellas
        partes derechas en las que el valor de sus producciones sea ~ e insertarlas en un set llamado eps

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017
    * @param set de char en el que introduciremos aquellas partes izquierdas de la producción cuya parte derecha es ~

  	*/

	void busqueda_eps(set<char> &eps);
  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Método que busca a los anulables

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017
		* @param set de caracteres

  	*/
	void busqueda_anulables(set<char> &anull);
  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Método que busca producciones

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017
		* @param char que es la parte izquierda

  	*/
    Produccion * searchProduction(char p_izq);
    ////////////////////////////////////////////////////////////////////////////////
    	/**

    			@detalles  Metodo que busca las posibilidades de cada una de las producciones que están afectadas por los anulable

    		@Autor Kathrina Arrocha Umpiérrez.

    	@fecha 14 de Noviembre de 2017
			* @param String parte derecha
			* @param set de caracteres
			* @param set string
			* @param string que representa la parte izquierda

    	*/
    void addPosibilities(string p_dcha, set<char> &anull, set<string> &nuevas, string p_izq);
    ////////////////////////////////////////////////////////////////////////////////
    	/**

    			@detalles  Método de la ETAPA 2 DE PRODUCCIONES NULAS: En ella detectamos que variables son anulables
          y eliminamos las producciones que van a lambda directamentes

    		@Autor Kathrina Arrocha Umpiérrez.

    	@fecha 14 de Noviembre de 2017

    	*/
    void eliminarVacios();


////////////////////////////////////////////////////////////////////////////////

      /**

          @detalles  Método de la ALGORITMO DE PRODUCCIONES UNITARIAS: Se encarga de, primero cojo la produccioe entera
          y busco si en la parte derecha hay un solo no terminal en la produccion. Si se cumple, inserto en el set de parejas
          donde el primero que inserto es la parte izq y el segundo es el no terminal.
          Luego recorro el set de parejas y busco si tengo guardada alguna pareja en la que el segundo sea igual al primero de otra pareja.
          Por último, intercambio en las parejas: En la parte izquierda inserto las producciones de la parte derecha

        @Autor Kathrina Arrocha Umpiérrez.

      @fecha 14 de Noviembre de 2017

      */
    void encontrandoParejas();



  ////////////////////////////////////////////////////////////////////////////////
  	/**

  			@detalles  Metodo que va buscando en el string de producciones, dada una pos, una letra

  		@Autor Kathrina Arrocha Umpiérrez.

  	@fecha 14 de Noviembre de 2017
		* @param String de producciones
		* @param Posicion a comparar
		*@param caracter con el que comparamos prod[i]
  	*/
int posicionEnProduccion(string prod, unsigned int pos,char letra);
};
