//Autore : Giacomo Dal Poz appartenente al gruppo: "C++2.0" (collaboratori : Andrea Moratto e Andrea Vadori)

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <fstream>

#include "../Include/Highway.h"
#include "../Include/Veicolo.h"

//calcola il tempo in cui un veicolo passa al varco di indice indexVarco
double tempoPassato(const std::vector<VarcoSvincolo>& varchi, int indexVarco, const Veicolo& veicolo);

//genera i file Runs e Passages a partire dalla mappa autostradale.
void outputGenerator(const Highway& hMap, std::ofstream& fileRuns, std::ofstream& filePassages);

#endif



