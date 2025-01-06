#include "Unidad.hpp"
#include <iostream>

class Arquero : public Unidad {
    public:
    Arquero();
    Arquero(double, double, int, double);
    double getPrecision();
    void setPrecision(double);
    void atacar(Unidad&);
    void recibeAtaque(double);
    bool estaVivo();
    void imprimir();

    private:
    double precision;
};