#pragma once
using namespace std;
#include <iostream>
#include "Carta.h"
#include <list>

class Baraja
{
private:
	list<Carta> baraja;

public:
	Baraja();
	Baraja(list<Carta>);
	void generarBaraja();
	void barajar();
	Carta sacarCarta();
	void mostrarBaraja();
	bool estaVacia() const {
		return baraja.empty(); 
	}
};

