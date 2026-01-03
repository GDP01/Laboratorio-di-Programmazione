//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)

#include <iostream>
#include <ctime>
#include "../Include/Veicolo.h"
#include "../Include/Highway.h"

int main()
{
    srand(time(0));
    try{
    
    Highway hMap("Highway.txt");      //creazione mappa autostradale
        
    std::ofstream fileRuns("Runs.txt");  //file di output per i viaggi
    try{
    if(!fileRuns.is_open())                                                     //gestione errore apertura file
        throw std::invalid_argument("Errore ! ");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    std::ofstream filePassages("Passages.txt");   //file di output per i passaggi ai varchi
    try{
    if(!filePassages.is_open())                                                     //gestione errore apertura file
        throw std::invalid_argument("Errore ! ");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    outputGenerator(hMap, fileRuns, filePassages);  //generazione degli output: file dei viaggi e file dei passaggi ai varchi
    fileRuns.close();       //chiusura del file dei viaggi
    filePassages.close();   //chiusura del file dei passaggi ai varchi
    }
    catch(const std::invalid_argument& e)   //gestione errori mappa autostradale
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
