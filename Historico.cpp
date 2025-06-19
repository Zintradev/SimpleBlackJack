#include "Historico.h"

Historico::Historico() {
    this->historial_jugadores = {};
}
Historico::Historico(vector<Jugador> historial_jugadores) {
	this->historial_jugadores = historial_jugadores;
}

ostream& operator<<(ostream& os, const Historico& historico) {
    for (const auto& jugador : historico.historial_jugadores) {
        os << "Nombre: " << jugador.getNombre() << endl;
        os << "Partidas ganadas: " << jugador.getGanadas() << endl;
        os << "Partidas perdidas: " << jugador.getPerdidas() << endl;
        os << "------------------------" << endl;
    }
    return os;
}

void Historico::añadirJugador(const Jugador& jugador) {
    auto it = std::find_if(historial_jugadores.begin(), historial_jugadores.end(),
        [&jugador](const Jugador& j) { return j.getNombre() == jugador.getNombre(); });

    if (it == historial_jugadores.end()) {
        historial_jugadores.push_back(jugador);
    }
    else {
        cout << "El jugador '" << jugador.getNombre() << "' ya esta en el historial." << endl;
    }
}



