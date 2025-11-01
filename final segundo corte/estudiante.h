#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

/**
 * @brief Clase que representa un estudiante con su información académica.
 */
class Estudiante {
private:
    std::string nombre;        ///< Nombre del estudiante
    int programa;              ///< Código del programa
    float promedio;            ///< Promedio acumulado
    int creditosAprobados;     ///< Créditos aprobados

public:
    /**
     * @brief Constructor que inicializa todos los atributos.
     * @param nombre Nombre del estudiante.
     * @param programa Código del programa.
     * @param promedio Promedio inicial.
     * @param creditosAprobados Créditos aprobados iniciales.
     */
    Estudiante(const std::string& nombre, int programa, float promedio, int creditosAprobados);

    /**
     * @brief Registra una nueva nota y actualiza el promedio ponderado.
     * @param nota Nota obtenida.
     * @param creditos Créditos de la materia.
     */
    void registrarNota(float nota, int creditos);

    /**
     * @brief Suma créditos al total de créditos aprobados.
     * @param creditos Créditos a añadir.
     */
    void agregarCreditos(int creditos);

    /**
     * @brief Devuelve un resumen con los datos principales del estudiante.
     * @return Cadena con la información general.
     */
    std::string obtenerResumen() const;

    /**
     * @brief Obtiene el promedio del estudiante
     * @return Promedio del estudiante
     */
    float obtenerPromedio() const { return promedio; }

    /**
     * @brief Verifica si cumple los créditos requeridos para graduarse.
     * @param creditosRequeridos Créditos necesarios.
     * @return true si cumple los requisitos, false en caso contrario.
     */
    bool cumpleRequisitosGrado(int creditosRequeridos) const;
};

/// Implementación a mano del método solicitado
inline bool Estudiante::cumpleRequisitosGrado(int creditosRequeridos) const {
    return creditosAprobados >= creditosRequeridos;
}

#endif // ESTUDIANTE_H
