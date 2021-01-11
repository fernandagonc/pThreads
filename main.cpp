#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "character.hpp"
#include "monitor.hpp"

using namespace std;

Monitor forno;
Personagem personagens[8]; 



void * threadHandler (void * p){
    Personagem personagem;
    personagem.nome = (char *) p;

    while(true) {
        
        personagem.esquentarAlgo();

        personagem.comer();
    
        personagem.trabalhar();
    }


    return 0; 
}


void criarThread (Personagem personagem) {
    int status;
    Personagem * addr = &personagem;

    status = pthread_create(&forno.threads[personagem.id], NULL, threadHandler, (void *) &personagem.nome[0] );
    if (status < 0) {
        cout << "Erro ao criar a thread.";
    }
    cout << "Thread do personagem " << personagem.nome << " criada com sucesso! \n";
    
 
};

void inicializarPersonagens(int nroVezesUsoForno, Personagem personagens[]){
    Personagem* novo;
    char nomes[8][12] = {"Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Stuart", "Kripke"};

    for(int i = 0; i < 8; i++){
        if (i >= 0 && i <= 5){
            novo = new Personagem(nomes[i], true, nroVezesUsoForno, i);
        }
          
        else 
            novo = new Personagem(nomes[i], false, nroVezesUsoForno, i);

        
        personagens[i] = *novo;
    }

}

int main(int argc, char *argv[]){
    
    if(argc < 1){
        cout << "Especifique número de vezes para os personagens usarem o forno.";
        exit(1);
    }

    int nroVezesUsoForno = atoi(argv[1]);
    Personagem personagens[8];
    inicializarPersonagens(nroVezesUsoForno, personagens);
    criarThread(personagens[0]);

    

    // pthread_join(threads[0], NULL); 
    // pthread_join(threads[1], NULL);

    // pthread_mutex_destroy(&lock); 
  

    return 0;
}