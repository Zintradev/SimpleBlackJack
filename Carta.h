#pragma once
using namespace std;
#include <iostream>

class Carta
{
private:
	string palo;
	int puntuacion;
	string nombre;

public:
	Carta();
	Carta(string, int, string);
	Carta(const Carta&);
	int getPuntuacion() const;
	string getPalo() const;
	string getNombre() const;
};

