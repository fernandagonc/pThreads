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
            //Verificar Penny e casais
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

        if(posicaoPenny != fila.end()){
            fila.insert(++posicaoPenny, nome);
        }
        else if(posicaoHoward ==  fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoHoward, nome);
        }
    }
    else if (nome == "Amy"){
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        if(posicaoSheldon != fila.end()){
            fila.insert(++posicaoSheldon, nome);
        }
        else if(posicaoPenny == fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoPenny, nome); 
        }

    }
    else if(nome == "Bernadette"){
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");

        if(posicaoHoward != fila.end()){
            fila.insert(++posicaoHoward, nome);
        }
        else if(posicaoAmy ==  fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoAmy, nome);
        }
    }
    else if(nome == "Penny"){
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");

        if(posicaoLeonard != fila.end()){
            fila.insert(++posicaoLeonard, nome);
        }
        else if(posicaoBernadette ==  fila.end()){
            fila.push_front(nome);
        }
        else{
            fila.insert(++posicaoLeonard, nome);
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
    else{
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

bool deadLockPersonagensMasculinos(){
    auto posicaoHoward = posicaoPersonagemNaFila("Howard");
    auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
    auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");

    if(posicaoSheldon != fila.end() && posicaoLeonard != fila.end() && posicaoHoward != fila.end()){
        return true;
    }
    
    return false;
    

}

bool deadLockPersonagensFemininos(){
    auto posicaoAmy = posicaoPersonagemNaFila("Amy");
    auto posicaoPenny = posicaoPersonagemNaFila("Penny");
    auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

    if(posicaoAmy != fila.end() && posicaoPenny != fila.end() && posicaoBernadette != fila.end()){
        return true;
    }
    
    return false;
    

}

void Monitor::verificar(){

    cout << "Verificando: ";

    bool deadLockFeminino = deadLockPersonagensFemininos();
    bool deadlockMasculino = deadLockPersonagensMasculinos();

    if(deadLockFeminino && deadlockMasculino){
        cout << "Deadlock casais \n";
        //liberar um dos casais aleatoriamente
    }
    else if (deadLockFeminino){
        cout << "Deadlock feminino \n";
        //liberar uma das mulheres
    }
    else if (deadlockMasculino){
        cout << "Deadlock masculino \n";
        //liberar um dos homens
    }
    else
        cout << "Sem deadlocks \n";

    return;
};