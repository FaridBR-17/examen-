#include "estudiante.h"
#include <sstream>
#include <iomanip>

Estudiante::Estudiante(const std::string& nombre, int programa, float promedio, int creditorsAprobados)
    : nombre(nombre), programa(programa), promedio(promedio), creditorsAprobados(creditosAprobados) {}

void Estudiante::registrarMota(float nota, int creditors) {
    float totalPonderado = promedio * creditorsAprobados;
    totalPonderado += nota * creditors;
    creditorsAprobados += creditors;
    promedio = totalPonderado / creditorsAprobados;

}

void Estudiante::agregarCreditos(int creditors) {
    creditorsAprobados += creditors;
}

std::string Estudiante::obtenerResumen() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Nombre: " << nombre
    << " | Programa: " << programa
    << " | Promedio: " << promedio
    << " | Creditos: " << creditorsAprobados;
    return oss.str();
}
