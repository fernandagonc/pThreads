#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include "personagem.hpp"
#include "monitor.hpp"
#include <unistd.h>

using namespace std;

Monitor forno;

void * threadHandler (void * pointer){

    Personagem * dados = (Personagem *)pointer;
    Personagem personagem(dados->nome, dados->isCasal, dados->nroVezesUsoForno, dados->id);
    personagem.printDadosPersonagem();
    while(personagem.nroVezesUsoForno > 0) {
        forno.esperar(personagem);
        personagem.esquentarAlgo();
        forno.liberar(personagem);
        personagem.comer();
        personagem.nroVezesUsoForno = personagem.nroVezesUsoForno - 1;
        personagem.trabalhar();
    }


    return 0; 
}


pthread_t criarThread (Personagem personagem) {
    int status;
    Personagem p = personagem;
    Personagem * pointer;
    pointer = &p;
    pthread_t id;

    status = pthread_create(&id, NULL, &threadHandler, (void *) pointer);
    if (status < 0) {
        cout << "Erro ao criar a thread.";
    }

    cout << "Thread do personagem " << personagem.nome << " criada com sucesso! \n";
    forno.controleThreadsCriadas++;
 
    return id;
};

void inicializarPersonagens(int nroVezesUsoForno, Personagem personagens[]){
    Personagem novo;
    string nomes[8] = {"Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Stuart", "Kripke"};

    for(int i = 0; i < 8; i++){
        if (i >= 0 && i <= 5){
            novo = Personagem(nomes[i], true, nroVezesUsoForno, i);
        }
          
        else 
            novo = Personagem(nomes[i], false, nroVezesUsoForno, i);

        
        personagens[i] = novo;
    }

}

void joinThread(pthread_t id){
    if (pthread_join(id, NULL) < 0) {
        cout << "Erro ao dar join na thread";
    }; 
}

int main(int argc, char *argv[]){
    
    if(argc < 1){
        cout << "Especifique número de vezes para os personagens usarem o forno.";
        exit(1);
    }

    int nroVezesUsoForno = atoi(argv[1]);
    Personagem personagens[8];
    inicializarPersonagens(nroVezesUsoForno, personagens);
    
    // for(int i = 0; i < 8; i++){
    //     personagens[i].printDadosPersonagem();
    // }
    
    personagens[0].id = criarThread(personagens[0]);
    personagens[5].id = criarThread(personagens[5]);

    sleep(20);

    joinThread(personagens[0].id);
    joinThread(personagens[5].id);


    return 0;
}