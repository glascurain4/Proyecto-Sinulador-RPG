#include "Mago.hpp"
#include <iostream>

Mago::Mago():mana{100}{}
Mago::Mago(double v, double a, int n, double m):Unidad(v, a, n) {setMana(m);}

double Mago::getMana() {return mana;}
void Mago::setMana(double m) {
    if (m < 0) {
        mana = 0;
        } 
    else if (m > 100) {
        mana = 100;
        } 
    else {
        mana = m; //maná debe ser un valor entre 0 y 100
        } 
}

void Mago::imprimeBarraMana() {
    int largo = 20;
    int mana_ = (mana/100)*largo;
    int vacio = largo - mana_;
    std::cout << "Barra de maná: ";
        for (int i = 0; i < mana_; ++i) {
            std::cout << '%';
        }
        for (int i = 0; i < vacio; ++i) {
            std::cout << '=';
        }
        std::cout << std::endl;
}

void Mago::recibeAtaque(double ataq) {
    double mana_ = mana - ataq*0.25; //Se pierde 25% del daño en maná
    if (mana < 80) {
        ataq -= ataq*0.3; //Si el mana es mayor a 80% se recibe -30% de daño
        } 
    else if (mana < 50) {
        ataq -= ataq*0.15; //Si el mana es mayor 50% se recibe -15% de daño
        } 
    else {
        ataq = ataq;
        }
    setMana(mana_);
    Unidad::recibeAtaque(ataq);
}
void Mago::atacar(Unidad& enemigo) {
    if (mana > 0) {
    if (enemigo.estaVivo()) { //Verificamos que el enemigo se encuentre vivo antes y despues del ataque

    double dano = Unidad::calculaDano(enemigo);
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    if (mana > 80) 
    {if (randomValue < 0.5) { //Si el maná es más de 80 hay un 50% de probabilidad de un crítico (+100% daño)
    dano *= 2;
    std::cout << "¡Crítico!" << std::endl;
    }
    }  
    else if (mana > 50) {
    if (randomValue < 0.2) { // más de 50 hay 20% de probabilidad
    dano *= 2;
    std::cout << "¡Crítico!" << std::endl;
    }
    } 
    else {
    if (randomValue < 0.05) { // menos de 50 hay 5% de probabilidad
    dano *= 2;
    std::cout << "¡Crítico!" << std::endl;
    }
    } 

    enemigo.recibeAtaque(dano);

    mana -= dano*0.1; //El mana disminuye en un 10% del daño causado
    if (enemigo.getSalud() == 0) {
        setMana(mana + enemigo.getVida()*0.5);} //Si el enemigo es derrotado el mana incrementa en un 50% de la vida total del enemigo
    }
    else {
        std::cout << "La unidad enemiga se encuentra fuera de combate" << std::endl;
    }
    } else {
        std::cout << "El mago no tiene maná para atacar" << std::endl;
        setSalud(0); //Si el mago se queda sin mana, muere
    }
}

bool Mago::estaVivo() {
    if (getSalud() > 0) {
        return true;
    } else {
        if (mana > 30) { //Si el mago tiene mas del 30% de mana al morir, recibe los puntos de mana en vida (-10)
            setSalud(mana-10);
            setMana(10);
            return true;
        }
        else {
            return false;
        }
    }
}

void Mago::imprimir() {
    std::cout << "MAGO: " << std::endl;
    Unidad::imprimir();
    Mago::imprimeBarraMana();
}

