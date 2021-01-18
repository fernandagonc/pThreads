#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>
#include <list>


using namespace std;

list<Personagem> fila = {};
int livre = 1;

Monitor::Monitor() {

    this->lock = PTHREAD_MUTEX_INITIALIZER;
    this->condicao = PTHREAD_COND_INITIALIZER;
    this->controleThreadsCriadas = 0;

    if (pthread_mutex_init(&this->lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
    } 


};

void Monitor::printFila(){
    for (auto const& i: fila) {
        cout << i.nome << ", ";
    }
    cout << "\n";
}

void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    pthread_mutex_lock(&this->lock); 

    cout << "waiting";
    pthread_cond_wait(&this->condicao, &this->lock);
    cout << "liberado";
};

void Monitor::liberar(Personagem p){
    p.comer();
 
    pthread_cond_signal(&this->condicao);
    pthread_mutex_unlock(&this->lock); 
};

void Monitor::verificar(){
    cout << "Verificando deadlock \n";
    return;
};