#pragma once
using namespace std;
#include <vector>
#include <iostream>
#include "Jugador.h"
#include "Crupier.h"
#include "Baraja.h"
#include "Historico.h"

class Juego
{
private:
	vector<Jugador> jugadores;
	Jugador jugador;
	Crupier crupier;
	Baraja baraja;
	Historico historico;

public:
	Juego();
	Juego(Jugador, Crupier, Baraja, Historico);
	void iniciarMenu();
	void iniciarPartida();
	void iniciarTurnos();
	void mostrarEstado();
	void añadirJugadores();
	void decidirGanador();
	void actualizarPuntuacion(Jugador&);
	vector<Jugador> getJugadores() const {
		return jugadores;
	}

};

