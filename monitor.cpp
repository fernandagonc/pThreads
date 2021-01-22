#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
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

void passarPrimeiroDoCasalNaFrente(string nome){
    fila.remove(nome);
    fila.push_front(nome);
}

void adicionarPersonagemNaFila(string nome){
    auto inicioFila = fila.begin();

    if (nome == "Sheldon"){
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        bool pennyNaFila = posicaoPenny != fila.end();
        bool leonardNaFila = posicaoLeonard != fila.end();
        bool amyNaFila = posicaoAmy != fila.end();

        if(amyNaFila){
            if(!leonardNaFila){
                if(!pennyNaFila){
                    passarPrimeiroDoCasalNaFrente("Amy");
                    fila.insert(++posicaoAmy, nome);
                }
            }
            else{
                if(pennyNaFila){
                   if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                        fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);
               }
            }
        }
        else{
           if(!leonardNaFila){
                if(!pennyNaFila){
                    fila.push_front(nome);
                }   
                else{
                    fila.insert(++posicaoPenny, nome);
                }
           }
           else{
               if(pennyNaFila){
                   if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                        fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);

               }
           }
        }

    }

    else if(nome == "Howard"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

        if(posicaoBernadette != fila.end()){
            passarPrimeiroDoCasalNaFrente("Bernadette");
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
            passarPrimeiroDoCasalNaFrente("Penny");
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
            passarPrimeiroDoCasalNaFrente("Sheldon");
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
            passarPrimeiroDoCasalNaFrente("Howard");
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
            passarPrimeiroDoCasalNaFrente("Leonard");
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

bool hasDeadLock(){
    auto posicaoHoward = posicaoPersonagemNaFila("Howard");
    auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
    auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");

    auto posicaoAmy = posicaoPersonagemNaFila("Amy");
    auto posicaoPenny = posicaoPersonagemNaFila("Penny");
    auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

    auto filaEnd = fila.end();

    if(posicaoSheldon != filaEnd && posicaoLeonard != filaEnd && posicaoHoward != filaEnd){
        if (posicaoAmy == filaEnd && posicaoPenny == filaEnd && posicaoBernadette == filaEnd)
            return true; // deadlock masculino
        else if(posicaoAmy != filaEnd && posicaoPenny != filaEnd && posicaoBernadette != filaEnd)
            return true; // deadlock casais
    }
    
    else if(posicaoAmy != filaEnd && posicaoPenny != filaEnd && posicaoBernadette != filaEnd){
        if(posicaoSheldon == filaEnd && posicaoLeonard == filaEnd && posicaoHoward == fila.end())
            return true; // deadlock feminino
    }
    return false;
    

}



void Monitor::verificar(){

    cout << "Verificando: ";

    bool deadLock =  hasDeadLock();

    if(deadLock){
        cout << "Deadlock \n";
        pthread_cond_signal(&this->condicao);
    }
    else
        cout << "Sem deadlocks \n";

    return;
};