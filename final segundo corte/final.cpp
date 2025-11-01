#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
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

    // Calcular promedio general (CORREGIDO)
    float sumaPromedios = 0.0f;
    for (const auto& est : estudiantes) {
        sumaPromedios += est.obtenerPromedio(); // Necesitas el getter
    }
    float promedioGeneral = sumaPromedios / estudiantes.size();
    
    std::cout << "\nPromedio general: " << promedioGeneral << std::endl;

    // BONUS: generar reporte .txt (MEJORADO)
    std::ofstream reporte("reporte_estudiantes.txt");
    if (reporte.is_open()) {
        reporte << "=== REPORTE DE ESTUDIANTES ===\n";
        for (const auto& est : estudiantes) {
            reporte << est.obtenerResumen() << "\n";
        }
        reporte << "\nPromedio general: " << promedioGeneral << "\n";
        reporte.close();
        std::cout << "\nReporte generado: reporte_estudiantes.txt\n";
    } else {
        std::cout << "\nError al crear el reporte.\n";
    }

    return 0;
}
