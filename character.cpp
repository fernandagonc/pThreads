#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <random>

#include "character.hpp"

using namespace std;

random_device rd; // obtain a random number from hardware
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(3, 6); // define the range


Personagem::Personagem(){};

Personagem::Personagem(string nome, bool isCasal, int nroVezesUsoForno){
    this->nroVezesUsoForno = nroVezesUsoForno;
    this->nome = nome;
    this->isCasal = isCasal;
}

void Personagem::esquentarAlgo() {
    cout << this->nome << " começa a esquentar algo\n";
    sleep(1);
}

void Personagem::comer() {
    cout << this->nome << " vai comer\n";
    sleep(distr(gen));
}

void Personagem::trabalhar() {
    cout << this->nome << " voltou para o trabalho\n";
    sleep(distr(gen));
}