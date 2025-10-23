#include <iostream>
#include "Biblioteca.h"
#include "Libro.h"

int main() {
    Biblioteca biblioteca;
    
    // Agregar libros
    biblioteca.agregarLibro(Libro("El Principito", "Antoine de Saint-Exupéry", "978-0156012195"));
    biblioteca.agregarLibro(Libro("Harry Potter y la piedra filosofal", "J.K. Rowling", "978-8478884452"));
    biblioteca.agregarLibro(Libro("Orgullo y prejuicio", "Jane Austen", "978-0141439518"));
    biblioteca.agregarLibro(Libro("El señor de los anillos", "J.R.R. Tolkien", "978-0544003415"));
    biblioteca.agregarLibro(Libro("Crimen y castigo", "Fiódor Dostoyevski", "978-8420664266"));
    
    // Buscar libros
    std::cout << "Buscar por título 'Harry Potter':" << std::endl;
    biblioteca.buscarPorTitulo("Harry Potter");
    
    std::cout << "\nBuscar por autor 'Tolkien':" << std::endl;
    biblioteca.buscarPorAutor("Tolkien");
    
    std::cout << "\nLibros disponibles:" << std::endl;
    biblioteca.mostrarLibrosDisponibles();
    
    return 0;
}
