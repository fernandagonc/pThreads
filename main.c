#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "character.h"

pthread_t threads[2]; 
int counter; 
pthread_mutex_t lock; 

void monitor(){
    pthread_mutex_lock(&lock); 

    //verificar prioridades e usar forno
    printf("usando forno");
    pthread_mutex_unlock(&lock); 

}


int main(int argc, char *argv[]){
    
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n Inicialização mutex falhou.\n"); 
        return 1; 
    } 

    Personagem personagens[8];

    int status;
    int args;
    for (int i=0; i < 2; i ++){
        status = pthread_create(&threads[i], NULL, monitor, (void *) args);
        if (status < 0) {
            printf("Erro ao criar a thread: %s ", strerror(status));
        }
        printf("Thread criada com sucesso! \n");
    }
    

    pthread_join(threads[0], NULL); 
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&lock); 
  


}