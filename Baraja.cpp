#include "Baraja.h"
#include <algorithm>
#include <random>
#include <ctime>

Baraja::Baraja() {
    this->baraja = {};
}

Baraja::Baraja(list<Carta> baraja) {
    this->baraja = baraja;
}

void Baraja::generarBaraja() {

    string palos[] = { "Corazones", "Diamantes", "Treboles", "Picas" };
    string nombres[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int valores[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

    for (const auto& palo : palos) {
        for (size_t i = 0; i < sizeof(nombres) / sizeof(nombres[0]); ++i) {
            Carta carta(palo, valores[i], nombres[i]); 
            baraja.push_back(carta);
        }
    }
}

void Baraja::barajar() {
    //Lo convierto a vector para que no me de problemas con la aleatorizacion
    std::vector<Carta> tempVector(baraja.begin(), baraja.end());

    unsigned seed = std::time(0);  
    shuffle(tempVector.begin(), tempVector.end(), default_random_engine(seed));

    baraja.assign(tempVector.begin(), tempVector.end());
}

Carta Baraja::sacarCarta() {
    if (!baraja.empty()) {
        Carta cartaSacada = baraja.front();
        baraja.pop_front();
        return cartaSacada;
    }
    else {
        return Carta();
    }
}

void Baraja::mostrarBaraja() {
    for (const auto& carta : baraja) {
        cout << carta.getPalo() << " " << carta.getNombre() << endl;
    }
}