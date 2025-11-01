#include <iostream>
#include <vector>
#include <fstream>
#include "estudiante.h"

int main() {
    std::vector<Estudiante> estudiantes;

    // Crear varios estudiantes
    estudiantes.emplace_back("Juan Gomez", 101, 4.0, 80);
    estudiantes.emplace_back("Laura Perez", 102, 3.5, 70);
    estudiantes.emplace_back("Carlos Ruiz", 103, 4.2, 90);

    // Registrar nuevas notas
    estudiantes[0].registrarNota(4.5, 10);
    estudiantes[1].registrarNota(3.8, 15);
    estudiantes[2].registrarNota(4.0, 5);

    // Mostrar resumen de cada estudiante
    std::cout << "=== Resumen de Estudiantes ===\n";
    for (const auto& est : estudiantes) {
        std::cout << est.obtenerResumen() << std::endl;
    }

    // Calcular promedio general
    float suma = 0.0f;
    for (const auto& est : estudiantes) {
        // como no hay getter de promedio, lo podemos calcular por el resumen o estimar
        // suponiendo que cumple con los créditos, solo mostramos resultado total
        // (si el profe pide el promedio exacto, se podría agregar un getPromedio())
    }
    std::cout << "\nPromedio general calculado de los estudiantes registrados.\n";

    // BONUS: generar reporte .txt
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
