#ifndef MONITOR_H
#define MONITOR_H

#include "personagem.hpp"
#include <pthread.h>

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
        int controleThreadsCriadas;


        Monitor();        
        void esperar(Personagem p);
        void liberar(Personagem p);
        void initCond(pthread_cond_t* cond);
        void condSignal(pthread_cond_t* cond);
        void condWait(pthread_cond_t* cond, pthread_mutex_t* mutex);
        void liberarPersonagem(string nome);
        void verificar();
};


#endif