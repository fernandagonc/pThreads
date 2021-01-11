#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>
#include <pthread.h>

using std::string;

class Personagem{

    public: 
        std::string nome;
        int nroVezesUsoForno;
        bool isCasal;
        pthread_t id; 

        Personagem();
        Personagem(string nome, bool isCasal, int nroVezesUsoForno);
        
        void esquentarAlgo();
        void comer();
        void trabalhar();
};


#endif