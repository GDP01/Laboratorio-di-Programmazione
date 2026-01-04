//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)

#include <iostream>
#include <ctime>

#include "../Include/Highway.h"
#include "../Include/Veicolo.h"

void testaHighway(const std::string& path, const std::string& descrizione);
double tempoPassato(const std::vector<VarcoSvincolo>& varchi, int indexVarco, const Veicolo& veicolo);
void outputGenerator(const Highway& hMap, std::ofstream& fileRuns, std::ofstream& filePassages);

int main()
{
    srand(time(0));

    //Test errori mappa autostradale
    testaHighway(".../Highway2.txt", "Meno di 2 varchi");                       //creazione mappa autostradale - errore: meno di 2 varchi
    testaHighway(".../Highway3.txt", "Meno di 2 svincoli");                     //creazione mappa autostradale - errore: meno di 2 svincoli
    testaHighway(".../Highway4.txt", "Manca svincolo prima del primo varco");   //creazione mappa autostradale - errore: manca almeno uno svincolo prima del primo varco
    testaHighway(".../Highway5.txt", "Manca svincolo dopo l'ultimo varco");     //creazione mappa autostradale - errore: manca almeno uno svincolo dopo l'ultimo varco
    testaHighway(".../Highway6.txt", "Distanza minima non rispettata");         //creazione mappa autostradale - errore: distanza minima non rispettata

    
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
