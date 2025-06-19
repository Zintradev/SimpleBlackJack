#pragma once
using namespace std;
#include <iostream>
#include <list>
#include "Jugador.h"

class Crupier : public Jugador
{
private:
	int puntuacion;
	list<Carta> mano;
public:
	Crupier();
	Crupier(int, list<Carta>);
};

