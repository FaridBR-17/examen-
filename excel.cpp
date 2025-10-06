#include <iostream>
#include <string>
using namespace std;

int funcion(string valorcolumna) {
    long long resultado = 0;
    for (char c : valorcolumna) {
        int valor = c - 'A' + 1;   
        resultado = resultado * 26 + valor;
    }
    return resultado;
}

int main() {
    string valor;
    cout << "ingrese el titulo de la columna,tipo ab y asi: ";
    cin >> valor;

    int numero = funcion(valor);
    cout << "el numero es: " << numero << endl;

    return 0;
}
