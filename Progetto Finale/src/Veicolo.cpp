
//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)



#include "../Include/Veicolo.h"



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

//generatore speedG(aspetti generali come tempo e velocità) casuale
std::vector<std::pair<double, int>> Veicolo::generatoreSpeedG(double e, double u) 
{
    std::vector<std::pair<double, int>> tut;
    double distanza = u - e; // km rimanenti

    while (distanza > 0.0)
    {
        int speed = randomInt(MIN_SPEED, MAX_SPEED); // km/h
        double tempo = randomInt(5, 15);             // minuti

        double distanzaPercorribile = (speed * tempo) / 60.0; // km

        if (distanzaPercorribile >= distanza) {
            // ultimo tratto: percorro solo ciò che rimane
            double tempoNecessario = (distanza * 60.0) / speed;
            tut.push_back({tempoNecessario, speed});
            break; // distanza esattamente coperta
        } else {
            // tratto completo
            tut.push_back({tempo, speed});
            distanza -= distanzaPercorribile;
        }
    }

    return tut;
}


Veicolo::Veicolo(double e, double u, int a, int b, double t, std::string d) : entroKm{e}, escoKm{u}, entroId{a}, escoId{b}, ingressoS{t}, distanza{u-e}, data{d}
{
    if(entroKm<0 || escoKm<0 || escoKm<entroKm || ingressoS<0 || entroId<0 || escoId<0 || entroId>escoId) {  //possibili errori
        throw std::invalid_argument("Errore di entrata o uscita dall'autostrada nel tempo ");
    }
        
    tg=generatoreTg();    
    speedG=generatoreSpeedG(entroKm, escoKm);
}


std::ostream& operator<<(std::ostream& os, const Veicolo& v)        //overload dell'operatore di output
{
    os << v.getTg() << " " << v.getEntroId() << " " << v.getEscoId() << " "<< v.getIngressoS() << " "; //targa, id varco ingresso, id varco uscita, tempo di ingresso
    size_t i=0;
    while(i<v.getSpeedG().size())
    {
        os << v.getSpeedG()[i].second << " " << v.getSpeedG()[i].first;   //velocità , tempo
        if(i!=v.getSpeedG().size()-1)
            os << ", ";  
        i++;
    }
    os << std::endl;
    return os;
}


