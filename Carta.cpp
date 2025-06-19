#include "Carta.h"
using namespace std;
#include <iostream>

Carta::Carta() {
	this->palo = "";
	this->puntuacion = 0;
	this->nombre = "";

}
Carta::Carta(string palo, int puntuacion, string nombre) {
	this->palo = palo;
	this->puntuacion = puntuacion;
	this->nombre = nombre;

}

Carta::Carta(const Carta& original) {
	this->palo = original.palo;
	this->puntuacion = original.puntuacion;
	this->nombre = original.nombre;
}

int Carta::getPuntuacion() const {
	return puntuacion;
}

string Carta::getPalo() const {
	return palo;
}

string Carta::getNombre() const {
	return nombre;
}

