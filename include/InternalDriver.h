#include "MyVector.h"
#include "misura.h"
#include <iostream>
const int BUFFER_DIM = 200;

class InertialDriver
{
    private:
        MyVector<misura> measureBuffer; 
        int front;
        int back;
        int count;

    public:
        InertialDriver();
        ~InertialDriver();
        void push_back(const misura& m);
        misura pop_front();
        void clear_buffer();
        lettura get_reading(int sensor_index) const;
        std::ostream& operator<<(std::ostream& os, const InertialDriver& driver);
};
