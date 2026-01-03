//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)


#ifndef HIGHWAY_H
#define HIGHWAY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

struct VarcoSvincolo {	//struttura per i varchi e gli svincoli
    int id;				//identificativo
    double km;			//distanza dall'inizio dell'autostrada
    char tipo;			//'V' per varco e 'S' per svincolo
};

class Highway {

private:
    std::vector<VarcoSvincolo> varchi;//varchi
	std::vector<VarcoSvincolo> svincoli;     //svincoli 
	    
        void restrizioniC(const std::vector<VarcoSvincolo>& varchi, const std::vector<VarcoSvincolo>& svincoli);      //controllo delle restrizioni
        void idRiconoscimento(std::vector<VarcoSvincolo>& elementi);                                                          //assegnazione degli id
        void readFile(std::ifstream& fileInput, std::vector<VarcoSvincolo>& varchi, std::vector<VarcoSvincolo>& svincoli); //lettura del file di input

public:
    
    Highway(const std::string& filename);                                       		//costruttore che legge il file di input
        const std::vector<VarcoSvincolo>& getVarchi() const { return varchi; }          //getter varchi
        const std::vector<VarcoSvincolo>& getSvincoli() const { return svincoli; }    	//getter svincoli

		double gateKm(int id) const;
};

#endif
