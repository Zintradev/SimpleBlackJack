#include "Jugador.h"
using namespace std;
#include <iostream>
#include <string>

Jugador::Jugador() {
	this->nombre = "";
	this->puntuacion = 0;
	this->mano = {};
	this->ganadas = 0;
	this->perdidas = 0;
	this->plantado = false;
	this->activo = false;
}
Jugador::Jugador(string nombre, int puntuacion, list<Carta> mano, int ganadas, int perdidas, bool plantado, bool activo) {
	this->nombre = nombre;
	this->puntuacion = puntuacion;
	this->mano = mano;
	this->ganadas = ganadas;
	this->perdidas = perdidas;
	this->plantado = plantado;
	this->activo = activo;
}
Jugador::Jugador(const Jugador& original) {
	this->nombre = original.nombre;
	this->puntuacion = original.puntuacion;
	this->mano = original.mano;
	this->ganadas = original.ganadas;
	this->perdidas = original.perdidas;
	this->plantado = original.plantado;
	this->activo = original.activo;
}

void Jugador::agregarCarta(const Carta& carta) {
	mano.push_back(carta);
}

void Jugador::actualizarNombre(Jugador& jugador) {
	cout << "Introduce el nombre del jugador: ";
	string nuevoNombre;
	getline(cin,nuevoNombre);
	jugador.setNombre(nuevoNombre);
}





