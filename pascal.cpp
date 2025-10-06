#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generar(int filas) {
    vector<vector<int>> triangulo;
    for (int i = 0; i < filas; ++i) {
        vector<int> fila(i + 1, 1);
        for (int j = 1; j < i; ++j) {
            fila[j] = triangulo[i - 1][j - 1] + triangulo[i - 1][j];
        }
        triangulo.push_back(fila);
    }
    return triangulo;
}

int main() {
    int filas;
    cout << "Ingrese el numero de filas: ";
    if (!(cin >> filas)) {
        cerr << "error";
        return 1;
    }

    if (filas <= 0) {
        cout << "No hay filas .";
        return 0;
    }

    vector<vector<int>> pascal = generar(filas);

    cout << "triangulo (" << filas << " filas):\n";
    for (const auto& fila: pascal) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << "\n";
    }

    return 0;
}