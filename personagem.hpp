#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>
#include <pthread.h>

using std::string;

class Personagem{

    public: 
        string nome;
        int nroVezesUsoForno;
        pthread_t id; 

        Personagem();
        Personagem(string nome, int nroVezesUsoForno, pthread_t id);
        
        void esquentarAlgo();
        void comer();
        void trabalhar();
        void printDadosPersonagem();
};


#endif