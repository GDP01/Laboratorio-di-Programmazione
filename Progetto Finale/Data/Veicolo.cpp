
//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)



#include "Veicolo.h"



int Veicolo::randomInt(int min, int max)
{
    return min+rand()%(max-min+1);
}

std::string Veicolo::generatoreTg()      //generatore targa casuale
{
    std::string tg;
    for(int i=0; i<2; i++)
    {
        tg+= LETTERE_POSSIBILI[rand() % LETTERE_POSSIBILI.size()];
    }
    for(int i=0; i<3; i++)
    {
        tg+= std::to_string(rand() % 10);
    }
    for(int i=0; i<2; i++)
    {
        tg+= LETTERE_POSSIBILI[rand() % LETTERE_POSSIBILI.size()];
    }
    return tg;
}


std::vector<std::pair<double, int>> Veicolo::generatoreSpeedG(double e, double u)   //generatore speedG(aspetti generali come tempo e velocita)  casuale
{
    std::vector<std::pair<double, int>> tut;
    double distanza=u-e; //km
    while(distanza>0)
    { 
        int speed=randomInt(MIN_SPEED, MAX_SPEED); //km/h
        double tempo=randomInt(5, 15); //minuti
        distanza-=(double)(speed*tempo)/60.0; 
        if(distance<0)
            tempo+=(double)(distanza*60)/speed; //serve per coprire esattamente la distanza rimanente
        tut.push_back({tempo, speed});
    }
    return tut;
}


Veicolo::Veicolo(double e, double u, int a, int b, double t, std::string d) : entroKm{e}, escoKm{u}, entroId{a}, escoId{b}, distanza{u-e}, ingressoS{t}, data{d}
{
    if(entroKm<0 || escoKm<0 || escoKm<entroKm || ingressoS<0 || entroId<0 || escoId<0 || entroId>escoId)   //possibili errori
        throw std::invalid_argument("Errore di entrata o uscita dall'autostrada nel tempo ");

        tg=generatoreTg();

        speedG=generatoreSpeedG(entroKm, escoKm);
}


std::ostream& operator<<(std::ostream& os, const Veicolo& tut)        //overload dell'operatore di output
{
    os << tut.getTg() << " " << tut.getEntroId() << " " << tut.getEscoId() << " "<< tut.getIngressoS() << " "; //targa, id varco ingresso, id varco uscita, tempo di ingresso
    int i=0;
    while(i<tut.getSpeedG().size())
    {
        os << tut.getSpeedG()[i].second << " " << v.getSpeedG()[i].first;   //velocita , tempo
        if(i!=tut.getSpeedG().size()-1)
            os << ", ";  
        i++;
    }
    os << std::endl;
    return os;
}


