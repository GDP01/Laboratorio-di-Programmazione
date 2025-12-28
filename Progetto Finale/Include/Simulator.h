//@author : Andrea Vadori

//Definisce la classe Simulator che gestisce il ciclo di vita della simulazione.

#ifndef SIMULATOR_H
#define SIMULATOR_H

//#include "Vehicle.h"
#include "Highway.h"
#include <vector>
#include <string>
#include <random> //per std::mt19937

//Salvo i dati dei transiti
struct Transito{
    int idVarco;
    std::string targa;
    double tempoPassaggio;
    //Ordine cronologico dei passaggi
    bool operator<(const Transito& other) const{
          return tempoPassaggio < other.tempoPassaggio;
    }
};

class Simulator{
private:
    //Costanti progetto
    const int VEICOLI_TOTALI = 10000;
    const double GAP_MINIMO = 0.5;
    const double GAP_MASSIMO =10.0;

    //Generatore numeri casuali
    std::mt19937 gen;

    //Buffer per accumulare transiti prima di scriverli in output
    std::vector<Transito> bufferTransiti;

public:
    Simulator(); //Costruttore

    //Metodo principale per la simulazione
    void run(const std::string& fileRuns, const std::string& filePassaggi, const Highway& highway);

private:
    //Metodi interni
    //Genera gap temporale tra un veicolo e quello successivo
    double generatoreTimeGap();

    //Scelta casuale di ID svincolo d'ingresso
    int pickRandomEntry(const Highway& highway);

    //scelta casuale di ID svincolo di uscita
    int pickRandomExit(const Highway& highway);

    //Calcola quando veicolo passa sotto i varchi. Riempie il buffer
    void calcolaPassaggiVeicolo(const Vehicle& v, const Highway& highway);

    //Scrive il file Passages.txt
    void scriviFilePassaggi(const std::string& filename);
};
#endif
    
