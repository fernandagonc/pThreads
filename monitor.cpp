#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

Monitor::Monitor() {

    if (pthread_mutex_init(&this->lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
    } 


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