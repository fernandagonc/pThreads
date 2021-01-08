#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include<string>

using std::string;

class Personagem{

    public: 
        std::string nome;
        int nroVezesUsoForno;
        bool isCasal;

        Personagem();
        Personagem(string nome, bool isCasal, int nroVezesUsoForno);

};


#endif