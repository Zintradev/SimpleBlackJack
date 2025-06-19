#include "Juego.h"
#include "Excepcion.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm> // Para funcion find_if

Juego::Juego() {
    this->jugadores = {};
    this->crupier = {};
    this->baraja = {};
    this->historico = {};
}

Juego::Juego(Jugador jugador, Crupier crupier, Baraja baraja, Historico historico) {
    this->jugadores.push_back(jugador);
    this->crupier = crupier;
    this->baraja = baraja;
    this->historico = historico;
}

void Juego::añadirJugadores() {
    int numeroJugadores; 

    // Bucle para volver a pedir el número de jugadores si es inválido
    do {
        try {
            cout << "Ingrese el numero de jugadores para esta partida: ";
            cin >> numeroJugadores;
            cin.ignore(); // Limpiar el búfer antes de leer líneas completas

            // Lanzar excepción si el número de jugadores es inválido (0 o menor)
            if (numeroJugadores <= 0) {
                throw NumeroJugadoresInvalidoException("El numero de jugadores no puede ser menor o igual a 0.");
            }

            break;  // Salir del bucle cuando el número de jugadores sea válido
        }
        catch (const NumeroJugadoresInvalidoException& ex) {
            // Capturar el error y mostrar el mensaje
            cout << "Error: " << ex.what() << endl;
        }
    } while (numeroJugadores <= 0);  // Si el número de jugadores es inválido, vuelve a pedirlo


    // Desactivar todos los jugadores actuales antes de agregar los nuevos
    for (auto& jugador : jugadores) {
        jugador.setActivo(false);
    }

    for (int i = 0; i < numeroJugadores; ++i) {
        string nombre;
        cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        getline(cin, nombre);

        // Buscar si el jugador ya está en la lista activa (codigo modificado de stack overflow)
        auto it = std::find_if(jugadores.begin(), jugadores.end(),
            [&nombre](const Jugador& j) { return j.getNombre() == nombre; });

        if (it != jugadores.end()) {
            // Reactivar al jugador de la lista activa
            it->setActivo(true);
            it->limpiarMano();
            it->setPuntuacion(0);
            it->setPlantado(false);
            continue;
        }

        // Buscar el jugador en el historial y si esta lo activa y reinicia su mano y puntos de la partida
        bool jugadorEncontrado = false;
        for (auto& jugadorHist : historico.getJugadores()) {
            if (jugadorHist.getNombre() == nombre) {
                Jugador jugadorCopia = jugadorHist; 
                jugadorCopia.setActivo(true);
                jugadorCopia.limpiarMano();
                jugadorCopia.setPuntuacion(0);  
                jugadorCopia.setPlantado(false);
                jugadores.push_back(jugadorCopia);
                jugadorEncontrado = true;
                break;
            }
        }

        // Si no se encuentra el jugador en el historial crear uno 
        if (!jugadorEncontrado) {
            Jugador nuevoJugador;
            nuevoJugador.setNombre(nombre);
            nuevoJugador.setActivo(true);
            nuevoJugador.limpiarMano();
            nuevoJugador.setPuntuacion(0);
            nuevoJugador.setPlantado(false);
            jugadores.push_back(nuevoJugador); 
            historico.añadirJugador(nuevoJugador);
        }
    }
}


void Juego::iniciarPartida() {
    añadirJugadores();

    this->baraja.generarBaraja();
    cout << "Baraja generada." << endl;

    this->baraja.barajar();
    cout << "Baraja barajada." << endl;

    // Reiniciar las manos de los jugadores
    for (auto& jugador : jugadores) {
        if (jugador.esActivo()) {
            jugador.limpiarMano();
        }
    }
    crupier.limpiarMano();

    // Reiniciar las puntuaciones
    for (auto& jugador : jugadores) {
        if (jugador.esActivo()) {
            jugador.setPuntuacion(0);
        }
    }
    crupier.setPuntuacion(0);
    system("cls");

    bool blackjackNaturalJ = false;
    bool blackjackNaturalC = false;

    // Repartir dos cartas a cada jugador 
    for (auto& jugador : jugadores) {
        if (jugador.esActivo()) {
            Carta carta1 = baraja.sacarCarta();
            Carta carta2 = baraja.sacarCarta();
            jugador.agregarCarta(carta1);
            jugador.agregarCarta(carta2);
            cout << "Jugador " << jugador.getNombre() << " recibe las cartas: " << carta1.getNombre() << " de " << carta1.getPalo() << " y " << carta2.getNombre() << " de " << carta2.getPalo() << endl;
            actualizarPuntuacion(jugador);

            if (jugador.getPuntuacion() == 21) {
                blackjackNaturalJ = true;
            }
        }
    }

    // Repartir dos cartas al crupier
    Carta carta1Crupier = baraja.sacarCarta();
    Carta carta2Crupier = baraja.sacarCarta();
    crupier.agregarCarta(carta1Crupier);
    crupier.agregarCarta(carta2Crupier);
    cout << "Crupier recibe las cartas: " << carta1Crupier.getNombre() << " de " << carta1Crupier.getPalo() << " y " << carta2Crupier.getNombre() << " de " << carta2Crupier.getPalo() << endl;
    actualizarPuntuacion(crupier);

    // Blackjack natural
    if (crupier.getPuntuacion() == 21) {
        blackjackNaturalC = true;
    }
    if (blackjackNaturalC == true && blackjackNaturalJ == true) { // Crupier y jugador tienen blackjack
        cout << "====Crupier y jugador blackjack natural====\n\tEMPATE" << endl;
    }
    else if (blackjackNaturalC == true) { // Crupier tiene blackjack
        cout << "====Crupier blackjack natural====\n\tDERROTA" << endl;
        jugador.setPerdidas(jugador.getPerdidas() + 1);
    }
    else if (blackjackNaturalJ == true) { // Jugador tiene blackjack
        cout << "====Jugador " << jugador.getNombre() << " blackjack natural====\n\tVICTORIA" << endl;
        jugador.setGanadas(jugador.getGanadas() + 1);
    }
}

void Juego::iniciarMenu() {
    int opcion;

    do {
        cout << "\n==== MENU ====" << endl;
        cout << "1. Iniciar Partida" << endl;
        cout << "2. Ver historial" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        //Lo coje sin enter pero en ascii
        opcion = _getch();

        switch (opcion) {
        case 49:
            system("cls");
            cout << "====INICIANDO LA PARTIDA====\n" << endl;
            iniciarPartida();
            iniciarTurnos();
            break;
        case 50:
            system("cls");
            cout << "\n\n====HISTORIAL====" << endl;
            historico.setHistorialJugadores(jugadores);
            cout << historico;
            break;

        case 51:
            cout << "Saliendo del juego. Hasta luego!" << endl;
            exit(0);
            break;

        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 3);
}

void Juego::iniciarTurnos() {
    bool partidaFinalizada = false;

    while (!partidaFinalizada) {
        
        // Cada jugador toma su turno
        for (auto& jugador : jugadores) {
            if (!jugador.esActivo()) continue;  // Solo jugadores activos

            if (!jugador.isPlantado()) {  // Si el jugador no se ha plantado
                jugador.setPlantado(false);
                bool jugadorPlantado = false;
                cout << "\nTurno de " << jugador.getNombre() << ":\n" << endl;

                while (!jugadorPlantado && jugador.getPuntuacion() <= 21) {
                    int opcion = 0;
                    do {
                        cout << "1. Pedir carta" << endl;
                        cout << "2. Plantarse" << endl;
                        opcion = _getch(); // Sin enter pero con ascii

                        if (opcion != 49 && opcion != 50) {
                            cout << "Opción invalida. Por favor, elige una opcion valida.\n" << endl;
                        }
                    } while (opcion != 49 && opcion != 50); // Repite hasta que se elija 1 o 2

                    if (opcion == 49) {
                        Carta nuevaCarta = baraja.sacarCarta();  
                        jugador.agregarCarta(nuevaCarta);  
                        cout << "\nCarta obtenida: " << nuevaCarta.getNombre() << " de " << nuevaCarta.getPalo() << " (Valor: " << nuevaCarta.getPuntuacion() << ")" << endl;
                        actualizarPuntuacion(jugador);

                        // Verificar si el jugador se pasa de 21
                        if (jugador.getPuntuacion() > 21) {
                            cout << "Te has pasado de 21 Te plantas automaticamente." << endl;
                            jugador.setPlantado(true); // El jugador se planta automáticamente si se pasa de 21
                            jugadorPlantado = true;
                        }
                    }
                    else if (opcion == 50) {
                        jugador.setPlantado(true); 
                        jugadorPlantado = true;
                    }
                    break;
                }
            }
        }

        // Turno del crupier 
        bool crupierPlantado = false;
        if (!crupierPlantado) {  
            cout << "\nTurno del crupier:" << endl;
            while (!crupierPlantado) {
                if (crupier.getPuntuacion() <= 16) {
                    Carta nuevaCarta = baraja.sacarCarta();  
                    crupier.agregarCarta(nuevaCarta);  
                    cout << "Crupier obtiene: " << nuevaCarta.getNombre() << " de " << nuevaCarta.getPalo() << " (Valor: " << nuevaCarta.getPuntuacion() << ")\n" << endl;
                    actualizarPuntuacion(crupier);
                    mostrarEstado();
                    break;
                }
                else {
                    cout << "El crupier se planta.\n" << endl;
                    mostrarEstado();
                    crupierPlantado = true;  
                }
            }
        }

        // Verificamos si la partida ha terminado
        bool jugadoresPlantados = true;
        for (auto& jugador : jugadores) {
            if (jugador.esActivo() && !jugador.isPlantado()) {  // Solo jugadores activos
                jugadoresPlantados = false;  // Si algún jugador aún no se ha plantado la partida sigue
            }
        }

        if (jugadoresPlantados || crupier.getPuntuacion() > 21) {
            partidaFinalizada = true;  // La partida termina si todos se plantan o si el crupier se pasa de 21
        }
    }
    system("cls");
    decidirGanador();
}

void Juego::decidirGanador() {
    mostrarEstado();
    int puntuacionCrupier = crupier.getPuntuacion();

    for (auto& jugador : jugadores) {
        if (!jugador.esActivo()) continue; // Saltar jugadores inactivos

        int puntuacionJugador = jugador.getPuntuacion();

        if (puntuacionJugador > 21) { // Jugador se pasa de 21
            cout << "====Jugador " << jugador.getNombre() << " busted====\n\tDERROTA" << endl;
            jugador.setPerdidas(jugador.getPerdidas() + 1);
        }
        else if (puntuacionCrupier > 21) { // Crupier se pasa de 21
            cout << "====Crupier busted====\n\tVICTORIA" << endl;
            jugador.setGanadas(jugador.getGanadas() + 1);
        }
        else if (puntuacionCrupier == 21) { // Crupier tiene blackjack
            cout << "====Crupier blackjack====\n\tDERROTA" << endl;
            jugador.setPerdidas(jugador.getPerdidas() + 1);
        }
        else if (puntuacionJugador == 21) { // Jugador tiene blackjack
            cout << "====Jugador " << jugador.getNombre() << " blackjack====\n\tVICTORIA" << endl;
            jugador.setGanadas(jugador.getGanadas() + 1);
        }
        else if (puntuacionCrupier > puntuacionJugador && puntuacionCrupier < 21) { // Crupier más cerca de 21
            cout << "====Crupier mas cerca de blackjack====\n\tDERROTA" << endl;
            jugador.setPerdidas(jugador.getPerdidas() + 1);
        }
        else if (puntuacionJugador > puntuacionCrupier && puntuacionJugador < 21) { // Jugador más cerca de 21
            cout << "====Jugador " << jugador.getNombre() << " mas cerca de blackjack====\n\tVICTORIA" << endl;
            jugador.setGanadas(jugador.getGanadas() + 1);
        }
        else { // Empate
            cout << "Empate entre jugador " << jugador.getNombre() << " y el crupier." << endl;
        }
    }
}

void Juego::mostrarEstado() {
    cout << "\n============ PUNTUACIONES ============" << endl;

    for (const auto& jugador : jugadores) {
        if (jugador.esActivo()) { // Mostrar solo jugadores activos
            cout << "\nJugador " << jugador.getNombre() << ": Puntuacion = " << jugador.getPuntuacion() << endl;
            cout << "Cartas:\n";
            for (const auto& carta : jugador.getMano()) {
                cout << carta.getNombre() << " de " << carta.getPalo() << "\n";
            }
        }
    }

    // Mostrar el crupier
    cout << "\nCrupier: Puntuacion = " << crupier.getPuntuacion() << endl;
    cout << "Cartas:\n";
    for (const auto& carta : crupier.getMano()) {
        cout << carta.getNombre() << " de " << carta.getPalo() << "\n";
    }
    cout << "============================\n";
}

void Juego::actualizarPuntuacion(Jugador& jugador) {
   jugador.setPuntuacion(0);
    int puntuacion = 0;
    int ases = 0;

    for (const Carta& carta : jugador.getMano()) {
        puntuacion += carta.getPuntuacion();
        if (carta.getNombre() == "A") {  
            ases++;
        }
    }

    // Ajustar los Ases de 11 a 1 si la puntuación supera 21
    while (puntuacion > 21 && ases > 0) {
        puntuacion -= 10;  // Reducir el valor de un As de 11 a 1
        ases--;
    }

    jugador.setPuntuacion(puntuacion);
   
}
