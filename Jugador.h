#pragma once
using namespace std;
#include <iostream>
#include "Baraja.h"

class Jugador
{
private:
	string nombre;
	int puntuacion;
	list<Carta> mano;
	int ganadas;
	int perdidas;
    bool plantado;
    bool activo;

public:
	Jugador();
	Jugador(string, int, list<Carta>, int, int,bool, bool);
	Jugador(const Jugador&);
	void actualizarNombre(Jugador&);
    void agregarCarta(const Carta&);

    bool isPlantado() const { return plantado; } 
    void setPlantado(bool plantado) { this->plantado = plantado; }  


    bool esActivo() const {
        return activo;
    }


    void setActivo(bool estado) {
        activo = estado;
    }

    void setNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    std::string getNombre() const {
        return nombre;
    }

    void setPuntuacion(int nuevaPuntuacion) {
        puntuacion = nuevaPuntuacion;
    }

    int getPuntuacion() const {
        return puntuacion;
    }

    void setGanadas(int nuevasGanadas) {
        ganadas = nuevasGanadas;
    }

    int getGanadas() const {
        return ganadas;
    }

    void setPerdidas(int nuevasPerdidas) {
        perdidas = nuevasPerdidas;
    }

    int getPerdidas() const {
        return perdidas;
    }

    list<Carta> getMano() const {
        return mano;
    }

    void limpiarMano() {
        this->mano.clear();  
    }

};

