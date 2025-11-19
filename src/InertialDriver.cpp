#include "InertialDriver.h"
#include <iostream>

InertialDriver::InertialDriver() 
    : measureBuffer(BUFFER_DIM), front(0), back(0), count(0) {}

void InertialDriver::push_back(const misura& m) {
    if (count < BUFFER_DIM) {
        measureBuffer[back] = m;
        back = (back + 1) % BUFFER_DIM;
        count++;
    } else {
        // Buffer pieno - sovrascrivi la più vecchia
        measureBuffer[front] = m;
        front = (front + 1) % BUFFER_DIM;
        back = front;  // Mantieni buffer pieno
    }
}

misura InertialDriver::pop_front() {
    if (count == 0) {
        throw std::runtime_error("Buffer vuoto");
    }
    
    misura result = measureBuffer[front];
    front = (front + 1) % BUFFER_DIM;
    count--;
    return result;
}

void InertialDriver::clear_buffer() {
    front = back = count = 0;
}

lettura InertialDriver::get_reading(int sensor_index) const {
    if (count == 0) throw std::runtime_error("Nessuna misura disponibile");
    if (sensor_index < 0 || sensor_index >= 17) throw std::out_of_range("Indice sensore non valido");
    
    // La misura più recente è all'indice (back - 1) mod BUFFER_DIM
    int latest_index = (back == 0) ? BUFFER_DIM - 1 : back - 1;
    return measureBuffer[latest_index][sensor_index];
}

std::ostream& operator<<(std::ostream& os, const InertialDriver& driver) {
    if (driver.count == 0) {
        os << "Nessuna misura disponibile";
    } else {
        int latest_index = (driver.back == 0) ? BUFFER_DIM - 1 : driver.back - 1;
        os << driver.measureBuffer[latest_index];
    }
    return os;
}
