#include <iostream>
using namespace std;

// Definir la estructura de una nota (grade)
struct Grade
{
    int studentId;
    float grade;
};

// Función para leer las notas
void leerNotas(Grade notas[], int n)
{
    char respuesta;
    cout << "desea ingresar las notas manualmente? si(s) o no(n) ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S')
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Ingrese los datos del estudiante " << i + 1 << " (id nota): ";
            cin >> notas[i].studentId >> notas[i].grade;
        }
    }
    else
    {
        cout << "usando valores predeterminados: ";
        if (n >= 4)
        {
            notas[0] = {1010, 4.5};
            notas[1] = {1020, 3.8};
            notas[2] = {1030, 2.9};
            notas[3] = {2056, 5.0};
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                notas[i].studentId = 1000+i;
                notas[i].grade = 3.0+0.2*i;

            }
        }
    }
}

// Función para calcular el promedio y encontrar la nota más alta
double calcularPromedio(Grade notas[], int n, int &indiceNotaMasAlta)
{
    double suma = 0;
    indiceNotaMasAlta = 0; // inicializar con el primero

    for (int i = 0; i < n; i++)
    {
        suma += notas[i].grade;
        if (notas[i].grade > notas[indiceNotaMasAlta].grade)
        {
            indiceNotaMasAlta = i;
        }
    }
    return suma / n;
}

// Función para mostrar el promedio y estudiante con mayor nota
void mostrarResultado(Grade notas[], int indiceNotaMasAlta, double promedio)
{
    cout << "El id del estudiante con mejor calificación es: "
         << notas[indiceNotaMasAlta].studentId
         << ", con una nota de " << notas[indiceNotaMasAlta].grade <<;

    cout << "La calificación promedio del arreglo es: " << promedio << endl;
}

int main()
{
    int n;
    cout << "Ingrese el numero de estudiantes (minimo 2): ";
    cin >> n;

    if (n < 2)
    {
        cout << "se necesitan al menos 2 estudiantes para determinar el promedio ";
        return 1;
    }

    Grade *notas = new Grade[n]; // arreglo dinámico

    // Leer las notas (manual o predeterminadas)
    leerNotas(notas, n);

    // Calcular promedio y mejor nota
    int indiceNotaMasAlta;
    double promedio = calcularPromedio(notas, n, indiceNotaMasAlta);

    // Mostrar resultados
    mostrarResultado(notas, indiceNotaMasAlta, promedio);

    delete[] notas; // liberar memoria
    return 0;
}
