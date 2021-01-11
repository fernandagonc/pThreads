#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "character.hpp"

using namespace std;
pthread_t threads[2]; 
int counter; 
pthread_mutex_t lock; 

void * threadHandler (void * args){
    pthread_mutex_lock(&lock); 

    //verificar prioridades e usar forno
    pthread_mutex_unlock(&lock); 
    return 0; 
}

void iniciarAcoesPersonagem (Personagem personagem) {
    int status;

    status = pthread_create(&threads[0], NULL, threadHandler, (void *) &personagem.nome[0] );
    if (status < 0) {
        cout << "Erro ao criar a thread.";
    }
    cout << "Thread do personagem " << personagem.nome << " criada com sucesso! \n";
    
    while(personagem.nroVezesUsoForno > 0) {
    
        personagem.esquentarAlgo();
        personagem.nroVezesUsoForno = personagem.nroVezesUsoForno - 1;

        personagem.comer();
    
        personagem.trabalhar();
    }

};

void inicializarPersonagens(int nroVezesUsoForno, Personagem array[]){
    Personagem* novo;
    string nomes[8] = {"Sheldon", "Amy", "Leonard", "Penny", "Howard", "Bernadette", "Stuart", "Kripke"};

    for(int i = 0; i < 8; i++){
        if (i > 0 && i <= 5)
            novo = new Personagem(nomes[i], true, nroVezesUsoForno);
        else 
            novo = new Personagem(nomes[i], false, nroVezesUsoForno);

        
        array[i] = *novo;

    }

}

int main(int argc, char *argv[]){
    
    if(argc < 1){
        cout << "Especifique número de vezes para os personagens usarem o forno.";
        exit(1);
    }

    if (pthread_mutex_init(&lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
        return 1; 
    } 

    int nroVezesUsoForno = atoi(argv[1]);
    Personagem personagens[8]; 
    inicializarPersonagens(nroVezesUsoForno, personagens);
    iniciarAcoesPersonagem(personagens[0]);

    

    pthread_join(threads[0], NULL); 
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&lock); 
  


}