#include <iostream>
using namespace std;

bool palindromo(int x) {
   
    if (x < 0) return false;

    long long inicial = x;
    long long invertido = 0;

    while (x > 0) {
        int digito = x % 10;                                                                                                                                                                
        invertido= invertido * 10 + digito; 
        x /= 10;                    
    }

    return inicial == invertido;
}

int main() {
    int x;
    cout << "Ingrese el numero: ";
    cin >> x;

    if (palindromo(x))
        cout << "es palindromo" << endl;
    else
        cout << "no es palindromo" << endl;

    return 0;
}