#include "Crupier.h"

Crupier::Crupier() {
	this->puntuacion = 0;
	this->mano = {};
}
Crupier::Crupier(int puntuacion, list<Carta> mano) {
	this->puntuacion = puntuacion;
	this->mano = mano;
}