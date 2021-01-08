#include <iostream>
#include "character.hpp"

using namespace std;

Personagem::Personagem(){};
Personagem::Personagem(string nome, bool isCasal, int nroVezesUsoForno){
    this->nroVezesUsoForno = nroVezesUsoForno;
    this->nome = nome;
    this->isCasal = isCasal;
}
