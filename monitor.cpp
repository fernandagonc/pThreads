#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

Monitor::Monitor() {

    this->lock = PTHREAD_MUTEX_INITIALIZER;
    this->condicao = PTHREAD_COND_INITIALIZER;
    this->controleThreadsCriadas = 0;

    if (pthread_mutex_init(&this->lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
    } 

    pthread_mutex_lock(&this->lock); 

// while(!condition){
//     pthread_cond_wait(&condition, &mutex); //wait for the condition
// }


};

void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    pthread_mutex_lock(&this->lock); 
};

void Monitor::liberar(Personagem p){
    pthread_mutex_unlock(&lock); 
    cout << p.nome << " vai comer \n";
};

void Monitor::verificar(){
    cout << "Verificando deadlock \n";
};