#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>


using namespace std;

int livre = 1;

Monitor::Monitor() {

    this->lock = PTHREAD_MUTEX_INITIALIZER;
    this->condicao = PTHREAD_COND_INITIALIZER;
    this->controleThreadsCriadas = 0;

    if (pthread_mutex_init(&this->lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
    } 


};

void printFila(list <string> g) 
{ 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << *it  << ", "; 
    cout << '\n'; 
} 

void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    this->fila.push_back(p.nome);
    
    //printFila(this->fila);

    if (pthread_mutex_lock(&this->lock) != 0) {
        cout << "pthread_mutex_lock error";
        exit(2);
    }

    //cout << "waiting  ";
    while(fila.front() != p.nome)
        pthread_cond_wait(&this->condicao, &this->lock);
    //cout << "    liberado \n ";

};

void Monitor::liberar(Personagem p){
    
    
    cout << p.nome << " vai comer \n";
    this->fila.pop_front();
    // showlist(this->fila);
    pthread_mutex_unlock(&this->lock); 

    if(this->fila.front() == p.nome)
        pthread_cond_signal(&this->condicao);
};

void Monitor::verificar(){
    cout << "Verificando deadlock \n";
    return;
};