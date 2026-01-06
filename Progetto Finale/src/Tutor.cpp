//Autore : Andrea Vadori appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Moratto)

#include "../Include/Tutor.h"
#include "../Include/Highway.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

Tutor::Tutor() {
    reset();
}

void Tutor::reset(){
  veicoliAttivi.clear();
  statisticheVarchi.clear();

  indice=0;
  tempoAttuale = 0.0;
  conteggioMulte = 0;
  sommaVelocita = 0.0;
  conteggioMisurazioni = 0;
  std::cout << "Tutor resettato" << std::endl;
}

bool Tutor::init(const std::string& nomeFile){
  std::ifstream file(nomeFile);
  if(!file.is_open()){
      std::cerr<< "Impossibile aprire "<< nomeFile << std::endl;  
      return false;
  }

  storicoTransiti.clear();
    
  Transito transito; 
  //lettura file -> <varco><targa><tempo>
  while(file >> transito.idVarco >> transito.targa >> transito.timestamp){
      storicoTransiti.push_back(transito);
  }
file.close();
std::cout << "Caricati "<< storicoTransiti.size()<<" transiti"<< std::endl;
return true;
}

void Tutor::updateTime(double nuovoIstante, const Highway& autostrada){
  if(nuovoIstante < tempoAttuale){
    std::cerr << "Errore: puoi solo andare avanti con il tempo" << std::endl;
    return;
  }
  while(indice < storicoTransiti.size()){
      const auto& transitoCorrente = storicoTransiti[indice];
      if(transitoCorrente.timestamp>nuovoIstante){
        break;
      }
        //aggiornamento statistiche 
        statisticheVarchi[transitoCorrente.idVarco]++;

        //uso auto per aiutarmi con i tipi di dati
        auto v = veicoliAttivi.find(transitoCorrente.targa);
        if (v != veicoliAttivi.end()){
          // Già tracciato recupero dati ultimo passaggio
          int idVarcoPrecedente = v->second.idUltimoVarco;
          double tempoPrecedente = v->second.ultimoTempo;

          // presi da Highway
          double kmPrim = autostrada.gateKm(idVarcoPrecedente); 
          double kmAtt = autostrada.gateKm(transitoCorrente.idVarco);

          // Calcoli utili
          double distKm = std::abs(kmAtt - kmPrim);
          double diffSecondi = transitoCorrente.timestamp - tempoPrecedente;
          if(diffSecondi > 0.1){
            double diffOre = diffSecondi / 3600.0;
            double velocitaMedia = distKm / diffOre;

            //aggiornamento statistiche globali
            sommaVelocita += velocitaMedia;
            conteggioMisurazioni++;

            //controllo se sanzione o no(130 km/h)
            if(velocitaMedia > 130.0){
              conteggioMulte++;
              //output
              std::cout << "MULTA: Veicolo " << transitoCorrente.targa << "\n" << "  Tratta: Varco " << idVarcoPrecedente << " (" << kmPrim << "km) -> " << "Varco " << transitoCorrente.idVarco << " (" << kmAtt << "km)\n" << "  Velocita' Media: " << std::fixed << std::setprecision(2) << velocitaMedia << " km/h\n" << "  Passaggi: t1=" << tempoPrecedente << "s, t2=" << transitoCorrente.timestamp << "s\n"<< std::endl;
            }
          }
        }
        veicoliAttivi[transitoCorrente.targa] = {transitoCorrente.idVarco, transitoCorrente.timestamp};
        indice++;
      }
      tempoAttuale = nuovoIstante;
      std::cout << "Tempo aggiornato a: " << tempoAttuale << "s" << std::endl;
}  
void Tutor::showStats() {
    std::cout << "Veicoli sanzionati finora: " << conteggioMulte << std::endl;
    
    double mediaGlobale = (conteggioMisurazioni > 0) ? (sommaVelocita / conteggioMisurazioni) : 0.0;

    //fixed-setprecision(2) per avere la parte decimale della velocità a due cifre 
    std::cout << "Velocita' media globale rilevata: " << std::fixed << std::setprecision(2) << mediaGlobale << " km/h" << std::endl;

    std::cout << "Traffico per varco:" << std::endl;
    // Contatori dei varchi
    for (const auto& pair : statisticheVarchi) {
        // Calcolo veicoli al minuto, evito divisione per zero
        double veicoliPerMinuto = (tempoAttuale > 0) ? (pair.second / (tempoAttuale / 60.0)) : 0.0;
        
        std::cout << "  Varco " << pair.first << ": " << pair.second << " veicoli ("<< veicoliPerMinuto << " veic/min)" << std::endl;
    }
}
