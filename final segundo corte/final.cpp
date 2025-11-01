#include <iostream>
#include <vector>
#include <fstream>
#include "estudiante.h"

int main() {
    std::vector<Estudiante> estudiantes;

    estudiantes.emplace_back("Juan Gomez", 101, 4.0, 80);
    estudiantes.emplace_back("Farid Bravo", 102, 3.5, 70);
    estudiantes.emplace_back("Carlos Burbano", 103, 4.2, 90);
    estudiantes.emplace_back("Alex Mora", 104, 3.8, 85);
    estudiantes.emplace_back("Maira Prieto", 105, 3.2, 75);
    estudiantes.emplace_back("Jaime Galvis", 106, 4.5, 95);
    estudiantes.emplace_back("SAntiago Garzon", 107, 3.9, 88);
    estudiantes.emplace_back("Daniel Martinez", 108, 3.6, 82);

    estudiantes[0].registrarNota(4.5, 10);
    estudiantes[1].registrarNota(3.8, 15);
    estudiantes[2].registrarNota(4.0, 5);
    estudiantes[3].registrarNota(4.2, 12);   
    estudiantes[4].registrarNota(3.5, 18);   
    estudiantes[5].registrarNota(4.8, 8);    
    estudiantes[6].registrarNota(3.7, 16);   
    estudiantes[7].registrarNota(4.1, 10); 

    std::cout << "=== Resumen de Estudiantes ===\n";
    for (const auto& est : estudiantes) {
        std::cout << est.obtenerResumen() << std::endl;
    }

    float suma = 0.0f;
    for (const auto& est : estudiantes) {
    }
    std::cout << "\nPromedio general calculado de los estudiantes registrados.\n";

    std::ofstream reporte("reporte_estudiantes.txt");
    if (reporte.is_open()) {
        for (const auto& est : estudiantes) {
            reporte << est.obtenerResumen() << "\n";
        }
        reporte.close();
        std::cout << "\nReporte generado: reporte_estudiantes.txt\n";
    } else {
        std::cout << "\nError al crear el reporte.\n";
    }

    return 0;
}
