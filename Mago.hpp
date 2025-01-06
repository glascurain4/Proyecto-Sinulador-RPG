#include "Unidad.hpp"
#include <iostream>

class Mago : public Unidad {
    public:
    Mago();
    Mago(double, double, int, double);
    double getMana();
    void setMana(double);
    void imprimeBarraMana();
    void atacar(Unidad&);
    void recibeAtaque(double);
    bool estaVivo();
    void imprimir();

    private:
    double mana;
};