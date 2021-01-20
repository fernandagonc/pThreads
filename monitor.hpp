#ifndef MONITOR_H
#define MONITOR_H

#include "personagem.hpp"
#include <pthread.h>
#include <list>
#include <string>
class Monitor{

    public: 
        pthread_mutex_t lock; 
        pthread_cond_t condicao; 
        int controleThreadsCriadas;
        std::list<string> fila;


        Monitor();        
        void esperar(Personagem p);
        void liberar(Personagem p);
        void verificar();
};


#endif