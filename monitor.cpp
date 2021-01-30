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

    // this->lock = PTHREAD_MUTEX_INITIALIZER;
    initCond(&sheldonCond);
    initCond(&amyCond);
    initCond(&howardCond);
    initCond(&bernadetteCond);
    initCond(&leonardCond);
    initCond(&pennyCond);
    initCond(&stuartCond);
    initCond(&kripkeCond);
    primeiroDaFila = "";

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

void printFila(list <string> g) { 
    cout << "FILA: ";
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout << *it  << ", "; 
    cout << '\n'; 
} 


list<string>::iterator posicaoPersonagemNaFila(string nome){
    auto it = find(fila.begin(), fila.end(), nome);
    return it;
}

void passarPessoaNaFrente(string nome){
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
                    passarPessoaNaFrente("Amy");
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
                    passarPessoaNaFrente("Bernadette");
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
                    passarPessoaNaFrente("Penny");
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
                    passarPessoaNaFrente("Sheldon");
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
                    passarPessoaNaFrente("Howard");
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
                    passarPessoaNaFrente("Leonard");
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

void Monitor::waitPersonagem(string nome){
    if(nome == "Sheldon"){
        condWait(&sheldonCond, &this->lock);         
    }
    else if(nome == "Howard"){
        condWait(&howardCond, &this->lock);
    }
    else if(nome == "Leonard"){
        condWait(&leonardCond, &this->lock);
    }
    else if(nome == "Amy"){
        condWait(&amyCond, &this->lock);
    }
    else if(nome == "Bernadette"){
        condWait(&bernadetteCond, &this->lock);
    }
    else if(nome == "Penny"){
        condWait(&pennyCond, &this->lock);
    }
    else if(nome == "Stuart"){
        condWait(&stuartCond, &this->lock);
    }
    else if(nome == "Kripke"){
        condWait(&kripkeCond, &this->lock);
    }

}



void Monitor::esperar(Personagem p){
    cout << p.nome << " quer usar o forno \n";
    
    adicionarPersonagemNaFila(p.nome);
    printFila(fila);

    if (pthread_mutex_lock(&this->lock) != 0) {
        cout << "pthread_mutex_lock error";
        exit(2);
    }
    
    if(fila.size() > 1){
        if(primeiroDaFila != p.nome){
            waitPersonagem(p.nome);
        }
    }
       
};

string acharCasal(string nome){
    if(nome == "Sheldon"){
        return "Amy";
    }
    else if (nome == "Amy"){
        return "Sheldon";
    }
    else if (nome == "Howard"){
        return "Bernadette";
    }
    else if (nome == "Bernadette"){
        return "Howard";
    }
    else if (nome == "Leonard"){
        return "Penny";
    }
    else if (nome == "Penny"){
        return "Leonard";
    }

    return "";
}

void acharOCasalEPassarNaFrente(string nome){

    string nomeCasal = acharCasal(nome);
    if (nomeCasal != ""){
        auto posicaoCasal = posicaoPersonagemNaFila(nomeCasal);
        bool casalNaFila = posicaoCasal != fila.end();
        if (casalNaFila){
            fila.remove(nomeCasal);
            fila.push_front(nomeCasal);
        }

        return;
    }
     return;
    
}


int qtdSheldonAmy (){
    auto posicaoAmy = posicaoPersonagemNaFila("Amy");
    auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
    int sheldonAmy = 0;
    if(posicaoSheldon != fila.end())
        sheldonAmy++;
    
    if(posicaoAmy != fila.end())
        sheldonAmy++;
    return sheldonAmy;
}

int qtdLeonardPenny(){
    auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
    auto posicaoPenny = posicaoPersonagemNaFila("Penny");
    
    int leonardPenny = 0;
    if(posicaoLeonard != fila.end())
        leonardPenny++;
    
    if(posicaoPenny != fila.end())
        leonardPenny++;

    return leonardPenny;
}

int qtdHowardBernadette(){
    auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
    auto posicaoHoward = posicaoPersonagemNaFila("Howard");

    int howardBernadette = 0;
    if(posicaoHoward != fila.end())
        howardBernadette++;
    
    if(posicaoBernadette != fila.end())
        howardBernadette++;

    return howardBernadette;

}

void reorganizarFila(){
    auto posicaoAmy = posicaoPersonagemNaFila("Amy");
    auto posicaoSheldon = posicaoPersonagemNaFila("Sheldon");
    auto posicaoBernadette = posicaoPersonagemNaFila("Bernadette");
    auto posicaoHoward = posicaoPersonagemNaFila("Howard");
    auto posicaoLeonard = posicaoPersonagemNaFila("Leonard");
    auto posicaoPenny = posicaoPersonagemNaFila("Penny");
    auto inicioFila = fila.begin();
    bool leonardNaFila = posicaoLeonard != fila.end();
    bool howardNaFila = posicaoHoward != fila.end();
    bool sheldonNaFila = posicaoSheldon != fila.end();

    int sheldonAmy = qtdSheldonAmy();
    int howardBernadette = qtdHowardBernadette();
    int leonardPenny = qtdLeonardPenny();

    if(sheldonAmy == 0){
        if(howardBernadette == 1){
            if(howardNaFila){
                passarPessoaNaFrente("Howard");
            }
            else{
                passarPessoaNaFrente("Bernadette");
            }
        }
        else {
            if(distance(inicioFila, posicaoBernadette) < distance(inicioFila, posicaoHoward)){
                passarPessoaNaFrente("Howard");
                passarPessoaNaFrente("Bernadette");
            }
            else{
                passarPessoaNaFrente("Bernadette");
                passarPessoaNaFrente("Howard");
            }
        }
    }
    else if(howardBernadette == 0){
        if(leonardPenny == 1){
            if(leonardNaFila){
                passarPessoaNaFrente("Leonard");
            }
            else{
                passarPessoaNaFrente("Penny");
            }
        }
        else{
             if(distance(inicioFila, posicaoPenny) < distance(inicioFila, posicaoLeonard)){
                passarPessoaNaFrente("Leonard");
                passarPessoaNaFrente("Penny");
            }
            else{
                passarPessoaNaFrente("Penny");
                passarPessoaNaFrente("Leonard");
            }
        }
    }
    else if(leonardPenny == 0){
        if(sheldonAmy == 1){
            if(sheldonNaFila){
                passarPessoaNaFrente("Sheldon");
            }
            else{
                passarPessoaNaFrente("Amy");
        
            }
        }
        else{
             if(distance(inicioFila, posicaoAmy) < distance(inicioFila, posicaoSheldon)){
                passarPessoaNaFrente("Sheldon");
                passarPessoaNaFrente("Amy");
            }
            else{
                passarPessoaNaFrente("Amy");
                passarPessoaNaFrente("Sheldon");
            }
        }
    }



}


bool precisaReorganizarFila(){
    int sheldonAmy = qtdSheldonAmy();
    int howardBernadette = qtdHowardBernadette();
    int leonardPenny = qtdLeonardPenny();

    if(sheldonAmy == 0 && howardBernadette == leonardPenny){
        if(howardBernadette > 0)
            return true;
    }
    if(howardBernadette == 0 && sheldonAmy == leonardPenny){
        if(sheldonAmy > 0)
            return true;
    }
    if(leonardPenny == 0 && sheldonAmy == howardBernadette){
        if(sheldonAmy > 0)
            return true;
    }
    

    return false;

} 

void Monitor::liberar(Personagem p){
    
    fila.remove(p.nome);
    if(precisaReorganizarFila())
        reorganizarFila();
    acharOCasalEPassarNaFrente(p.nome);
    primeiroDaFila = fila.front();
    printFila(fila);

    pthread_mutex_unlock(&this->lock); 
    
    if(primeiroDaFila != ""){
        liberarPersonagem(primeiroDaFila);
    }


};

bool hasDeadLock(){
    int sheldonAmy = qtdSheldonAmy();
    int howardBernadette = qtdHowardBernadette();
    int leonardPenny = qtdLeonardPenny();
    
    if (sheldonAmy == howardBernadette && howardBernadette == leonardPenny){
        if(sheldonAmy == 0)
            return false; //(apenas kripke e stuart na lista)
        return true;
    }

    return false;
    
}



void Monitor::verificar(){

    bool deadLock =  hasDeadLock();

    if(deadLock){
        string nome = fila.front();
        cout << "Raj detectou um deadlock, liberando: " << nome << "\n";
        liberarPersonagem(nome);
    }
       

    return;
};