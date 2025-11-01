#include "estudiante.h"
#include <sstream>
#include <iomanip>

// CORREGIR: creditorsAprobados → creditosAprobados
Estudiante::Estudiante(const std::string& nombre, int programa, float promedio, int creditosAprobados)
    : nombre(nombre), programa(programa), promedio(promedio), creditosAprobados(creditosAprobados) {}

// CORREGIR: registrarMota → registrarNota y creditors → creditos
void Estudiante::registrarNota(float nota, int creditos) {
    float totalPonderado = promedio * creditosAprobados;
    totalPonderado += nota * creditos;
    creditosAprobados += creditos;
    promedio = totalPonderado / creditosAprobados;
}

// CORREGIR: creditors → creditos
void Estudiante::agregarCreditos(int creditos) {
    creditosAprobados += creditos;
}

// CORREGIR: creditorsAprobados → creditosAprobados
std::string Estudiante::obtenerResumen() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Nombre: " << nombre
        << " | Programa: " << programa
        << " | Promedio: " << promedio
        << " | Creditos: " << creditosAprobados;
    return oss.str();
}
