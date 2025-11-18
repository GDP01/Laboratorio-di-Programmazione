#include "MyVector.cpp"
#include <vector>
const int BUFFER_DIM = 200;

class InertialDriver
{
    private:
    //vector<MyVector> arr = new vector<MyVector>[BUFFER_DIM];

    MyVector[]* measureBuffer;

    public:
    void push_back()
    {

    }
    void pop_front()
    {

    }
    void clear_buffer()
    {

    }

};

//La funzione push_back che accetta un array stile C contenente una misura e la
//memorizza nel buffer (sovrascrivendo la misura meno recente se il buffer è pieno);

//● La funzione pop_front che fornisce in output un array stile C contenente la misura più
//vecchia e la rimuove dal buffer;
//● La funzione clear_buffer che elimina (senza restituirle) tutte le misure salvate;
//● La funzione get_reading che accetta un numero tra 0 e 16 e ritorna la corrispondente
//lettura della misura più recente, senza cancellarla dal buffer;
//● L’overloading dell’operator<< che stampa a schermo l’ultima misura salvata (ma non la
//rimuove dal buffer)