//Main2
//#include "DFA_temp.hpp"
#include "NFA.hpp"
#include "DFA.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) //Se rellena el vector y se ordena con uno de los algoritmos
{
    
    DFA A;
    NFA B ;
    
    DFA resultado_A;
    NFA resultado_B;
  
    
    char compara[2][20] = {"compara1.dfa", "compara2.dfa"};
    char nombre_min[2][10] = {"minA.dfa", "minB.dfa"};
    
    
    for (int i = 1; i <argc; i++){
        string convert_to_dfa;
        string name;
        string aux;
        aux = argv[i];
        name = nombre_min[i-1];
        convert_to_dfa = compara[i-1];
    
    
	    //Como necesitamos saber si se trata de un nfa pues vamos a comprobar si termina en .nfa o en .dfa
	    if (argv[i][aux.size()-3] == 'n'){
	        
	        
	        //Una vez comprobado que es un nfa 
	        // Vamos a pasar de un nfa a dfa con el algoritmo de construcción de subconjuntos:
	        //cout << "LOL" << endl;
	        B = NFA (argv[i]);
	        //cout << "LOL 2" << endl;
	        resultado_A = B.convert2DFA();
	        //cout << "LOL 3" << endl;
	        resultado_A.Exportar_DFA(convert_to_dfa);
	        //cout << "LOL 4" << endl;
	        
	        //Cuando ya tenermos a los 2 dfa vamos a minimizarlos
	        ///
	        
	        char convert_to_dfa_[50];
	        strcpy(convert_to_dfa_, convert_to_dfa.c_str());
	        //
	     //   cout << "LOL 5" << endl;
	        DFA inicializado(convert_to_dfa_);
	        DFA result;
	       //  cout << "LOL 6" << endl;
	        result = inicializado.Minimizar_DFA(false);
	        
	        //cout << "LOL 7" <<endl;
	        result = inicializado.Exportar_DFA(name);
	       	//         cout << "LOL 8" << endl;
	    }else{
	        
	        //	         cout << "LOL 9" << endl;
	        //Se trata de un dfa, entonces:
	        DFA inicializado(argv[i]);
	        //	         cout << "LOL 10" << endl;
	        DFA result;
	        //cout << "LOL 11" << endl;
	        result = inicializado.Minimizar_DFA(false);
	        //cout << "LOL 12" << endl;
	        result.Exportar_DFA(name);
	        //cout << "LOL 13" << endl;
	     }
     
    }
    
    
    DFA comparando("minA.dfa");
    DFA entrando("minB.dfa");
    
  
    bool EsEquivalente;
    
    EsEquivalente = comparando.compareDFAmin(entrando);
   
    if (EsEquivalente){ 
        cout << "EQUIVALENT" << endl;
    }else{
        cout << "NON_EQUIVALENT" << endl;
    }
}