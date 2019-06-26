/* Autor: Kathrina Arrocha Umpiérrez
   Fecha de entrega: 4/10/2017
   Clase cadena.*/
 
   
#pragma once
#include "cadena.hpp"


cadena::cadena(){
  cad_ += "";
}


cadena::cadena(string cad){

  this -> cad_ = cad;

}


cadena::cadena(const cadena &copyin){
  this -> cad_ = copyin.cad_;
}


ostream &operator<<(ostream &output, const cadena  &bbb)
{
   output << bbb.cad_;
   return output;
}


cadena& cadena::operator=(const cadena &rhs)
{
   this->cad_ = rhs.cad_;
   return *this;
}


int cadena::operator==(const cadena &rhs) const
{
   if( this->cad_.compare(rhs.cad_) !=0 ) return 0;
   return 1;
}


int cadena::operator<(const cadena &rhs) const
{
   if (this->cad_ < rhs.cad_) return 1;
   return 0;
}


cadena::~cadena(){
}
