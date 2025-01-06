// Crear el archivo header de la clase Unidad

#pragma once // previene múltiples definiciones como las guardas

class Unidad {
    public:
        //Constructores
        Unidad();
        Unidad(double, double, int);
        //Getters - Setters
        double getVida();
        double getSalud(); 
        double getAtaque(); 
        int getNivel();

        void setVida(double);
        void setSalud(double);
        void setAtaque(double);
        void setNivel(int);
        //Métodos especiales
        double porcentajeSalud();
        double calculaDano(Unidad&);
        void imprimeBarraVida();
        void recibeAtaque(double);
        virtual void atacar(Unidad&) = 0;
        virtual bool estaVivo()= 0;
        virtual void imprimir();
        void operator += (Unidad&); //imprime los datos de ambas unidades a enfrentar
        void operator ++ (); //sube el nivel de la unidad, actualizando sus estadísticas
    private:
        //Atributos
        double vida, salud, ataque;
        int nivel;
};