#include <iostream>
#include <cmath>

// Definir la estructura de una nota(grade)
struct Grade
{
    int studentId; float grade;
};

// Función para leer las coordenadas de varias notas
void leerNotas(Grade notas[], int n)
{
    char respuesta;
    std::cout << "¿Desea ingresar las notas manualmente? (s/n): ";
    // Leer la respuesta del usuario
    std::cin >> respuesta;

    // Verificar si la respuesta es 's' o 'n', tener en cuenta mayúsculas y minúsculas
    if (respuesta == 's' || respuesta == 'S')
    {
        // Leer las coordenadas de cada nota
        for (int i = 0; i < n; i++)
        {
            std::cout << "Ingrese las notas del estudiante " << i + 1 << " (id, nota): ";
            std::cin >> notas[i].studentId >> notas[i].grade;
            
            // Validar que la nota no exceda 5.0
            while (notas[i].grade > 5.0 || notas[i].grade < 0.0) {
                std::cout << "Error: La nota debe estar entre 0.0 y 5.0. Ingrese nuevamente: ";
                std::cin >> notas[i].grade;
            }
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
    double suma = 0.0;
    float maxNota = -1.0;
    indiceNotaMasAlta = 0;
    
    for (int i = 0; i < n; i++) {
        suma += notas[i].grade;
        if (notas[i].grade > maxNota) {
            maxNota = notas[i].grade;
            indiceNotaMasAlta = i;
        }
    }
    
    return suma / n;
}

// Función para mostrar el promedio y estudiante con mayor nota
void mostrarResultado(Grade notas[], int indiceNotaMasAlta, double promedio)
{
    std::cout << "El id del estudiante con mejor calificación es: " << notas[indiceNotaMasAlta].studentId << ", con una nota de " << notas[indiceNotaMasAlta].grade << "\n";
    std::cout << "La calificación promedio del arreglo es: " << promedio << std::endl;
}

int main()
{
    int n;

    std::cout << "Ingrese el número de estudiantes (mínimo 2): ";
    // Leer el número de notas
    std::cin >> n;

    if (n < 2)
    {
        std::cout << "Se necesitan al menos 2 estudiantes para determinar el promedio.\n";
        return 1;
    }

    Grade notas[n]; // Arreglo de estructuras para almacenar las coordenadas (x, y)

    // Leer las notas (manual o predeterminado)
    leerNotas(notas, n);

    // Calcular promedio
    int indiceNotaMasAlta;
    double promedio = calcularPromedio(notas, n, indiceNotaMasAlta);
    // Mostrar el resultado
    mostrarResultado(notas, indiceNotaMasAlta, promedio);

    return 0;
}
