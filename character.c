#include "character.h"

Personagem * inicializarPersonagens(int nroVezesUsoForno ){
    Personagem array[8];

    for (int i = 0; i < 8; i++){
        array[i].nroVezesUsoForno = nroVezesUsoForno;
    }

    array[0].nome = 'Sheldon';
    array[0].isCasal = 1;

    array[1].nome = 'Amy';
    array[1].isCasal = 1;

    array[2].nome = 'Leonard';
    array[2].isCasal = 1;

    array[3].nome = 'Penny';
    array[3].isCasal = 1;

    array[4].nome = 'Howard';
    array[4].isCasal = 1;

    array[5].nome = 'Bernadette';
    array[5].isCasal = 1;

    array[6].nome = 'Stuart';
    array[6].isCasal = 0;
    
    array[7].nome = 'Kripke';
    array[7].isCasal = 0;

    return array;

};
