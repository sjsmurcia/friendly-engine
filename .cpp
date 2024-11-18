#include <iostream>
#include <vector>
using namespace std;

// Capacidad de la tabla hash
const int TAMANO_TABLA = 750;

//para almacenar la posición y la llave
struct Entrada {
    int llave;
    bool ocupado;
};

//dispersión (hash) para llaves numéricas
int hashNumerico(int llave) {
    return (llave * 3 + 7) % TAMANO_TABLA;
}

class TablaHash {
private:
    vector<Entrada> tabla;

public:
    //inicializar la tabla
    TablaHash() {
        tabla.resize(TAMANO_TABLA, {-1, false});
    }

    //insertar una llave en la tabla hash
    bool insertar(int llave) {
        int posicion = hashNumerico(llave);

        // Verificar si la posición está ocupada (manejo básico de colisiones)
        if (tabla[posicion].ocupado) {
            cout << "Colisión detectada en la posición: " << posicion << endl;
            return false;
        }

        // Insertar la llave en la tabla
        tabla[posicion] = {llave, true};
        cout << "Llave " << llave << " insertada en la posición: " << posicion << endl;
        return true;
    }

    //buscar una llave en la tabla hash
    bool buscar(int llave) {
        int posicion = hashNumerico(llave);
        if (tabla[posicion].ocupado && tabla[posicion].llave == llave) {
            return true;
        }
        return false;
    }

    // Mostrar el contenido de la tabla hash
    void mostrarTabla() {
        for (int i = 0; i < TAMANO_TABLA; i++) {
            if (tabla[i].ocupado) {
                cout << "Posicion: " << i << " -> Llave: " << tabla[i].llave << endl;
            }
        }
    }
};

int main() {
    system("chcp 65001");

    // Configurar el entorno para mostrar caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");
    TablaHash tabla;

    // Menú para probar la tabla hash
    int opcion, llave;
    do {
        cout << "\n1. Insertar llave\n";
        cout << "2. Buscar llave\n";
        cout << "3. Mostrar tabla\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese una llave numérica: ";
                cin >> llave;
                tabla.insertar(llave);
                break;
            case 2:
                cout << "Ingrese una llave a buscar: ";
                cin >> llave;
                if (tabla.buscar(llave)) {
                    cout << "Llave " << llave << " encontrada en la tabla.\n";
                } else {
                    cout << "Llave no encontrada.\n";
                }
                break;
            case 3:
                tabla.mostrarTabla();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 4);

    return 0;
}
