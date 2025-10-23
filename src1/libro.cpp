#include "Libro.h"

Libro::Libro(std::string tit, std::string aut, std::string isbn) 
    : titulo(tit), autor(aut), ISBN(isbn), disponible(true) {}

std::string Libro::getTitulo() const {
    return titulo;
}

std::string Libro::getAutor() const {
    return autor;
}

std::string Libro::getISBN() const {
    return ISBN;
}

bool Libro::estaDisponible() const {
    return disponible;
}

void Libro::setDisponible(bool disp) {
    disponible = disp;
}
