/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Clase cadena.*/


#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdio>
#include <iterator>

using namespace std;

class cadena {

  friend ostream &operator<<(ostream &, const cadena &);
public:
  string cad_;

  cadena();
  cadena(string);
  cadena(const cadena&);
  virtual ~cadena ();
  //string get_cadena();
  cadena &operator=(const cadena &rhs);
  int operator ==(const cadena &rhs) const;
  int operator <(const cadena &rhs) const;

};
