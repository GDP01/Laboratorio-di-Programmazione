#ifndef HIGHWAY_H
#define HIGHWAY_H

#include <string>
#include <vector>
#include <stdexcept>
#include <cstddef>

/* 
   Questo file racchiude la struttura dell'autostrada (svincoli + varchi) letta da Highway.txt
   Funzionalità principali:
   - parsing del file
   - validazione vincoli (min 2 varchi, svincolo prima/dopo, distanza >= 1 km tra S e V,...)
   - assegnazione ID (separata per svincoli e varchi) in base alla distanza crescente
   - funzioni utili a simulator e tutor
*/

class Highway {
public:
    // Tipi di punti sull'autostrada
    enum class PointType { Gate, Interchange }; // Gate = Varco (V), Interchange = Svincolo (S)

    struct Point {
        PointType type{};
        double km{0.0}; // distanza dall'origine (km 0)
        int id{0}; // ID assegnato automaticamente: 1...N (separati per tipo)
    };

    struct Gate {
        int id{0};
        double km{0.0};
    };

    struct Interchange {   
        int id{0};
        double km{0.0};
    };

    enum class ErrorCode { 
        FileOpenFailed,
        ParseError, 
        UnknownType, // (carattere diverso da 'V'/'S')
        NegativeDistance, 
        NotEnoughGates, // (meno di 2 varchi)
        MissingInterchangeBeforeFirstGate,
        MissingInterchangeAfterLastGate,
        GateInterchangeTooClose, // (es. varco e svincolo a meno di 1 km)
        DuplicateSameTypeSameKm // (es. due varchi alla stessa distanza)
    };

    class HighwayError : public std::runtime_error {
    public:
        HighwayError(ErrorCode code, const std::string& msg) : std::runtime_error(msg), code_(code) {}
        ErrorCode code() const noexcept { return code_; } // uso noexcept perchè non deve mai lanciare eccezioni
    private:
        ErrorCode code_;
    };

    // Costanti vincoli
    static constexpr int minGates = 2; // minimo 2 varchi
    static constexpr double minGateInterchangeKm = 1.0; // distanza minima tra varco e svincolo

    // Costruttori e gestione risorse
    Highway() = default;

    // Costruisce e carica subito dal file (può lanciare HighwayError)
    explicit Highway(const std::string& highwayFilePath);

    // Ricarica/Resetta la struttura (svuota e rilegge)
    void loadFromFile(const std::string& highwayFilePath);

    // Svuota tutti i dati
    void clear() noexcept;

    // Stato caricamento
    bool isLoaded() const noexcept;

    // Accesso ai dati
    const std::vector<Gate>& gates() const noexcept;
    const std::vector<Interchange>& interchanges() const noexcept;

    // Tutti i punti (varchi+svincoli) in ordine crescente di km
    const std::vector<Point>& pointsSorted() const noexcept;

    // Contatore del numero di varchi/svincoli
    std::size_t gateCount() const noexcept;
    std::size_t interchangeCount() const noexcept;

    // Ritorna i km di un certo varco/svincolo per ID (1...N)
    // Lancia HighwayError se l'ID non è valido (0 < ID <= N)
    double gateKm(int gateId) const;
    double interchangeKm(int interchangeId) const;

    int firstGateId() const; // ID del primo varco (km minimo)
    int lastGateId() const; //ID dell'ultimo varco (km massimo)

    // Dato un tratto tra due varchi consecutivi (gateId -> gateId+1), ritorna la lunghezza in km
    double segmentLengthKm(int gateIdStart) const;

    // Restituisce gli ID dei varchi con km strettamente compreso tra (km_in, km_out)
    std::vector<int> gatesBetweenInterchanges(int inInterchangeId, int outInterchangeId) const;

    // Valida i vincoli richiesti (può lanciare HighwayError)
    void validate() const;

    // Helper function di parsing: converte 'V'/'S' in PointType (lancia HighwayError se non valido)
    static PointType parseTypeChar(char c);

private:
    bool loaded_{false};

    std::vector<Gate> gates_; // Varchi ordinati per km crescente, mantenendo l'id coerente
    std::vector<Interchange> interchanges_; // Svincoli ordinati per km crescente, mantenendo l'id coerente
    std::vector<Point> pointsSorted_; // ordinamento con merge di gates e interchanges

    // Funzioni intererne di supporto: legge le righe del file Highway.txt e produce un vettore di Point non ancora numerati (cioè con id=0)
    static std::vector<Point> readRawPoints(const std::string& highwayFilePath);

    // Ordina e assegna ID separati per tipo, poi popola gates/interchanges/pointsSorted
    void buildFromRaw(std::vector<Point>& raw);

    // Costruisce pointsSorted_ come merge di gates_ e interchanges_
    void rebuildPointsSorted();

    // Controllo vincolo distanza minima tra ogni gate e ogni interchange (>= 1 km)
    // Implementazione efficiente: due puntatori su liste ordinate
    void checkGateInterchangeMinDistance() const;

    // Controllo presenza svincolo prima del primo varco e dopo l'ultimo varco
    void checkInterchangesBeforeAfter() const;

    // Helper functions per verificare l'ID range
    void ensureGateIdValid(int gateId) const;
    void ensureInterchangeIdValid(int interchangeId) const;
};

#endif // HIGHWAY_H
