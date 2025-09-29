#include <iostream>
#include <string>
#include <cstdlib> 
using namespace std;

float add(float a, float b) { return a + b; }
float subtract(float a, float b) { return a - b; }
float multiply(float a, float b) { return a * b; }
float divide(float a, float b) { return a / b; }

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cerr << "instruccion: " << argv[0] << " <valor 1> <signo> <valor 2>\n";
        return 1;
    }


    float x = atof(argv[1]);
    float y = atof(argv[3]);
    string operador = argv[2];

    float resultado = 0;

    if (operador == "+") {
        resultado = add(x, y);
    } else if (operador == "-") {
        resultado = subtract(x, y);
    } else if (operador == "*" || operador == "x" || operador == "X") {
        resultado = multiply(x, y);
    } else if (operador == "/") {
        if (y == 0) {
            cerr << " División por cero.";
            return 1;
        }
        resultado = divide(x, y);
    } else {
        cerr << "Error: Operador no válido. Use +, -, *, x o /.\n";
        return 1;
    }

    cout << "Resultado: " << resultado << endl;
    return 0;
}
