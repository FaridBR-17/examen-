#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Producto {
public:
    string nombre;
    float precio;
    int stock;
    Producto(string n, float p, int s) : nombre(n), precio(p), stock(s) {}
};

class ItemCarrito {
public:
    Producto* producto;
    int cantidad;
    ItemCarrito(Producto* p, int c) : producto(p), cantidad(c) {}
};

class Carrito {
private:
    ItemCarrito* items[10];
    int contador;
public:
    Carrito() : contador(0) {}
    
    void agregarProducto(Producto* p, int cant) {
        items[contador] = new ItemCarrito(p, cant);
        contador++;
        cout << "Agregado: " << p->nombre << " x" << cant << endl;
    }
    
    float calcularTotal() {
        float total = 0;
        for(int i = 0; i < contador; i++) {
            total += items[i]->producto->precio * items[i]->cantidad;
        }
        return total;
    }
    
    void mostrar() {
        cout << "\n--- TU CARRITO ---" << endl;
        for(int i = 0; i < contador; i++) {
            float subtotal = items[i]->producto->precio * items[i]->cantidad;
            cout << items[i]->producto->nombre << " x" << items[i]->cantidad 
                 << " - $" << fixed << setprecision(0) << subtotal << " cop" << endl;
        }
        cout << "TOTAL: $" << fixed << setprecision(0) << calcularTotal() << " cop" << endl;
        cout << fixed << setprecision(2); // Resetear para otros números
    }
};

class Usuario {
public:
    string nombre;
    Carrito carrito;
    Usuario(string n) : nombre(n) {}
};

int main() {
    // Productos disponibles CON PRECIOS ACTUALIZADOS
    Producto productos[4] = {
        Producto("Laptop", 3000000, 5),
        Producto("Mouse logitech 902", 100000, 10),
        Producto("Teclado", 300000, 8),
        Producto("Audifonos", 120000, 6)
    };
    
    Usuario user("Anonimo");
    int opcion, cantidad;
    
    do {
        cout << "\n TIENDA Farid&Juan" << endl;
        cout << "1. Laptop - $3,000,000 cop" << endl;
        cout << "2. Mouse logitech 902 - $100,000 cop" << endl;
        cout << "3. Teclado - $300,000 cop" << endl;
        cout << "4. Audifonos - $120,000 cop" << endl;
        cout << "5. Ver carrito" << endl;
        cout << "6. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        
        if(opcion >= 1 && opcion <= 4) {
            cout << "Cuantos quieres? ";
            cin >> cantidad;
            user.carrito.agregarProducto(&productos[opcion-1], cantidad);
        }
        else if(opcion == 5) {
            user.carrito.mostrar();
        }
        
    } while(opcion != 6);
    
    cout << "Estuvo genial tu compra, muchas gracias " << user.nombre << "!" << endl;
    return 0;
}