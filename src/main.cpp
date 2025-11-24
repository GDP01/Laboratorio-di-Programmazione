#include <iostream>
#include <stdexcept>

#include "../include/InertialDriver.h"
#include "../include/lettura.h"
#include "../include/misura.h"

// Funzione che crea una misura con valori facilmente riconoscibili
misura build_misura(double base) {
    misura m;

    for (int i = 0; i < MISURA_LENGTH; ++i) {
        double b = base + i;
        m.mis[i] = lettura(
            b,
            b + 0.1,
            b + 0.2,
            b + 0.3,
            b + 0.4,
            b + 0.5
        );
    }
    return m;
}

// Stampa compatta di una singola lettura
void print_lettura(const lettura& l) {
    std::cout << "  yaw_v="   << l.get_yaw_v()
              << ", yaw_a="   << l.get_yaw_a()
              << ", pitch_v=" << l.get_pitch_v()
              << ", pitch_a=" << l.get_pitch_a()
              << ", roll_v="  << l.get_roll_v()
              << ", roll_a="  << l.get_roll_a()
              << std::endl;
}

int main() {
  std::cout << "=== INIZIO TEST INERTIALDRIVER ===" << std::endl;

    InertialDriver driver;

    // 1) Test push_back
    std::cout << "\n1) Test push_back con poche misure" << std::endl;
    misura m0 = build_misura(0.0);
    misura m1 = build_misura(100.0);
    misura m2 = build_misura(200.0);

    driver.push_back(m0);
    driver.push_back(m1);
    driver.push_back(m2);

    // 2) Test operator<<
    std::cout << "\n2) Test operator<< (ultima misura nel buffer):" << std::endl;
    std::cout << driver << std::endl;

    // 3) Test get_reading
    std::cout << "\n3) Test get_reading sulla misura piu' recente" << std::endl;
    try {
        int sensore = 0;
        lettura l0 = driver.get_reading(sensore);
        std::cout << "Lettura sensore 0:" << std::endl;
        print_lettura(l0);

        sensore = 10;
        lettura l10 = driver.get_reading(sensore);
        std::cout << "Lettura sensore 10:" << std::endl;
        print_lettura(l10);
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione in get_reading: " << e.what() << std::endl;
    }

    // 4) Test pop_front (FIFO)
    std::cout << "\n4) Test pop_front (First In First Out)" << std::endl;
    try {
        misura pf0 = driver.pop_front();
        misura pf1 = driver.pop_front();
        misura pf2 = driver.pop_front();

        std::cout << "Estratta base 0: yaw_v sensore 0 = "
                  << pf0.mis[0].get_yaw_v() << std::endl;
        std::cout << "Estratta base 100: yaw_v sensore 0 = "
                  << pf1.mis[0].get_yaw_v() << std::endl;
        std::cout << "Estratta base 200: yaw_v sensore 0 = "
                  << pf2.mis[0].get_yaw_v() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione in pop_front: " << e.what() << std::endl;
    }

    // 5) pop_front su buffer vuoto
    std::cout << "\n5) Test pop_front su buffer vuoto" << std::endl;
    try {
        misura px = driver.pop_front();
        (void)px;
        std::cout << "Errore: pop_front non ha lanciato eccezione!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione correttamente lanciata: " << e.what() << std::endl;
    }

    // 6) Test buffer circolare
    std::cout << "\n6) Test buffer circolare" << std::endl;
    driver.clear_buffer();

    for (int i = 0; i < BUFFER_DIM + 5; ++i) {
        driver.push_back(build_misura(i * 10.0));
    }

    try {
        misura oldest = driver.pop_front();
        double base_estratta = oldest.mis[0].get_yaw_v();

        std::cout << "Base estratta (atteso ~50): "
                  << base_estratta << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione in pop_front durante overflow: " << e.what() << std::endl;
    }

    // 7) Test clear_buffer
    std::cout << "\n7) Test clear_buffer" << std::endl;
    driver.clear_buffer();

    try {
        misura py = driver.pop_front();
        (void)py;
        std::cout << "ERRORE: niente eccezione dopo clear_buffer!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione dopo clear_buffer: " << e.what() << std::endl;
    }

    // 8) Test errori get_reading
    std::cout << "\n8) Test get_reading con indice fuori range" << std::endl;
    driver.push_back(build_misura(999.0));

    try {
        std::cout << "Chiamo get_reading(-1)..." << std::endl;
        lettura lneg = driver.get_reading(-1);
        (void)lneg;
        std::cout << "ERRORE: niente eccezione!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione per indice -1: " << e.what() << std::endl;
    }

    try {
        std::cout << "Chiamo get_reading(17)..." << std::endl;
        lettura l17 = driver.get_reading(17);
        (void)l17;
        std::cout << "ERRORE: niente eccezione!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Eccezione per indice 17: " << e.what() << std::endl;
    }

    std::cout << "\n=== FINE TEST INERTIALDRIVER ===" << std::endl;
    return 0;
}
