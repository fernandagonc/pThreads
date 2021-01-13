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


void criarThread (Personagem personagem) {
    int status;
    Personagem p = personagem;
    Personagem * pointer;
    pointer = &p;

    status = pthread_create(&forno.threads[personagem.id], NULL, &threadHandler, (void *) pointer);
    if (status < 0) {
        cout << "Erro ao criar a thread.";
    }

    cout << "Thread do personagem " << personagem.nome << " criada com sucesso! \n";
    //pthread_join(forno.threads[personagem.id], NULL); 
    forno.controleThreadsCriadas++;
 
};

void inicializarPersonagens(int nroVezesUsoForno, Personagem personagens[]){
    Personagem* novo;
    string nomes[8] = {"Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Stuart", "Kripke"};

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
    criarThread(personagens[1]);

    if(forno.controleThreadsCriadas == 2){
        pthread_mutex_unlock(&forno.lock); 
    }
      



    // pthread_mutex_destroy(&lock); 
  

    return 0;
}