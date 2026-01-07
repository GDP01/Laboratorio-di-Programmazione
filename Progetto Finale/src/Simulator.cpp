//Autore : Moratto Andrea appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Vadori)

#include "../Include/Highway.h"
#include "../Include/Veicolo.h"


static const int NUM_VEICOLI=10000;    //numero di veicoli da generare

//funzione di controllo dei file autostrade
void testaHighway(const std::string& path, const std::string& filename) {
    try {
        Highway h(path);
        std::cout << "Errore in " << filename << " non ha lanciato eccezione (file: " << path << ")\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Errore in " << filename << " -> " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Errore in " << filename
                  << " -> eccezione diversa: " << e.what() << "\n";
    }
}

double tempoPassato(const std::vector<VarcoSvincolo>& varchi, int indexVarco, const Veicolo& veicolo) //calcolo del tempo di passaggio al varco
{
    double tempo=veicolo.getIngressoS();  //secondi
    double distanza=varchi[indexVarco].km-veicolo.getEntroKm(); //km
    double distanzaCoperta=0;
    size_t i=0;
    while(distanzaCoperta<distanza && i<veicolo.getSpeedG().size()) 
    {
        double distanzaPercorsa=(double)(veicolo.getSpeedG()[i].second*veicolo.getSpeedG()[i].first)/60; //km percorsi in questo segmento
        if(distanzaCoperta+distanzaPercorsa<=distanza)  //se il veicolo non supera la distanza del varco in questo segmento
        {
            tempo+=(double)(veicolo.getSpeedG()[i].first*60.0); //aumento il tempo con il tempo di questo segmento 
            distanzaCoperta+=distanzaPercorsa;                      //aggiorno la distanza coperta
        }
        else
        {
            double distanzaRimanente=distanza-distanzaCoperta; //km rimasti al varco
            double secondiNec=(double)(distanzaRimanente)/veicolo.getSpeedG()[i].second*3600.0; //secondi necessari per coprire la distanza rimanente
            tempo+=secondiNec;
            distanzaCoperta+=distanzaRimanente;
        }
        i++;
    }
    return tempo;
}

void outputGenerator(const Highway& hMap, std::ofstream& fileRuns, std::ofstream& filePassages)  //generazione degli output: file dei viaggi e file dei passaggi ai varchi
{
    double ingressoS=0;                  //inizializzo il tempo di ingresso a 0 secondi
    for(int i=0; i<NUM_VEICOLI; i++)     //generazione di veicoli
    {
        int indiceIn=rand()%(hMap.getSvincoli().size()-1);                        	//id casuale del varco di ingresso
        int indiceEx=rand()%(hMap.getSvincoli().size()-indiceIn-1)+indiceIn+1; 		//id casuale del varco di uscita
        
        double entroKm=hMap.getSvincoli()[indiceIn].km;
        double escoKm=hMap.getSvincoli()[indiceEx].km;
        ingressoS+=(double(rand()%96 + 5)/10.0);      //incremento il tempo di ingresso di un valore casuale tra 0.5 e 10 secondi compresi
        std::string data = "2026-01-01";                            //data fissa per tutti i veicoli

        try {     
            Veicolo v(entroKm, escoKm, hMap.getSvincoli()[indiceIn].id, hMap.getSvincoli()[indiceEx].id, ingressoS, data);     //creazione del veicolo
            fileRuns << v;  //scrittura del veicolo nel file dei viaggi
            
            size_t indexVarco=0;
            while (indexVarco < hMap.getVarchi().size() && hMap.getVarchi()[indexVarco].km < v.getEntroKm()) //trovo il primo varco dopo il punto di ingresso del veicolo
            {
                indexVarco++;
            }
            while(indexVarco<hMap.getVarchi().size() && v.getEscoKm()>hMap.getVarchi()[indexVarco].km)  //scrittura dei passaggi ai varchi nel file dei passaggi
            {
                filePassages << hMap.getVarchi()[indexVarco].id << " " << v.getTg() << " "<< tempoPassato(hMap.getVarchi(), indexVarco, v) << std::endl;
                indexVarco++;
            }
        } catch (const std::invalid_argument& e) {                              //gestione errori creazione veicolo
            std::cerr << "Errore nella creazione del veicolo  " << e.what() << std::endl;
            i--; 																// decremento i per rigenerare il veicolo
        }
    }
}
