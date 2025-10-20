#include <iostream>
#include "Biblioteca.h"
#include "Libro.h"

int main() {
    Biblioteca biblioteca;
    
    // Agregar libros
    biblioteca.agregarLibro(Libro("Cien años de soledad", "Gabriel García Márquez", "978-8437604947"));
    biblioteca.agregarLibro(Libro("1984", "George Orwell", "978-0451524935"));
    
    // Buscar libros
    std::cout << "Buscar por título '1984':" << std::endl;
    biblioteca.buscarPorTitulo("1984");
    
    std::cout << "\nBuscar por autor 'Gabriel':" << std::endl;
    biblioteca.buscarPorAutor("Gabriel");
    
    std::cout << "\nLibros disponibles:" << std::endl;
    biblioteca.mostrarLibrosDisponibles();
    
    return 0;
}
