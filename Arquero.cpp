#include "Arquero.hpp"
#include <iostream>

Arquero::Arquero():precision{1}{}
Arquero::Arquero(double v, double a, int n, double p): Unidad(v, a, n) {setPrecision(p);}

double Arquero::getPrecision() {return precision;}
void Arquero:: setPrecision(double p) {precision = (p < 1)? 1 : p;} //Precisión mínima 1.

void Arquero::atacar(Unidad& enemigo) {
    if (enemigo.estaVivo()) {  //Verificamos que el enemigo se encuentre vivo antes y despues del ataque
    double dano = Unidad::calculaDano(enemigo);
    double probCritico = (precision-1)*0.03; //La probabilidad de daño critico aumenta en 3% por cada punto de precisión sobre el 1
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    if (randomValue < probCritico) 
    {dano *= 1.5; //Creamos un valor aleatorio y de ser menor a nuestra probabilidad obtenemos un critico (+50% daño)
    std::cout << "¡Crítico!" << std::endl;
    }
    enemigo.recibeAtaque(dano);
    } else {
        std::cout << "La unidad enemiga se encuentra fuera de combate" << std::endl;
    }
}
void Arquero::recibeAtaque(double dano) {
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    if (randomValue < getNivel()*0.05) { //Por cada nivel la probabilidad de esquivar el ataque aumenta 5%
        std::cout << "¡El arquero esquiva el ataque!" << std::endl;
        recibeAtaque(0);
    } else {
        recibeAtaque(dano);
    }
}
bool Arquero::estaVivo() {
    if (getSalud() > 0) {
        return true;
    } else {
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue < getNivel()*0.04) { //Por cada nivel la probabilidad de sobrevivir del arquero aumenta en un 4%
            setSalud(getVida()*0.2); //Sobrevive con un 20% de la vida máxima
            return true;
        }
        return false;
    }
}

void Arquero::imprimir() {
    std::cout << "ARQUERO: " << std::endl;
    Unidad::imprimir();
    std::cout << "Precision: " << std::to_string(precision) << std::endl;
    std::cout << "Probabilidad de crítico: " << std::to_string(((precision-1)*0.03)*100) << "%" << std::endl;
}
