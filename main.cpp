#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "character.hpp"

using namespace std;
pthread_t threads[2]; 
int counter; 
pthread_mutex_t lock; 

void * monitor(void *v){
    pthread_mutex_lock(&lock); 

    //verificar prioridades e usar forno
    pthread_mutex_unlock(&lock); 

}

void iniciarAcoesPersonagem (Personagem personagem) {
    
    while(personagem.nroVezesUsoForno > 0) {
    
        personagem.esquentarAlgo();
    
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

    int status;
    int args;
    for (int i=0; i < 2; i ++){
        status = pthread_create(&threads[i], NULL, monitor, NULL);
        if (status < 0) {
            cout << "Erro ao criar a thread.";
        }
        cout << "Thread criada com sucesso! \n";
    }
    

    pthread_join(threads[0], NULL); 
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&lock); 
  


}