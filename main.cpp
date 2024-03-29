#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <algorithm> 
#include "personagem.hpp"
#include "monitor.hpp"
#include <unistd.h>
#include <cstdlib>


using namespace std;

Monitor forno;
bool threadsPersonagensAtivas = true;

void * threadHandler (void * pointer){

    Personagem * dados = (Personagem *)pointer;
    Personagem personagem(dados->nome, dados->nroVezesUsoForno, dados->id);

    while(personagem.nroVezesUsoForno > 0) {
        forno.esperar(personagem);
        personagem.esquentarAlgo();
        forno.liberar(personagem);
        personagem.comer();
        personagem.trabalhar();
        personagem.nroVezesUsoForno = personagem.nroVezesUsoForno - 1;
    }

    return 0; 
}


pthread_t criarThread (Personagem personagem) {
    Personagem p = personagem;
    Personagem * pointer;
    pointer = &p;
    pthread_t id;

    if (pthread_create(&id, NULL, &threadHandler, (void *) pointer) < 0) {
        cout << "Erro ao criar a thread.";
        return -1;
    }
    sleep(1);
    return id;
};

void joinThread(pthread_t id){
    if (pthread_join(id, NULL) < 0) {
        cout << "Erro ao dar join na thread \n";
        return; 
    }; 

    return;
}

void * threadRaj (void * pointer){

    while(threadsPersonagensAtivas){
        sleep(5);
        forno.verificar();
    }
    
    return 0;
}

void inicializarPersonagens(int nroVezesUsoForno, Personagem personagens[]){
    Personagem novo;
    //string nomes[8] = {"Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Stuart", "Kripke"};
    //string nomes[8] = {"Stuart", "Leonard", "Sheldon", "Howard", "Kripke", "Amy", "Penny", "Bernadette"};
    string nomes[8] = {"Stuart", "Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Kripke"};
    //string nomes[8] = {"Stuart", "Leonard", "Sheldon", "Howard", "Amy", "Penny", "Bernadette", "Kripke"};

    for(int i = 0; i < 8; i++){
    
        novo = Personagem(nomes[i], nroVezesUsoForno, i);
        personagens[i] = novo;
    }


}

int main(int argc, char *argv[]){
    srand(time(0));
    if(argc < 2){
        cout << "Especifique número de vezes para os personagens usarem o forno.";
        exit(1);
    }

    int nroVezesUsoForno = atoi(argv[1]);
    Personagem personagens[8];
    inicializarPersonagens(nroVezesUsoForno, personagens);
    
    pthread_t raj;
    int statusRaj = pthread_create(&raj, NULL, &threadRaj, NULL);

    if (statusRaj < 0) {
        cout << "Erro ao criar a thread do Raj.\n";
        return -1;
    }
    else{
        sleep(0.5);
    }
        
    random_shuffle(personagens, personagens+8);

    for(int i=0; i < 8; i++){
        personagens[i].id = criarThread(personagens[i]);
    }

    for(int i=0; i < 8; i++){
        joinThread(personagens[i].id);

    }


    threadsPersonagensAtivas = false;
    joinThread(raj);


    return 0;
}