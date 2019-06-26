
#include "estado.hpp"

/*
    Constructor por defecto
*/
estado_t::estado_t(void):
    id_(0),
    Aceptado_(false),
    Transiciones_(0),
    Simbolo_(NULL),
    Destino_(NULL)
    {}

 estado_t::estado_t(int id, bool Estado_Aceptacion, int Transitions, char* Simbolo, int* Destino):
    id_(id),
    Aceptado_(Estado_Aceptacion),
    Transiciones_(Transitions),
    Simbolo_(NULL),
    Destino_(NULL)
    {
        Simbolo_ = new char[Transiciones_];
        Destino_ = new int[Transiciones_];
        
        for(int i = 0; i< Transiciones_; i++){
            Simbolo_[i] = Simbolo[i];
            Destino_[i] = Destino[i];
        }
        
        if ((Simbolo_ == NULL) || (Destino_ == NULL)){
            std::cout << "Error reservando memoria" << std::endl;
        }
    }
    
estado_t::estado_t(const estado_t &copyin)
{
    
    id_ = copyin.id_;
    Aceptado_ = copyin.Aceptado_;
    Transiciones_ = copyin.Transiciones_;
    Simbolo_ = copyin.Simbolo_;
    Destino_ = copyin.Destino_;

}

estado_t::~estado_t(void)
{}

int estado_t::operator==(const estado_t &rhs) const
{
    if (this->id_ != rhs.id_) return 0;
    if (this->Aceptado_ != rhs.Aceptado_) return 0;
    if (this->Transiciones_ != rhs.Transiciones_) return 0;
    for (int i = 0; i < Transiciones_; i++){
        if (Simbolo_[i] != rhs.Simbolo_[i]) return 0;
        if (Destino_[i] != rhs.Destino_[i]) return 0;
    }
    
    return 1;
}

int estado_t::operator<(const estado_t &rhs) const
{
    if (this->id_ < rhs.id_) return 1;
    return 0;
}

estado_t& estado_t::operator=(const estado_t &rhs)
{
    this->id_ = rhs.id_;
    this->Aceptado_ = rhs.Aceptado_;
    this->Transiciones_ = rhs.Transiciones_;

    Simbolo_ = new char[Transiciones_];
    Destino_ = new int[Transiciones_];

    for (int i = 0; i < Transiciones_; i++){
        Simbolo_[i] = rhs.Simbolo_[i];
        Destino_[i] = rhs.Destino_[i];
    }
    
    return *this;
}

std::ostream &operator<<(std::ostream &output, const estado_t &bbb){
    output << bbb.id_ << " " <<  bbb.Aceptado_ << " " << bbb.Transiciones_ << " ";
    
    for (int i = 0; i < bbb.Transiciones_; i++){
        output << bbb.Simbolo_[i] << " " << bbb.Destino_[i] << " ";
    }
    
    std::cout << std::endl;
    
    return output;
}

bool estado_t::estado_muerte(){
    bool comprueba = true;
    
    for (int i=0; i < Transiciones_; i++){
        if (!(this->Destino_[i]) == id_){
            comprueba =false;
            
        }
    }
}


