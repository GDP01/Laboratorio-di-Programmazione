/*// @author: Andrea Vadori

#include "Simulator.h"
#include "Highway.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

//Costruttore, inizializza generatore random
Simulator::Simulator(){
    std::random_device rd;
    gen = std::mt19937(rd());
}

double Simulator::generatoreTimeGap(){
    std::uniform_real_distribution<double> distanza(MIN_GAP_SECONDS, MAX_GAP_SECONDS);
    return distanza(gen);

int Simulator::pickRandomEntry(const Highway& highway){
    //Casting per size_t
    int maxId=static_cast<int>(highway.interchangeCount());
    //Evito di far entrare all'ultimo svincolo
    if(maxId<2) return 1;
    std::uniform_int_distribution<> dist(1, maxId-1);
    return dist(gen);
}

int Simulator::pickRandomExit(const Highway& highway, int entryId){
    int maxId=static_cast<int>(highway.interchangeCount());
    //Evito di far uscire al primo svincolo
    std::uniform_int_distribution<> dist(entryId+1, maxId);
    return dist(gen);

//TODO: finire simulaRun
void Simulator::simulaRun(const std::string& fileRuns, const std::string& filePassaggi, Highway& highway){
    std::ofstream outFile(fileRuns);

    if(!outFile.is_open()){
        std::cerr << "Errore: impossibile creare il file " << fileRuns << std::endl;
        return;
    }
    double tempoAttuale = 0.0; //istante 0 simulazione

    std::cout << "Generazione " << veicoliTotali << " veicoli in corso..." << std::endl;
    for(int i = 0; i < veicoliTotali; ++i){
        Vehicle veicolo;
        veicolo.generatoreTarga(gen);
        veicolo.entryNode = pickRandomEntry(highway)
        veicolo.exitNode = pickRandomExit(highway, veicolo.entryNode);
        double kmIn = highway.interchangeKm(veicolo.entryNode);
        double kmOut = highway.interchangeKm(veicolo.exitNode);

        veicolo.generaProfilo(kmOut-kmIn, gen);

        double gap = generaTimeGap();
        tempoAttuale += gap;
        veicolo.startTime = tempoAttuale;

        //Scrittura su Runs.txt
        outFile << veicolo.targa << " " << veicolo.entryNode << " " << veicolo.exitNode << " " << v.startTime<< " ";

        for(size_t k = 0; k<veicolo.profilo.size(); ++k) {
            outfile << v.profilo.size[k].speed << " " << veicolo.profilo[k].minuti; 
            if(k < veicolo.profilo.size()-1) outfile << ", ";
        }
        outfile << "\n";
        calcolaPassaggioVeicolo(veicolo, highway);
    }
    outFile.close();
    std::cout<< "File percorsi completato" << std::endl;
    scriviFilePassaggi(filePassaggi);
}
*/
