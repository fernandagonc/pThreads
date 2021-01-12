#ifndef MONITOR_H
#define MONITOR_H

#include "personagem.hpp"
#include <pthread.h>

class Monitor{

    public: 
        pthread_t threads[8]; 
        pthread_mutex_t lock; 

        Monitor();        
        void esperar(Personagem p);
        void liberar(Personagem p);
        void verificar();
};


#endif