//@author : Andrea Vadori
#include "Tutor.h"
#include "Highway.h"
#include <iostream>
#include <string>

// Funzione per convertire il tempo 
double convertiTempo(const std::string& arg) {
    if (arg.empty()) return 0.0;

    // Se l'ultimo carattere è 'm'
    if (arg.back() == 'm') {
        // Rimuove e converte in minuti -> secondi
        std::string parteNum = arg.substr(0, arg.length() - 1);
        try {
            double minuti = std::stod(parteNum);
            return minuti * 60.0;
        } catch (...) {
            return -1.0; // Errore parsing
        }
    } else {
        // Sono secondi puri
        try {
            return std::stod(arg);
        } catch (...) {
            return -1.0;
        }
    }
}
int main() {
    Highway autostrada;
    try {
        autostrada.loadFromFile("../Data/Highway.txt");
    } catch (const std::exception& e) {
        std::cerr << "Errore caricamento autostrada: " << e.what() << std::endl;
        return -1;
    }
    Tutor tutor;
    if (!tutor.init("../Data/Passages.txt")) {
        std::cerr << "Errore: impossibile caricare Passages.txt. Esegui prima il simulatore." << std::endl;
        return -1;
    }

    std::cout << "Sistema Tutor Avviato. Comandi disponibili: set_time <t>, stats, reset, exit" << std::endl;

    //Comandi
    std::string comando;
    while (std::cin >> comando) {
        if (comando == "exit") {
            break;
        } 
        else if (comando == "set_time") {
            std::string inputTempo;
            std::cin >> inputTempo; // Legge l'argomento 
            
            double secondi = convertiTempo(inputTempo);
            if (secondi < 0) {
                std::cout << "Formato tempo non valido." << std::endl;
            } else {
                tutor.updateTime(tempoAttuale + secondi, autostrada); //ora faccio incrementale.
            }
        } 
        else if (comando == "stats") {
            tutor.showStats(highway);
        } 
        else if (comando == "reset") {
            tutor.reset();
        } 
        else {
            std::cout << "Comando sconosciuto." << std::endl;
        }
    }
    return 0;
}
