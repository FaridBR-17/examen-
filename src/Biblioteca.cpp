#include "Biblioteca.h"
#include <iostream>
#include <algorithm>

void Biblioteca::agregarLibro(const Libro& libro) {
    libros.push_back(libro);
}

void Biblioteca::eliminarLibro(const std::string& ISBN) {
    libros.erase(std::remove_if(libros.begin(), libros.end(),
        [&ISBN](const Libro& libro) {
            return libro.getISBN() == ISBN;
        }), libros.end());
}

void Biblioteca::buscarPorTitulo(const std::string& titulo) const {
    for (const auto& libro : libros) {
        if (libro.getTitulo().find(titulo) != std::string::npos) {
            std::cout << "Encontrado: " << libro.getTitulo() 
                      << " por " << libro.getAutor() 
                      << " (ISBN: " << libro.getISBN() << ")" << std::endl;
        }
    }
}

void Biblioteca::buscarPorAutor(const std::string& autor) const {
    for (const auto& libro : libros) {
        if (libro.getAutor().find(autor) != std::string::npos) {
            std::cout << "Encontrado: " << libro.getTitulo() 
                      << " por " << libro.getAutor() 
                      << " (ISBN: " << libro.getISBN() << ")" << std::endl;
        }
    }
}

void Biblioteca::mostrarLibrosDisponibles() const {
    for (const auto& libro : libros) {
        if (libro.estaDisponible()) {
            std::cout << "Disponible: " << libro.getTitulo() 
                      << " por " << libro.getAutor() 
                      << " (ISBN: " << libro.getISBN() << ")" << std::endl;
        }
    }
}
