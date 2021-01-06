#ifndef PERSONAGEM
#define PERSONAGEM  

typedef struct Personagem{
    char * nome;
    int nroVezesUsoForno;
    int isCasal;
} Personagem;


typedef struct Forno {
    int isOcupado;

} Oven;

Personagem * inicializarPersonagens(int nroVezesUsoForno );

#endif