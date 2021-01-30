#ifndef MONITOR_H
#define MONITOR_H

#include "personagem.hpp"
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <unistd.h>

using namespace std;

class Monitor{

    public: 
        pthread_mutex_t lock; 
        pthread_cond_t sheldonCond;
        pthread_cond_t amyCond;
        pthread_cond_t howardCond;
        pthread_cond_t bernadetteCond;
        pthread_cond_t leonardCond;
        pthread_cond_t pennyCond;
        pthread_cond_t stuartCond;
        pthread_cond_t kripkeCond;; 
        string primeiroDaFila;

        Monitor();        
        void esperar(Personagem p);
        void liberar(Personagem p);
        
        void initCond(pthread_cond_t* cond);
        void condSignal(pthread_cond_t* cond);
        void condWait(pthread_cond_t* cond, pthread_mutex_t* mutex);
        list<string>::iterator posicaoPersonagemNaFila(string nome);
        void passarPessoaNaFrente(string nome);
        void adicionarPersonagemNaFila(string nome);
        string acharCasal(string nome);
        int qtdSheldonAmy();
        int qtdLeonardPenny();
        int qtdHowardBernadette();
        void reorganizarFila();
        bool precisaReorganizarFila();
        bool hasDeadLock();
        void acharOCasalEPassarNaFrente(string nome);
        void liberarPersonagem(string nome);
        void waitPersonagem(string nome);
        void verificar();
};


#endif