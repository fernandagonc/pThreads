#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

bool isFornoLivre = true;
std::list<string> fila;

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


list<string>::iterator posicaoPersonagemNaFila(string nome){
    auto it = find(fila.begin(), fila.end(), nome);
    return it;
}

void adicionarPersonagemNaFila(string nome){

    if (nome == "Sheldon"){
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");
        if(posicaoAmy != fila.end()){
            fila.insert(++posicaoAmy, nome);
        }
        else if(posicaoLeonard == fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoLeonard, nome); 
        }

    }
    else if(nome == "Howard"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

        if(posicaoBernadette != fila.end()){
            fila.insert(++posicaoBernadette, nome);
        }
        else if(posicaoSheldon ==  fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoSheldon, nome);
        }
    }
    else if(nome == "Leonard"){
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        if(posicaoAmy != fila.end()){
            fila.insert(++posicaoPenny, nome);
        }
        else if(posicaoHoward ==  fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoHoward, nome);
        }
    }
    else if(nome == "Stuart"){
        auto posicaoKripke = posicaoPersonagemNaFila("Kripke");

        if(posicaoKripke == fila.end()){
            fila.push_back(nome);
        }
        else{
            fila.insert(posicaoKripke, nome);
        }

    }
    else if(nome == "Kripke"){
        fila.push_back(nome);
    }
}

void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    
    adicionarPersonagemNaFila(p.nome);
    cout << "LISTA: ";
    printFila(fila);

    if (pthread_mutex_lock(&this->lock) != 0) {
        cout << "pthread_mutex_lock error";
        exit(2);
    }

    while(fila.front() != p.nome)
        pthread_cond_wait(&this->condicao, &this->lock);

};

void Monitor::liberar(Personagem p){
    
    
    cout << p.nome << " vai comer \n";
    fila.remove(p.nome);
    cout << "LISTA: ";
    printFila(fila);

    pthread_mutex_unlock(&this->lock); 

    if(fila.front() == p.nome)
        pthread_cond_signal(&this->condicao);
};

void Monitor::verificar(){
    cout << "Verificando deadlock \n";
    return;
};