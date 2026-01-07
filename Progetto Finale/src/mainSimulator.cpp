//Autore : Giacomo Dal Poz appartenente al gruppo: "C++2.0" (collaboratori : Andrea Moratto e Andrea Vadori)

#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>

#include "../Include/Highway.h"
#include "../Include/Veicolo.h"

void testaHighway(const std::string& path, const std::string& filename);
double tempoPassato(const std::vector<VarcoSvincolo>& varchi, int indexVarco, const Veicolo& veicolo);
void outputGenerator(const Highway& hMap, std::ofstream& fileRuns, std::ofstream& filePassages);

int main()
{
    srand(time(0));

    /*
    //TEST MANUALE eccezioni funzione restrizioniC di Highway.cpp - lettura mappe autostradali sbagliate con generazione errori. POCO EFFICACE.
    //errore: meno di 2 varchi -> test Highway2.txt deve fallire
    try {
        Highway hMap2("Data/tester Highways/Highway2.txt"); 
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    
    //errore: meno di 2 svincoli -> test Highway3.txt deve fallire
    try {
        Highway hMap3("Data/tester Highways/Highway3.txt");
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    //errore: manca almeno uno svincolo prima del primo varco -> test Highway4.txt deve fallire
    try {
        Highway hMap4("Data/tester Highways/Highway4.txt");
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    //errore: manca almeno uno svincolo dopo l'ultimo varco -> test Highway5.txt deve fallire
    try {
        Highway hMap5("Data/tester Highways/Highway5.txt");
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl; 
    }

    //errore: distanza minima non rispettata -> test Highway6.txt deve fallire
    try {
        Highway hMap6("Data/tester Highways/Highway6.txt");
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl; 
    }
    */

    //Test eccezioni funzione restrizioniC di Highway.cpp ufficiale
    testaHighway("Data/tester Highways/Highway2.txt", "Highway2.txt");
    testaHighway("Data/tester Highways/Highway3.txt", "Highway3.txt");
    testaHighway("Data/tester Highways/Highway4.txt", "Highway4.txt");
    testaHighway("Data/tester Highways/Highway5.txt", "Highway5.txt");
    testaHighway("Data/tester Highways/Highway6.txt", "Highway6.txt");

    //Creazione mappa autostradale corretta e generazione degli output
    try{
        
        Highway hMap("Data/Highway.txt");      //creazione mappa autostradale

        std::ofstream fileRuns("Data/Runs.txt", std::ios::trunc); //file di output per i viaggi. std::ios::trunc sovrascrive il file già presente (lo fa già di default ofstream, ma lo esplicito per chiarezza)
        if (!fileRuns) {
            std::cerr << "Errore: impossibile creare Data/Runs.txt\n";
            return -1;
        }

        std::ofstream filePassages("Data/Passages.txt", std::ios::trunc); //file di output per i passaggi ai varchi
        if (!filePassages) {
            std::cerr << "Errore: impossibile creare Data/Passages.txt\n";
            return -1;
        }

        
        outputGenerator(hMap, fileRuns, filePassages);  //generazione degli output: file dei viaggi e file dei passaggi ai varchi
        fileRuns.close();       //chiusura del file dei viaggi. Per chiarezza vengono esplicitati, anche se lo fa già la funzione ofstream
        filePassages.close();   //chiusura del file dei passaggi ai varchi

        std::cout<<"File Passages.txt e Runs.txt generati con successo." << std::endl;
        
        }
        catch(const std::exception& e)   //gestione errori mappa autostradale
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        
        return 0;
}
