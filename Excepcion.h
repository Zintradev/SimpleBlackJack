#pragma once
#include <stdexcept>
#include <string>

class NumeroJugadoresInvalidoException : public std::invalid_argument {
public:
    explicit NumeroJugadoresInvalidoException(const std::string& mensaje)
        : std::invalid_argument(mensaje) {}
};
