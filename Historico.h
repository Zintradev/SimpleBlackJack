#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include "Jugador.h"

class Historico
{
private: 
	vector<Jugador> historial_jugadores;

public:
	Historico();
	Historico(vector<Jugador>);
	void añadirJugador(const Jugador&);
	friend ostream& operator<<(ostream& os, const Historico& historico);
	const std::vector<Jugador>& getJugadores() const {
		return historial_jugadores;
	};
	void setHistorialJugadores(const vector<Jugador>& nuevosJugadores) {
		historial_jugadores = nuevosJugadores;
	}
};

