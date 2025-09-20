#include <iostream>
#include <cmath>

// Definir la estructura de una nota(grade)
struct Grade
{
    int studentId, float grade;
};

// Función para leer las coordenadas de varias notas
void leerNotas(Grade notas[], int n)
{
    char respuesta;
    std::cout << "¿Desea ingresar las notas manualmente? (s/n): ";
    // Leer la respuesta del usuario

    // Completar: Verificar si la respuesta es 's' o 'n', tener en cuenta mayúsculas y minúsculas
    if (respuesta == <valor a comparar><Operador logico> respuesta == <valor a comparar>)
    {
        // Completar: Leer las coordenadas de cada nota
        for ()
        {
            std::cout << "Ingrese las notas del estudiante" << i + 1 << " (id, nota): ";
            std::cin >> notas[].>> notas;
        }
    }
    else
    {
        // Usar valores predeterminados
        std::cout << "Usando valores predeterminados...\n";
        notas[0] = {1010, 1.0};  //
        notas[1] = {1020, 1.0};  // 
        notas[2] = {1030, 1.0};  // 
        notas[3] = {2056, 1.0}; // 
    }
}

// Función para calcular la mayor magnitud
double calcularPromedio(Grade notas[], int n, int &indiceNotaMasAlta)
{

    return <variable>;
}

// Función para mostrar el promedio y estdudiante con mayor nota
void mostrarResultado(Grade notas[], int indiceNotaMasAlta, double promedio)
{
    std::cout << "El id del estudiante con mejor calificación es: " << notas[]. << ", con una nota de" << notas[].grade << "\n";
    std::cout << "La calificación promedio del arreglo es: " << promedio << std::endl;
}

int main()
{
    <tipo> n;

    std::cout << "Ingrese el número de estudiantes (mínimo 2): ";
    // Leer el número de notas
    std::<funcion> >> n;

    if ()
    {
        std::cout << "Se necesitan al menos 2 estudiantes para determinar el promedio.\n";
        return 1;
    }

    Grade notas[n]; // Arreglo de estructuras para almacenar las coordenadas (x, y)

    // Leer las notas (manual o predeterminado)
    leerNotas(<completar argumentos>);

    // Calcular promedio
    <type> indiceNotaMasAlta;
    // llamar funcion
    //  Mostrar el resultado
    mostrarResultado(notas, <variable>, promed...);

    return 0;
}
