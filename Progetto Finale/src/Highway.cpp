//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)


#include "../Include/Highway.h"



void Highway::restrizioniC(const std::vector<VarcoSvincolo>& varchi, const std::vector<VarcoSvincolo>& svincoli, const std::string& filename)  //controllo delle restrizioni
{
    if (varchi.size() < 2)
        throw std::invalid_argument("Necessari almeno due varchi sull'autostrada."); // file Highway2.txt
    if (svincoli.size() < 2)
        throw std::invalid_argument("Necessari almeno due svincoli sull'autostrada."); // file Highway3.txt
    if (!(svincoli.front().km < varchi.front().km))
        throw std::invalid_argument("Serve almeno uno svincolo prima del primo varco."); // file Highway4.txt
    if (!(svincoli.back().km > varchi.back().km))
        throw std::invalid_argument("Serve almeno uno svincolo dopo l'ultimo varco."); // file Highway5.txt

    // check distanza minima di 1 km tra ogni varco e svincolo
    size_t i=0, j=0; //uso size_t per evitare warning di conversione tra tipi
    while (i < varchi.size() && j < svincoli.size()) 
    {
        if (std::abs(varchi[i].km - svincoli[j].km) < 1) 
        {
            throw std::invalid_argument("Errore nel file " + filename + ": Distanza minima non rispettata."); // file Highway6.txt
        }

        // porta avanti l'indice del varco se il varco si trova prima dello svincolo
        if (varchi[i].km < svincoli[j].km) ++i;
        else ++j;
    }
}



void Highway::idRiconoscimento(std::vector<VarcoSvincolo>& elementi)  //assegnazione degli id
{
    for(size_t i=0; i<elementi.size(); i++) 
    {
        elementi[i].id=i+1;
    }
}



void Highway::readFile(std::ifstream& fileInput, std::vector<VarcoSvincolo>& varchi, std::vector<VarcoSvincolo>& svincoli, const std::string& filename)  //lettura del file di input
{
    std::string line;
    while(std::getline(fileInput, line))  //legge tutte le linee del file di input
    {
        std::istringstream ss(line);
        double km;
        char tipo;
        ss >> km >> tipo;
        if(tipo == 'V')
        {
            varchi.push_back({-1, km, tipo});
        }
        else if(tipo == 'S')
        {
            svincoli.push_back({-1, km, tipo});
        }
    }
    fileInput.close();    //chiusura del file di input
    
	std::sort(varchi.begin(), varchi.end(), [](const VarcoSvincolo& v1, const VarcoSvincolo& v2) {        //ordinamento  dei varchi in base ai km
        return v1.km < v2.km;
    });
    std::sort(svincoli.begin(), svincoli.end(), [](const VarcoSvincolo& s1, const VarcoSvincolo& s2) {  //ordinamento degli svincoli in base ai km
        return s1.km < s2.km;
    });
    


    restrizioniC(varchi, svincoli, filename); //controllo delle restrizioni

    idRiconoscimento(varchi);        // id ai varchi
    idRiconoscimento(svincoli);     // id agli svincoli

}



Highway::Highway(const std::string& filename)      //costruttore che legge il file di input
{
    std::ifstream fileInput(filename);                   //apertura del file di input
    if(!fileInput.is_open())
    throw std::invalid_argument("Errore nell'apertura del file " + filename);  //gestione errore apertura file

    readFile(fileInput, varchi, svincoli, filename);  //lettura del file di input
}



double Highway::gateKm(int id) const
{
    for(const auto& varco : varchi)
    {
        if(varco.id == id)
        {
            return varco.km;
        }
    }
    throw std::invalid_argument("ID varco non valido.");
}
