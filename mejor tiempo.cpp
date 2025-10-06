#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int ganancia(vector<int>& precios) {
    int minprecio = INT_MAX;
    int maxganancia = 0;

    for (int precio : precios) {
        if (precio < minprecio)
            minprecio = precio;
        else if (precio - minprecio > maxganancia)
            maxganancia = precio- minprecio;
    }

    return maxganancia;
}

int main() {
    int n;
    cout << "diga los dias:";
    cin >> n;

    vector<int> precios(n);
    cout << "Ingrese los precios separados por espacio:";
    for (int i = 0; i < n; i++) {
        cin >> precios[i];
    }

    int resultado = ganancia(precios);
    cout << "La ganancia maxima posible es:" << resultado << endl;

    return 0;
}