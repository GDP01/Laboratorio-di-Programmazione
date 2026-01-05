//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)

#include <iostream>
#include <ctime>

#include "../Include/Highway.h"
#include "../Include/Veicolo.h"

double tempoPassato(const std::vector<VarcoSvincolo>& varchi, int indexVarco, const Veicolo& veicolo);
void outputGenerator(const Highway& hMap, std::ofstream& fileRuns, std::ofstream& filePassages);

int main()
{
    srand(time(0));

    //Test eccezioni funzione restrizioniC di Highway.cpp - lettura mappe autostradali sbagliate
    try {
        Highway hMap2("../Data/tester Highways/Highway2.txt");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl; //errore: meno di 2 varchi
    }

    try {
        Highway hMap3("../Data/tester Highways/Highway3.txt");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl; //errore: meno di 2 svincoli
    }

    try {
        Highway hMap4("../Data/tester Highways/Highway4.txt");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl; //errore: manca almeno uno svincolo prima del primo varco
    }

    try {
        Highway hMap5("../Data/tester Highways/Highway5.txt");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl; //errore: manca almeno uno svincolo dopo l'ultimo varco
    }

    try {
        Highway hMap6("../Data/tester Highways/Highway6.txt");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl; //errore: distanza minima non rispettata
    }


    //Creazione mappa autostradale corretta e generazione degli output
    try{
        
        Highway hMap("../Data/Highway.txt");      //creazione mappa autostradale
            
        std::ofstream fileRuns("../Data/Runs.txt");  //file di output per i viaggi
        try{
        if(!fileRuns.is_open())                                                     //gestione errore apertura file
            throw std::invalid_argument("Errore ! ");
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    
        std::ofstream filePassages("../Data/Passages.txt");   //file di output per i passaggi ai varchi
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
