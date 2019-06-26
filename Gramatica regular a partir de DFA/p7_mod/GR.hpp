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
	vector<Produccion> production;
	
	
////////////////////////////////////////////////////////////////////////////////	
	/**
	
			@detalles Conjunto de gets y sets necesarios para la utilización de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.
	
	@fecha 8 de noviembre de 2017
	
	*/

////////////////////////////////////////////////////////////////////////////////

public:
	set<char> alfabeto; // Alfabeto letras no terminales mayúsculas

////////////////////////////////////////////////////////////////////////////////

		/**
	
			 @detalles Constructor vacío de la clase.
	
		 @Autor Kathrina Arrocha Umpiérrez.
		 
	@fecha 8 de noviembre de 2017
	
	*/
	
	Gramatica();

////////////////////////////////////////////////////////////////////////////////
	
	/*
			@detalles Constructor de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.
		
	@fecha 8 de noviembre de 2017
	
	*/
		
	Gramatica(set<char>, char);
		

////////////////////////////////////////////////////////////////////////////////

	/**
			@detalles Destructor vacío de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.
	 
	@fecha 8 de noviembre de 2017
	
	*/
		
	~Gramatica();
		


////////////////////////////////////////////////////////////////////////////////

	/**
	
			@detalles Metodo para exportar los resultados a un archivo
	
		@Autor Kathrina Arrocha Umpiérrez.
	
	@fecha 8 de noviembre de 2017
	
	*/
		
	void exportar();
	


		
////////////////////////////////////////////////////////////////////////////////

	/**
	
			@detalles  Metodo para ir añadiendo producciones para comprobarlas
	
		 @Autor Kathrina Arrocha Umpiérrez.
	 
	 @fecha 8 de noviembre de 2017
	
	*/

	void anadir_production(Produccion);
	
		
		
////////////////////////////////////////////////////////////////////////////////
	/**
	
			@detalles  Set que nos ayuda a obtener el calculo
	
		@Autor Kathrina Arrocha Umpiérrez.
	
	@fecha 8 de noviembre de 2017
	
	*/
	
	
	void set_nt(set<char>);
		
};