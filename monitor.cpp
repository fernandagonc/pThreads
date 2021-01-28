#include "monitor.hpp"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <unistd.h>

using namespace std;

bool isFornoLivre = true;
std::list<string> fila;

Monitor::Monitor() {

    this->lock = PTHREAD_MUTEX_INITIALIZER;
    initCond(&sheldonCond);
    initCond(&amyCond);
    initCond(&howardCond);
    initCond(&bernadetteCond);
    initCond(&leonardCond);
    initCond(&pennyCond);
    initCond(&stuartCond);
    initCond(&kripkeCond);
    this->controleThreadsCriadas = 0;

    if (pthread_mutex_init(&this->lock, NULL) != 0) { 
        cout << "\n Inicialização mutex falhou.\n"; 
    } 


};

void Monitor::initCond(pthread_cond_t* cond){
    if (pthread_cond_init(cond, NULL) != 0) {
        perror("condInit error");
        exit(2);
    }
}

void Monitor::condSignal(pthread_cond_t* cond) {
    if (pthread_cond_signal(cond) != 0) {
        perror("condSignal error");
        exit(2);
    }
}

void Monitor::condWait(pthread_cond_t* cond, pthread_mutex_t* mutex) {
    if (pthread_cond_wait(cond, mutex) != 0) {
        perror("condWait() error");
        exit(2);
    }
}
void printFila(list <string> g) 
{ 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << *it  << ", "; 
    cout << '\n'; 
} 


list<string>::iterator posicaoPersonagemNaFila(string nome){
    auto it = find(fila.begin(), fila.end(), nome);
    return it;
}

void passarPrimeiroDoCasalNaFrente(string nome){
    fila.remove(nome);
    fila.push_front(nome);
}

void adicionarPersonagemNaFila(string nome){
    auto inicioFila = fila.begin();

    if (nome == "Sheldon"){
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

        bool pennyNaFila = posicaoPenny != fila.end();
        bool leonardNaFila = posicaoLeonard != fila.end();
        bool amyNaFila = posicaoAmy != fila.end();
        bool howardEBernadetteNaFila = posicaoHoward != fila.end() && posicaoBernadette != fila.end();

        if(amyNaFila){
            if(!leonardNaFila || !pennyNaFila){
                    passarPrimeiroDoCasalNaFrente("Amy");
                    posicaoAmy = posicaoPersonagemNaFila("Amy");
                    fila.insert(++posicaoAmy, nome);
            }
            else{
                fila.insert(++posicaoAmy, nome);
               
            }
        }
        else{
           if(!leonardNaFila){
                if(!pennyNaFila){
                    if(!howardEBernadetteNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoBernadette) < distance(inicioFila, posicaoHoward))
                            fila.insert(++posicaoHoward, nome);
                    else
                         fila.insert(++posicaoBernadette, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoPenny, nome);
                }
           }
           else{
               if(pennyNaFila){
                   if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                        fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);

               }
               else{
                   fila.insert(++posicaoLeonard, nome);
               }
           }
        }

    }

    else if(nome == "Howard"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        bool bernadetteNaFila = posicaoBernadette != fila.end();
        bool sheldonNaFila = posicaoSheldon != fila.end();
        bool amyNaFila = posicaoAmy != fila.end();
        bool leonardEPennyNaFila = posicaoLeonard != fila.end() && posicaoPenny != fila.end();

        if(bernadetteNaFila){
            if(!sheldonNaFila || !amyNaFila){
                    passarPrimeiroDoCasalNaFrente("Bernadette");
                    posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
                    fila.insert(++posicaoBernadette, nome);
            }
            else{
                    fila.insert(++posicaoBernadette, nome);               
            }
        }
        else{
           if(!sheldonNaFila){
                if(!amyNaFila){
                    if(!leonardEPennyNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                            fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoAmy, nome);
                }
           }
           else{
               if(amyNaFila){
                   if(distance(inicioFila, posicaoAmy) < distance(inicioFila, posicaoSheldon))
                        fila.insert(++posicaoSheldon, nome);
                    else
                         fila.insert(++posicaoAmy, nome);
               }
                else{
                   fila.insert(++posicaoSheldon, nome);
               }
           }
        }
    }
    else if(nome == "Leonard"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        bool pennyNaFila = posicaoPenny != fila.end();
        bool howardNaFila = posicaoHoward != fila.end();
        bool bernadetteNaFila = posicaoBernadette != fila.end();
        bool sheldonEAmyNaFila = posicaoSheldon != fila.end() && posicaoAmy != fila.end();

        if(pennyNaFila){
            if(!howardNaFila || !bernadetteNaFila){
                    passarPrimeiroDoCasalNaFrente("Penny");
                    posicaoPenny = posicaoPersonagemNaFila("Penny");
                    fila.insert(++posicaoPenny, nome);
            }
            else{
                fila.insert(++posicaoPenny, nome);             
            }
        }
        else{
           if(!howardNaFila){
                if(!bernadetteNaFila){
                    if(!sheldonEAmyNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoAmy) < distance(inicioFila, posicaoSheldon))
                            fila.insert(++posicaoSheldon, nome);
                    else
                         fila.insert(++posicaoAmy, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoBernadette, nome);
                }
           }
           else{
               if(bernadetteNaFila){
                   if(distance(inicioFila, posicaoBernadette) < distance(inicioFila, posicaoHoward))
                        fila.insert(++posicaoHoward, nome);
                    else
                         fila.insert(++posicaoBernadette, nome);
                }
                else{
                   fila.insert(++posicaoHoward, nome);
               }
            }
        }
    }
    else if (nome == "Amy"){
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

        bool pennyNaFila = posicaoPenny != fila.end();
        bool leonardNaFila = posicaoLeonard != fila.end();
        bool sheldonNaFila = posicaoSheldon != fila.end();
        bool howardEBernadetteNaFila = posicaoHoward != fila.end() && posicaoBernadette != fila.end();

        if(sheldonNaFila){
            if(!leonardNaFila || !pennyNaFila){
                    passarPrimeiroDoCasalNaFrente("Sheldon");
                    posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
                    fila.insert(++posicaoSheldon, nome);
            }
            else{
                fila.insert(++posicaoSheldon, nome);
               
            }
        }
        else{
           if(!leonardNaFila){
                if(!pennyNaFila){
                    if(!howardEBernadetteNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoBernadette) < distance(inicioFila, posicaoHoward))
                            fila.insert(++posicaoHoward, nome);
                    else
                         fila.insert(++posicaoBernadette, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoPenny, nome);
                }
           }
           else{
               if(pennyNaFila){
                   if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                        fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);
               }
                else{
                   fila.insert(++posicaoLeonard, nome);
               }
           }
        }


    }
    else if(nome == "Bernadette"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoPenny = posicaoPersonagemNaFila("Penny");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        bool howardNaFila = posicaoHoward != fila.end();
        bool sheldonNaFila = posicaoSheldon != fila.end();
        bool amyNaFila = posicaoAmy != fila.end();
        bool leonardEPennyNaFila = posicaoLeonard != fila.end() && posicaoPenny != fila.end();

        if(howardNaFila){
            if(!sheldonNaFila || !amyNaFila){
                    passarPrimeiroDoCasalNaFrente("Howard");
                    posicaoHoward = posicaoPersonagemNaFila("Howard");
                    fila.insert(++posicaoHoward, nome);
            }
            else{
                fila.insert(++posicaoHoward, nome);           
            }
        }
        else{
           if(!sheldonNaFila){
                if(!amyNaFila){
                    if(!leonardEPennyNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard))
                            fila.insert(++posicaoLeonard, nome);
                    else
                         fila.insert(++posicaoPenny, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoAmy, nome);
                }
           }
           else{
               if(amyNaFila){
                   if(distance(inicioFila, posicaoAmy) < distance(inicioFila, posicaoSheldon))
                        fila.insert(++posicaoSheldon, nome);
                    else
                         fila.insert(++posicaoAmy, nome);
               }
                else{
                   fila.insert(++posicaoSheldon, nome);
               }
           }
        }
    }
    else if(nome == "Penny"){
        auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
        auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
        auto posicaoHoward = posicaoPersonagemNaFila("Howard");
        auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
        auto posicaoAmy = posicaoPersonagemNaFila("Amy");

        bool leonardNaFila = posicaoLeonard != fila.end();
        bool howardNaFila = posicaoHoward != fila.end();
        bool bernadetteNaFila = posicaoBernadette != fila.end();
        bool sheldonEAmyNaFila = posicaoSheldon != fila.end() && posicaoAmy != fila.end();

        if(leonardNaFila){
            if(!howardNaFila || !bernadetteNaFila){
                    passarPrimeiroDoCasalNaFrente("Leonard");
                    posicaoLeonard = posicaoPersonagemNaFila("Leonard");
                    fila.insert(++posicaoLeonard, nome);
            }
            else{
                fila.insert(++posicaoLeonard, nome);               
            }
        }
        else{
           if(!howardNaFila){
                if(!bernadetteNaFila){
                    if(!sheldonEAmyNaFila){
                        fila.push_front(nome);
                    }
                    else{
                        if(distance(inicioFila, posicaoAmy) < distance(inicioFila, posicaoSheldon))
                            fila.insert(++posicaoSheldon, nome);
                    else
                         fila.insert(++posicaoAmy, nome);
                    }
                }   
                else{
                    fila.insert(++posicaoBernadette, nome);
                }
           }
           else{
               if(bernadetteNaFila){
                   if(distance(inicioFila, posicaoBernadette) < distance(inicioFila, posicaoHoward))
                        fila.insert(++posicaoHoward, nome);
                    else
                         fila.insert(++posicaoBernadette, nome);
                }
                else{
                   fila.insert(++posicaoHoward, nome);
               }
            }
        }
    }
    else if(nome == "Stuart"){
        auto posicaoKripke = posicaoPersonagemNaFila("Kripke");

        if(posicaoKripke == fila.end()){
            fila.push_back(nome);
        }
        else{
            fila.insert(posicaoKripke, nome);
        }

    }
    else if(nome == "Kripke"){
        fila.push_back(nome);
    }
    else{
        fila.push_back(nome);
    }
}

void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    
    adicionarPersonagemNaFila(p.nome);
    cout << "LISTA: ";
    printFila(fila);

    if (pthread_mutex_lock(&this->lock) != 0) {
        cout << "pthread_mutex_lock error";
        exit(2);
    }

    if(p.nome == "Sheldon"){
        condWait(&sheldonCond, &this->lock);         
    }
    else if(p.nome == "Howard"){
        condWait(&howardCond, &this->lock);
    }
    else if(p.nome == "Leonard"){
        condWait(&leonardCond, &this->lock);
    }
    else if(p.nome == "Amy"){
        condWait(&amyCond, &this->lock);
    }
    else if(p.nome == "Bernadette"){
        condWait(&bernadetteCond, &this->lock);
    }
    else if(p.nome == "Penny"){
        condWait(&pennyCond, &this->lock);
    }
    else if(p.nome == "Stuart"){
        condWait(&stuartCond, &this->lock);
    }
    else if(p.nome == "Kripke"){
        condWait(&kripkeCond, &this->lock);
    }

    fila.remove(p.nome);


};

void Monitor::liberarPersonagem(string nome){
    
    if(nome == "Sheldon"){
        condSignal(&sheldonCond);         
    }
    else if(nome == "Howard"){
        condSignal(&howardCond);
    }
    else if(nome == "Leonard"){
        condSignal(&leonardCond);
    }
    else if(nome == "Amy"){
        condSignal(&amyCond);
    }
    else if(nome == "Bernadette"){
        condSignal(&bernadetteCond);
    }
    else if(nome == "Penny"){
        condSignal(&pennyCond);
    }
    else if(nome == "Stuart"){
        condSignal(&stuartCond);
    }
    else if(nome == "Kripke"){
        condSignal(&kripkeCond);
    }
}

void Monitor::liberar(Personagem p){
    
    cout << "liberar :";
    cout << "LISTA: ";
    printFila(fila);

    pthread_mutex_unlock(&this->lock); 
    liberarPersonagem(p.nome);
        
};

bool hasDeadLock(){
    auto posicaoHoward = posicaoPersonagemNaFila("Howard");
    auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
    auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");

    auto posicaoAmy = posicaoPersonagemNaFila("Amy");
    auto posicaoPenny = posicaoPersonagemNaFila("Penny");
    auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");

    int sheldonAmy = 0;
    if(posicaoSheldon != fila.end())
        sheldonAmy++;
        
    
    if(posicaoAmy != fila.end())
        sheldonAmy++;

    int leonardPenny = 0;
    if(posicaoLeonard != fila.end())
        leonardPenny++;
    
    if(posicaoPenny != fila.end())
            leonardPenny++;

    int howardBernadette = 0;
    if(posicaoHoward != fila.end())
        howardBernadette++;
        
    
    if(posicaoBernadette != fila.end())
            howardBernadette++;

    if (sheldonAmy == howardBernadette && howardBernadette == leonardPenny){
        return true;
    }

    return false;
    
}



void Monitor::verificar(){

    cout << "Verificando: ";

    bool deadLock =  hasDeadLock();

    if(deadLock){
        cout << "Deadlock \n";
        string nome = fila.front();
        liberarPersonagem(nome);
    }
    else
        cout << "Sem deadlocks \n";

    return;
};