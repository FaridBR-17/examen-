#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

/**
 * @brief Clase que representa un estudiante con su información academica.
 *Permite gestionar los datos de los estudiantes.
 *programa academico, promedio, creditos aprobados.
 */
class Estudiante {
private:
    std::string nombre;                       ///< Nombre y apellido del estudiante
    int programa;                             ///< Codigo del programa
    float promedio;                           ///< Promedio acumulado
    int creditosAprobados;                    ///< Creditos aprobados

public:
    /**
     * @brief Crea un nuevo estudiante con su info inicial.
     * @param nombre Nombre y apellido.
     * @param programa Codigo del programa.
     * @param promedio Promedio inicial de calificaciones.
     * @param creditosAprobados cantidasd de creditos aprobados.
     */
    Estudiante(const std::string& nombre, int programa, float promedio, int creditosAprobados);

    /**
     * @brief Registra una nueva nota y vuelve a calcular el promedio ponderado.
     * @param nota Nota obtenida.
     * @param creditos Creditos de la materia.
     */
    void registrarNota(float nota, int creditos);

    /**
     * @brief agrega creditos al total de creditos aprobados sain alterar el promedio.
     * @param creditos cantidad de creditos a sumar al total.
     */
    void agregarCreditos(int creditos);

    /**
     * @brief genera un texto cont toda la info importante del estudiante.
     * @return un tipo string nuevo con nombrwe, programa, promedio y cretidos.
     */
    std::string obtenerResumen() const;

    /**
     * @brief verifica si cumple los créditos requeridos para graduarse.
     * @param creditosRequeridos Creditos necesarios.
     * @return true si tiene los creditos necesarios, false sino.
     */
    bool cumpleRequisitosGrado(int creditosRequeridos) const;
};

inline bool Estudiante::cumpleRequisitosGrado(int creditosRequeridos) const {
    return creditosAprobados >= creditosRequeridos;
}

#endif 
