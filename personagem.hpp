#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>
#include <pthread.h>

using std::string;

class Personagem{

    public: 
        char * nome;
        int nroVezesUsoForno;
        bool isCasal;
        pthread_t id; 

        Personagem();
        Personagem(char * nome, bool isCasal, int nroVezesUsoForno, pthread_t id);
        
        void esquentarAlgo();
        void comer();
        void trabalhar();
};


#endif