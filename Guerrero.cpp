#include "Guerrero.hpp"
#include <iostream>

//Constructores
Guerrero::Guerrero():fuerza{1} {}
Guerrero::Guerrero(double v, double a, int n, double f): Unidad(v, a, n) {setFuerza(f);}

//Getter - Setter
double Guerrero::getFuerza() {return fuerza;}
void Guerrero::setFuerza(double f) {fuerza = (f < 1)? 1 : f;} //Fuerza mínima 1

//Métodos especiales
void Guerrero::atacar(Unidad& enemigo) {
    if (enemigo.estaVivo()) {  //Verificamos que el enemigo se encuentre vivo antes y despues del ataque
    double dano = Unidad::calculaDano(enemigo);
    dano = dano + dano*((fuerza-1)*0.15); //El daño infligido incrementa en un 15% por cada punto de fuerza sobre 1.
    enemigo.recibeAtaque(dano);
    } 
    else {
        std::cout << "La unidad enemiga se encuentra fuera de combate" << std::endl;
    }
}
void Guerrero::recibeAtaque(double ataq) {
    ataq = ataq - ataq*((fuerza-1)*0.05); //Se descuenta un 5% del daño recibido por punto de fuerza sobre 1.
    Unidad::recibeAtaque(ataq);
}

bool Guerrero::estaVivo() {
    if (getSalud() > 0) {
        return true;
    } else {
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (fuerza > 3 && randomValue < 0.25) { //Si la fuerza es mayor a 3, hay 25% de probabilidad de que sobreviva
            setSalud(fuerza*20);              // con 20 puntos de salud por cada punto de fuerza
            return true;
        }
        else {
            return false;
        }
    }
}

void Guerrero::imprimir() {
    std::cout << "GUERRRERO: " << std::endl;
    Unidad::imprimir();
    std::cout << "Fuerza: " << fuerza << std::endl;
}
