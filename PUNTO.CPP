#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehiculo {
protected:
    string marca, modelo, placa;
    bool disponible;

public:
    Vehiculo(string m, string mo, string p)
        : marca(m), modelo(mo), placa(p), disponible(true) {}

    virtual void mostrarInformacion() {
        cout << "Marca: " << marca
             << " | Modelo: " << modelo
             << " | Placa: " << placa
             << " | Estado: " << (disponible ? "Disponible" : "Alquilado") << endl;
    }

    bool estaDisponible() const { return disponible; }
    void alquilar() { disponible = false; }
    void devolver() { disponible = true; }
    string getPlaca() const { return placa; }

    virtual ~Vehiculo() {}
};

class Auto : public Vehiculo {
private:
    int capacidadPasajeros;

public:
    Auto(string m, string mo, string p, int cap)
        : Vehiculo(m, mo, p), capacidadPasajeros(cap) {}

    void mostrarInformacion() override {
        cout << "[AUTO] ";
        Vehiculo::mostrarInformacion();
        cout << "  Capacidad de pasajeros: " << capacidadPasajeros << endl;
    }
};

class Bicicleta : public Vehiculo {
private:
    string tipo; // Montaña, Ruta, etc.

public:
    Bicicleta(string m, string mo, string p, string t)
        : Vehiculo(m, mo, p), tipo(t) {}

    void mostrarInformacion() override {
        cout << "[BICICLETA] ";
        Vehiculo::mostrarInformacion();
        cout << "  Tipo: " << tipo << endl;
    }
};

class SistemaAlquiler {
private:
    vector<Vehiculo*> vehiculos;

public:
    void registrarVehiculo(Vehiculo* v) {
        vehiculos.push_back(v);
    }

    void mostrarVehiculos() {
        cout << "\n--- Banco de vehículos ---\n";
        for (auto v : vehiculos) {
            v->mostrarInformacion();
            cout << "---------------------------\n";
        }
    }

    void mostrarDisponibles() {
        cout << "\n--- Vehículos disponibles ---\n";
        bool hay = false;
        for (auto v : vehiculos) {
            if (v->estaDisponible()) {
                v->mostrarInformacion();
                cout << "---------------------------\n";
                hay = true;
            }
        }
        if (!hay)
            cout << "No hay vehículos disponibles.\n";
    }

    void alquilarVehiculo() {
        string placa;
        cout << "Ingrese la placa del vehículo a alquilar: ";
        cin >> placa;
        for (auto v : vehiculos) {
            if (v->getPlaca() == placa) {
                if (v->estaDisponible()) {
                    v->alquilar();
                    cout << "✅ Vehículo alquilado exitosamente.\n";
                } else {
                    cout << "❌ Ese vehículo ya está alquilado.\n";
                }
                return;
            }
        }
        cout << "❌ No se encontró un vehículo con esa placa.\n";
    }

    void devolverVehiculo() {
        string placa;
        cout << "Ingrese la placa del vehículo a devolver: ";
        cin >> placa;
        for (auto v : vehiculos) {
            if (v->getPlaca() == placa) {
                if (!v->estaDisponible()) {
                    v->devolver();
                    cout << "✅ Vehículo devuelto exitosamente.\n";
                } else {
                    cout << "❌ Ese vehículo no estaba alquilado.\n";
                }
                return;
            }
        }
        cout << "❌ No se encontró un vehículo con esa placa.\n";
    }

    ~SistemaAlquiler() {
        for (auto v : vehiculos)
            delete v;
    }
};

int main() {
    SistemaAlquiler sistema;

    // Banco inicial de 3 vehículos
    sistema.registrarVehiculo(new Auto("Toyota", "Corolla", "ABC123", 5));
    sistema.registrarVehiculo(new Auto("Chevrolet", "Spark", "XYZ789", 4));
    sistema.registrarVehiculo(new Bicicleta("GW", "Rally", "BIK001", "Montaña"));

    cout << "\n======= BANCO INICIAL DE VEHÍCULOS =======\n";
    sistema.mostrarVehiculos();

    int opcion;
    do {
        cout << "\n====== MENÚ DE ALQUILER ======\n";
        cout << "1. Mostrar todos los vehículos\n";
        cout << "2. Mostrar solo los disponibles\n";
        cout << "3. Alquilar vehículo\n";
        cout << "4. Devolver vehículo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                sistema.mostrarVehiculos();
                break;
            case 2:
                sistema.mostrarDisponibles();
                break;
            case 3:
                sistema.alquilarVehiculo();
                break;
            case 4:
                sistema.devolverVehiculo();
                break;
            case 5:
                cout << "👋 Saliendo del sistema...\n";
                break;
            default:
                cout << "❌ Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}