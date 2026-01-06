//Autore : Andrea Vadori appartenente al gruppo: "C++2.0" (collaboratori : Giacomo Dal Poz e Andrea Moratto)

#ifndef TUTOR_H
#define TUTOR_H

#include "../Include/Highway.h"
#include <string>
#include <vector>
#include <unordered_map> //struttura dati utilizzata

//#include <unordered_map>:implementa una tabella Hash. Permette di accedere al dato quasi istantaneamente, (O(1))

//Singolo passaggio letto dal file
struct Transito{
  int idVarco;
  std::string targa;
  double timestamp;
};

//Memo per sapere dove si trovava l'auto
struct DatiVeicolo{
  int idUltimoVarco;
  double ultimoTempo;
};

class Tutor{
  private:
      std::vector<Transito> storicoTransiti; //tutti i dati
      size_t indice;
      double tempoAttuale;
      std::unordered_map<std::string, DatiVeicolo> veicoliAttivi;

      //variabili per statitiche(media, multe ecc...)
      long conteggioMulte;
      double sommaVelocita;
      long conteggioMisurazioni;

      //conteggio dei passaggi su ogni varco
      std::unordered_map<int,int> statisticheVarchi;

public:
      Tutor();//costruttore

      //carica file transiti
      bool init(const std::string& nomeFile);
      //Gestione temporale e controllo velocita
      void updateTime(double nuovoIstante, const Highway& autostrada);
      
      void reset();
      //Output riepilogo
      void showStats();

      double getTempoAttuale() const { return tempoAttuale; }
};
#endif
