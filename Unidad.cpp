//Genera la implementación de la clase base Unidad

#include "Unidad.hpp"
#include <iostream>

//Constructores
Unidad::Unidad():vida{250}, salud{250}, ataque{50}, nivel{1} {}
Unidad::Unidad(double v, double a, int n) {setVida(v), setSalud(v), setAtaque(a), setNivel(n);}

//Getters - Setters
double Unidad::getVida() {return vida;}
double Unidad::getSalud() {return salud;}
double Unidad::getAtaque() {return ataque;}
int Unidad::getNivel() {return nivel;}

void Unidad::setVida(double v) {
    if (v <= 0) {
        std::string mensaje = "La unidad debe tener vida máxima mayor a 0";
        throw std::invalid_argument(mensaje);
    } else {
    vida = v;
    }
    }
    
void Unidad::setSalud(double s) {salud = (s <= 0)? 0 : s;}
void Unidad::setAtaque(double a) {ataque = (a <= 0)? 0 : a;}
void Unidad::setNivel(int n) {
    if (n >= 1 && nivel != 0) {
    vida += vida*0.2*(n-nivel);
    salud += salud*0.2*(n-nivel); //La vida y ataque de la unidad se actualizan al cambiar de nivel
    ataque += ataque*0.1*(n-nivel); 
    nivel = n;
    } else if (n < 1) {
        nivel = 1;
    } else {
        nivel = n;
    }
    }

//Métodos especiales
double Unidad::porcentajeSalud() {
    double porc_sal = (salud/vida)*100;
    return porc_sal;
}

double Unidad::calculaDano(Unidad& enemigo) {
    double dano;
    if (enemigo.getNivel() <= nivel) {
        dano = (ataque / 2) + rand() % (static_cast<int>(ataque) - static_cast<int>(ataque / 2) + 1);
    } else {
        dano = 1 + rand() % static_cast<int>(ataque / 2);
    }
    return dano;
}

void Unidad::imprimeBarraVida() {
    int largo = 20;
    int vida_ = (salud/vida)*largo;
    int vacio = largo - vida_;
    std::cout << "Barra de vida: ";
        for (int i = 0; i < vida_; ++i) {
            std::cout << '#';
        }
        for (int i = 0; i < vacio; ++i) {
            std::cout << '=';
        }
        std::cout << std::endl;
}

void Unidad::recibeAtaque(double ataq) {
    setSalud(salud-ataq);
    if (estaVivo()) {
        std::cout << "";
    }
    else {
        std::cout << "¡Unidad caída!" << std::endl;
    }
}

void Unidad::imprimir() {
        std::cout << "Nivel: " << nivel << std::endl;
        std::cout << "Salud(" << porcentajeSalud() << "%): " << salud << "/" << vida << std::endl;
        imprimeBarraVida();
        std::cout << "Ataque: " << ataque << std::endl;
}

void Unidad::operator += (Unidad& enemigo) {
    imprimir();
    std::cout << "--------------------------------------" << std::endl;
    enemigo.imprimir();
    std::cout << "--------------------------------------" << std::endl;
}

void Unidad::operator ++ () {
    setNivel(nivel+1);
}
