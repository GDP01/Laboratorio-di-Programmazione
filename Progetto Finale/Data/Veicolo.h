//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)



#ifndef VEICOLO_H
#define VEICOLO_H
#include <iostream>
#include <ctime>
#include <vector>




static const std::string LETTERE_POSSIBILI ="ABCDEFGHJKLMNPRSTVWXYZ";
static const int MAX_SPEED=190; //km/h
static const int MIN_SPEED=80;  //km/h


class Veicolo {

private:
        double entroKm;                                                 //km dall'inizio dell'autostrada di ingresso
        double escoKm;                                                  //km dall'inizio dell'autostrada di uscita
        int entroId;                                                    //id del varco di ingresso  
        int escoId;                                                     //id del varco di uscita
        double ingressoS;                                               //secondi dal'inizio della simulazione
        std::string data;                                               //data di ingresso
        std::string tg;                                              	//targa del veicolo
        double distanza;                                                   //km totali da percorrere
        std::vector<std::pair<double, int>> speedG;                  //<tempo in minuti, velocita  in km/h>
        int randomInt(int min, int max);
        std::string generatoreTg();                                                 //generatore targa casuale
        std::vector<std::pair<double, int>> generatoreSpeedG(double e, double u);   //generatore speedG(aspetti generali come tempo e velocita)  casuale
   




public:
    	Veicolo(double e, double u, int a, int b, double t, std::string d);

        virtual ~Veicolo() {}

        double getEntroKm() const { return entroKm; }
        double getEscoKm() const { return escoKm; }
        int getEntroId() const { return entroId; }
        int getEscoId() const { return escoId; }
        double getIngressoS() const { return ingressoS; }
        std::string getData() const { return data; }
        std::string getTg() const { return tg; }
        std::vector<std::pair<double, int>> getSpeedG() const { return speedG; }

};

std::ostream& operator<<(std::ostream& os, const Veicolo& tut);   //overload dell'operatore di output

#endif
