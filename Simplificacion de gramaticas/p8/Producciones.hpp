#pragma once
#include <vector>
#include <set>
#include <string>

using namespace std;

	/*
		 @clase Produccion
	 @detalles Clase para analizar las posibles producciones de un autÃ³mata

	 */
class Produccion{


////////////////////////////////////////////////////////////////////////////////
char part_izq; /*Char en el que guardare la parte izquierda */
set<string> part_derech; /* Set de String en el que guardare la parte derecha */


////////////////////////////////////////////////////////////////////////////////
public:

	/*

			@detalles Constructor vacÃ­o de la clase.

		@Autor Kathrina Arrocha UmpiÃ©rrez.

	@fecha 14 de Noviembre de 2017

	*/
	Produccion();




////////////////////////////////////////////////////////////////////////////////

		/*

			@detalles Destructor vacÃ­o de la clase.

		@Autor Kathrina Arrocha UmpiÃ©rrez.

	@fecha 14 de Noviembre de 2017

	*/
	~Produccion();



////////////////////////////////////////////////////////////////////////////////
		/**

			 @detalles Conjunto de gets y sets necesarios para la utilizaciÃ³n de la clase.

		@Autor Kathrina Arrocha UmpiÃ©rrez.

	 @fecha 14 de Noviembre de 2017

	*/

	////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Metodo para obtener la parte izquierda.

	@Autor Kathrina Arrocha UmpiÃ©rrez.

 @fecha 14 de Noviembre de 2017

*/
	char get_part_izq() const;

	////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Metodo para cambiar el valor de la parte izquierda.

	@Autor Kathrina Arrocha UmpiÃ©rrez.

 @fecha 14 de Noviembre de 2017

*/
	void set_part_izq(char);

////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Metodo constante para obtener la parte derecha.

	@Autor Kathrina Arrocha UmpiÃ©rrez.

 @fecha 14 de Noviembre de 2017

*/
	set<string> get_part_derech() const;

	////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Metodo para cambiar el valor de la parte derecha.

	@Autor Kathrina Arrocha UmpiÃ©rrez.

	@fecha 14 de Noviembre de 2017
	* @param Set string con el que cambio el valor
	*/

	void set_part_derech(set<string> &m);

////////////////////////////////////////////////////////////////////////////////

/**

	 @detalles Metodo para añadir en el set de la parte derecha

@Autor Kathrina Arrocha UmpiÃ©rrez.

@fecha 14 de Noviembre de 2017

* @param String parte derecha

*/
	void anadir_part_derech(string);

////////////////////////////////////////////////////////////////////////////////
/**

	 @detalles Metodo para buscar en la parte derecha

@Autor Kathrina Arrocha UmpiÃ©rrez.

@fecha 14 de Noviembre de 2017
* @param String a buscar en la parte derecha

*/

	bool Buscar_part(string);

////////////////////////////////////////////////////////////////////////////////
/**

	 @detalles Metodo para hacer un clear en la parte derecha

@Autor Kathrina Arrocha UmpiÃ©rrez.

@fecha 14 de Noviembre de 2017

*/
	void limpiarParteDerecha();


////////////////////////////////////////////////////////////////////////////////
	/**

			@detalles Conjunto de operadores necesarios para la utilizacion de la clase

		@Autor Kathrina Arrocha UmpiÃ©rrez.

	@fecha 14 de Noviembre de 2017

	*/

	//Sobrecarga de Operadores:
	////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Sobrecarga del operador = (Igualar)

	@Autor Kathrina Arrocha UmpiÃ©rrez.

 @fecha 14 de Noviembre de 2017

*/
	Produccion& operator=(const Produccion &rhs);
	////////////////////////////////////////////////////////////////////////////////
	/**

		 @detalles Sobrecarga del operador == (Comparar igualdad)

	@Autor Kathrina Arrocha UmpiÃ©rrez.

 @fecha 14 de Noviembre de 2017

*/
    int operator==(const Produccion &rhs) const;
   //	int operator<(const Produccion &rhs) const;




};
