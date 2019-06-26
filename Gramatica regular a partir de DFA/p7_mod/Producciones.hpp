#pragma once
#include <vector>
#include <set>
#include <string>

using namespace std;

	/*
		 @clase Produccion
	 @detalles Clase para analizar las posibles producciones de un autómata
	 
	 */
class Produccion{


////////////////////////////////////////////////////////////////////////////////
char part_izq;
vector<string> part_derech;


////////////////////////////////////////////////////////////////////////////////
public:

	/*
	
			@detalles Constructor vacío de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.
	
	@fecha 8 de noviembre de 2017
	
	*/
	Produccion();
	

	

////////////////////////////////////////////////////////////////////////////////	
	
		/*
	
			@detalles Destructor vacío de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.

	@fecha 8 de noviembre de 2017
	
	*/
	~Produccion();
	


////////////////////////////////////////////////////////////////////////////////		
		/**
	
			 @detalles Conjunto de gets y sets necesarios para la utilización de la clase.
	
		@Autor Kathrina Arrocha Umpiérrez.
		
	 @fecha 8 de noviembre de 2017
	
	*/
	//Gets y sets	
	char get_part_izq() const;
	void set_part_izq(char);
	vector<string> get_part_derech() const;
	void set_part_derech(vector<string>);
	void anadir_part_derech(string);
	bool Buscar_part(string);


////////////////////////////////////////////////////////////////////////////////
	/**
	
			@detalles Conjunto de operadores necesarios para la utilizacion de la clase
	
		@Autor Kathrina Arrocha Umpiérrez.
		
	@fecha 8 de noviembre de 2017
	
	*/
	
	//Operadores
	Produccion& operator=(const Produccion &rhs);
    int operator==(const Produccion &rhs) const;
   //	int operator<(const Produccion &rhs) const;




};