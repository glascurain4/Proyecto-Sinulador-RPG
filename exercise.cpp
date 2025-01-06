#include <iostream>
#include "Guerrero.hpp"
#include "Mago.hpp"
#include "Arquero.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

void presentar(vector<Unidad*> ej) { //creamos funcion para presentar un ejercito
  cout << "--------------------------------------" << endl;
  for (int i = 0; i < ej.size(); i++) {
    ej[i]->imprimir(); //imprimir polimórfico
    cout << "--------------------------------------" << endl; 
  }
}

void enfrentar(vector<Unidad*> ej1, vector<Unidad*> ej2) { //creamos funcion para enfrentar dos ejercitos
  for (int i = 0; i < ej1.size() && i < ej2.size(); i++) {

    *ej1[i] += *ej2[i]; //mostramos las unidades a enfrentar
    int ronda = 1;
    while (ej1[i]->estaVivo() && ej2[i]->estaVivo()) {
      cout << "Ronda: " << to_string(ronda) << endl;
      cout << "--------------------------------------" << endl; //Mientras ambas unidades sigan vivas
      ej1[i]->atacar(*ej2[i]);                       // hacemos que se ataquen mutuamente y mostranos sus datos
      ej2[i]->atacar(*ej1[i]);                      // llevando el conteo de las rondas
      *ej1[i] += *ej2[i];
      ronda++;
    }
              //Utilicé el getSalud() para asegurar que no reviviese la unidad fuera del enfrentamiento
    if (ej1[i]->getSalud() > 0 && ej2[i]->getSalud() == 0) {
      cout << "La unidad aliada ha ganado el enfrentamiento" << endl;
      cout << "--------------------------------------" << endl;
      ++*ej1[i]; //La unidad victoriosa sube de nivel
    } else if (ej2[i]->getSalud() > 0 && ej1[i]->getSalud() == 0) {
      cout << "La unidad enemiga ha ganado el enfrentamiento" << endl;  //Definimos cuál de las unidades ganó el combate
      cout << "--------------------------------------" << endl;
      ++*ej2[i];
    } else {
      cout << "Empate" << endl;
      cout << "--------------------------------------" << endl;
    }
  }
}

int main() 
{
  int entra;
  double vida;
  double ataque; //creamos las variables y el vector que utilizaremos
  int nivel;    //para construir nuestro ejército
  vector<Unidad*> unidades;

  vector<Unidad*> enemigos;
  enemigos.push_back(new Guerrero(350, 75, 5, 5));
  enemigos.push_back(new Guerrero(500, 80, 7, 3));
  enemigos.push_back(new Arquero(300, 80, 5, 3)); //creamos el ejército enemigo
  enemigos.push_back(new Arquero(290, 90, 5, 5));
  enemigos.push_back(new Mago(280, 100, 5, 100)); 

cout << "¡Bienvenido jugador! El día de hoy te deberás enfrentarte a este ejército de 5 unidades: " << endl;

presentar(enemigos);

cout << "¿Preparado? ¡Crea tu propio ejército!" << endl;

cout << "¿Cuántas unidades quieres para tu ejército?" << endl;
cin >> entra;

for (int i = 0; i < entra; i++) {
  while (unidades.size() <= i) {
    int opc;
    cout << "Escoge la clase de tu unidad: " << endl << "1) Guerrero" << endl << "2) Arquero" << endl << "3) Mago" << endl;
    cin >> opc;
    cout << "Ingresa los datos de tu unidad: " << endl;
    cout << "Vida: " << endl;
    cin >> vida;                   //Recibimos los datos del usuario y con ellos
    cout << "Ataque: " << endl;   //creamos la unidad y definimos su clase
    cin >> ataque;
    cout << "Nivel: " << endl;
    cin >> nivel;

    switch (opc) {
      case 1:
      double fuerza;
      cout << "Fuerza: " << endl;   //opción 1. Guerrero
      cin >> fuerza;
      try {
      unidades.push_back(new Guerrero(vida, ataque, nivel, fuerza));
      } catch (const std::invalid_argument &e) {
      cout << "Error: " << e.what() << endl;
      }
      break;

      case 2:
      double precision;
      cout << "Precision: " << endl; //opción 2. Arquero
      cin >> precision;
      try {
      unidades.push_back(new Arquero(vida, ataque, nivel, precision));
      } catch (const std::invalid_argument &e) {
      cout << "Error: " << e.what() << endl;
      }
      break;

      case 3:
      try {
      unidades.push_back(new Mago(vida, ataque, nivel, 100)); //opción 3. Mago
      } catch (const std::invalid_argument &e) {             //lo inicializamos siempre con el mana al 100%
      cout << "Error: " << e.what() << endl;
      }
      break;
    }
  }
}

cout << "--------------------------------------" << endl;
cout << "Tu ejercito:" << endl;
presentar(unidades);

while (true) { // Ciclo infinito que enfrenta las unidades hasta que algún ejército quede abatido
cout << "¡Que comience el combate!" << endl;
cout << "--------------------------------------" << endl;

enfrentar(unidades, enemigos);

  int aliados = 0;
  int enemigo = 0;

  cout << "Ejército aliado: " << endl;
  for (int i = 0; i < unidades.size();) {    
    if (unidades[i]->getSalud() > 0) { //Mismo caso con el getSalud()
        aliados++; //contabilizamos unidades sobrevivientes
        i++;
    } else {
        unidades.erase(unidades.begin() + i); //eliminamos del ejército a las unidades derrotadas
    }
}
presentar(unidades);
  cout << "Unidades aliadas sobrevivientes: " << to_string(aliados) << endl;
  cout << "--------------------------------------" << endl;


  cout << "Ejército enemigo: " << endl;
  for (int i = 0; i < enemigos.size();) {
    if (enemigos[i]->getSalud() > 0) { //Repetimos con el ejército enemigo
        enemigo++;
        i++;
    } else {
        enemigos.erase(enemigos.begin() + i);
    }
}
presentar(enemigos);
  cout << "Unidades enemigas sobrevivientes: " << to_string(enemigo) << endl;
  cout << "--------------------------------------" << endl;

  if (aliados > enemigo && enemigo == 0) {
    cout << "¡Tu ejército ha ganado!" << endl;
    break;
  } else if (aliados < enemigo && aliados == 0) {   //Comparamos los ejércitos y determinamos el resultado
    cout << "Tu ejército ha perdido" << endl;
    break;
    } else if (aliados == 0 && enemigo == 0){
      cout << "¡Empate!" << endl;
      break;
    } else {
    cout << "Siguiente enfrentamiento..." << endl; //Si siguen habiendo unidades en ambos ejércitos volvemos a enfrentralos
    }
}
    
  return 0;
}