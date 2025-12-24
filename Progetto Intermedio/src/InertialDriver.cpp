#include "../include/InertialDriver.h"

// Costruttore
InertialDriver::InertialDriver() 
    : measureBuffer(BUFFER_DIM), front(0), back(0), count(0) {
    // Inizializziamo il buffer con misure azero
    for (int i = 0; i < BUFFER_DIM; i++) {
        measureBuffer[i] = misura(); 
    }
}

// Distruttore di default
InertialDriver::~InertialDriver() = default;

// push_back aggiunge una misura al buffer 
void InertialDriver::push_back(const misura& m) {
    if (count < BUFFER_DIM) {
        // Buffer non pieno
        measureBuffer[back] = m;
        back = (back + 1) % BUFFER_DIM;
        count++;
    } else {
        // Buffer pieno => sovrascrive la misura più vecchia
        measureBuffer[front] = m;
        front = (front + 1) % BUFFER_DIM;
        back = front; // buffer rimane pieno
    }
}

// pop_front restituisce e rimuove la misura più vecchia
misura InertialDriver::pop_front() {
    if (count == 0) {
        throw std::runtime_error("Buffer vuoto");
    }
    
    misura oldest = measureBuffer[front];
    front = (front + 1) % BUFFER_DIM;
    count--;
    
    return oldest;
}

// clear_buffer elimina tutte le misure senza restituirle
void InertialDriver::clear_buffer() {
    front = 0;
    back = 0;
    count = 0;
}

// get_reading restituisce la lettura di un sensore dalla misura più recente
lettura InertialDriver::get_reading(int sensor_index) const {
    if (count == 0) {
        throw std::runtime_error("Nessuna misura disponibile nel buffer");
    }
    
    if (sensor_index < 0 || sensor_index >= MISURA_LENGTH) {
        throw std::out_of_range("Indice sensore non valido. Deve essere compreso tra 0 e 16");
    }
    
    // Calcola l'indice della misura più recente
    // La misura più recente è alla posizione (back - 1)
    int latest_index = (back == 0) ? BUFFER_DIM - 1 : back - 1;
    
    return measureBuffer[latest_index].mis[sensor_index];
}

// Overload dell'operatore << per stampare l'ultima misura
std::ostream& InertialDriver::print(std::ostream& os) const {
    if (count == 0) {
        os << "Nessuna misura disponibile nel buffer";
        return os;
    }

    int latest_index = (back == 0) ? BUFFER_DIM - 1 : back - 1;
    const misura& latest = measureBuffer[latest_index];

    os << "= ULTIMA MISURA (17 sensori) =" << std::endl;
    for (int i = 0; i < MISURA_LENGTH; i++) {
        os << "Sensore " << i << ": " 
           << "Yaw(v="   << latest.mis[i].get_yaw_v() 
           << ", a="     << latest.mis[i].get_yaw_a() << ") "
           << "Pitch(v=" << latest.mis[i].get_pitch_v()
           << ", a="     << latest.mis[i].get_pitch_a() << ") "
           << "Roll(v="  << latest.mis[i].get_roll_v()
           << ", a="     << latest.mis[i].get_roll_a() << ")"
           << std::endl;
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const InertialDriver& driver) {
    return driver.print(os);
}
