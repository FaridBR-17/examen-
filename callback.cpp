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
        cerr << "Uso: " << argv[0] << " <operando1> <operador> <operando2>\n";
        return 1;
    }


    float op1 = atof(argv[1]);
    float op2 = atof(argv[3]);
    string operador = argv[2];

    float resultado = 0;

    if (operador == "+") {
        resultado = add(op1, op2);
    } else if (operador == "-") {
        resultado = subtract(op1, op2);
    } else if (operador == "*" || operador == "x" || operador == "X") {
        resultado = multiply(op1, op2);
    } else if (operador == "/") {
        if (op2 == 0) {
            cerr << "Error: División por cero.\n";
            return 1;
        }
        resultado = divide(op1, op2);
    } else {
        cerr << "Error: Operador no válido. Use +, -, *, x o /.\n";
        return 1;
    }

    cout << "Resultado: " << resultado << endl;
    return 0;
}
