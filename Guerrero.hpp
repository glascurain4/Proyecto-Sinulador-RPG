#include "Unidad.hpp"
#include <iostream>

class Guerrero : public Unidad {
    public:
    Guerrero();
    Guerrero(double, double, int, double);
    double getFuerza();
    void setFuerza(double);
    void atacar(Unidad&);
    void recibeAtaque(double);
    bool estaVivo();
    void imprimir();

    private:
    double fuerza;
};