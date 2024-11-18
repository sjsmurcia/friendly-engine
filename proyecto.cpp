#include <iostream>
#include <vector>
using namespace std;

// Capacidades de las tablas hash
const int TAMANO_TABLA_NUMERICA = 750;
const int TAMANO_TABLA_ALFANUMERICA = 1100;

// Estructura para almacenar la posición y la llave
struct Entrada {
    string llave;
    bool ocupado;
};

// Algoritmo de dispersión para llaves numéricas
int hashNumerico(int llave) {
    return (llave * 3 + 7) % TAMANO_TABLA_NUMERICA;
}

// Algoritmo de dispersión para llaves alfanuméricas
int hashAlfanumerico(const string& llave) {
    int hash = 0;
    int factor = 31; // Factor multiplicativo
    for (char c : llave) {
        hash = (hash * factor + c) % TAMANO_TABLA_ALFANUMERICA;
    }
    return hash;
}

class TablaHash {
private:
    vector<Entrada> tablaNumerica;
    vector<Entrada> tablaAlfanumerica;

public:
    // Constructor para inicializar ambas tablas
    TablaHash() {
        tablaNumerica.resize(TAMANO_TABLA_NUMERICA, {"", false});
        tablaAlfanumerica.resize(TAMANO_TABLA_ALFANUMERICA, {"", false});
    }

    // Función para insertar una llave numérica
    bool insertarNumerico(int llave) {
        int posicion = hashNumerico(llave);

        // Verificar si la posición está ocupada
        if (tablaNumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (numérica): " << posicion << endl;
            return false;
        }

        // Insertar la llave numérica
        tablaNumerica[posicion] = {to_string(llave), true};
        cout << "Llave numérica " << llave << " insertada en la posición: " << posicion << endl;
        return true;
    }

    // Función para insertar una llave alfanumérica
    bool insertarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);

        // Verificar si la posición está ocupada
        if (tablaAlfanumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (alfanumérica): " << posicion << endl;
            return false;
        }

        // Insertar la llave alfanumérica
        tablaAlfanumerica[posicion] = {llave, true};
        cout << "Llave alfanumérica \"" << llave << "\" insertada en la posición: " << posicion << endl;
        return true;
    }

    // Función para buscar una llave numérica
    bool buscarNumerico(int llave) {
        int posicion = hashNumerico(llave);
        return tablaNumerica[posicion].ocupado && tablaNumerica[posicion].llave == to_string(llave);
    }

    // Función para buscar una llave alfanumérica
    bool buscarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);
        return tablaAlfanumerica[posicion].ocupado && tablaAlfanumerica[posicion].llave == llave;
    }

    // Mostrar la tabla hash numérica
    void mostrarTablaNumerica() {
        cout << "\nTabla Hash Numérica:\n";
        for (int i = 0; i < TAMANO_TABLA_NUMERICA; i++) {
            if (tablaNumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llave: " << tablaNumerica[i].llave << endl;
            }
        }
    }

    // Mostrar la tabla hash alfanumérica
    void mostrarTablaAlfanumerica() {
        cout << "\nTabla Hash Alfanumérica:\n";
        for (int i = 0; i < TAMANO_TABLA_ALFANUMERICA; i++) {
            if (tablaAlfanumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llave: " << tablaAlfanumerica[i].llave << endl;
            }
        }
    }
};

int main() {
       system("chcp 65001");

    // Configurar el entorno para mostrar caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");
    TablaHash tabla;
    int opcion;
    string llaveAlfa;
    int llaveNum;

    do {
        cout << "\n1. Insertar llave numérica\n";
        cout << "2. Insertar llave alfanumérica\n";
        cout << "3. Buscar llave numérica\n";
        cout << "4. Buscar llave alfanumérica\n";
        cout << "5. Mostrar tabla numérica\n";
        cout << "6. Mostrar tabla alfanumérica\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese una llave numérica: ";
                cin >> llaveNum;
                tabla.insertarNumerico(llaveNum);
                break;
            case 2:
                cout << "Ingrese una llave alfanumérica: ";
                cin >> llaveAlfa;
                tabla.insertarAlfanumerico(llaveAlfa);
                break;
            case 3:
                cout << "Ingrese una llave numérica a buscar: ";
                cin >> llaveNum;
                if (tabla.buscarNumerico(llaveNum)) {
                    cout << "Llave numérica " << llaveNum << " encontrada.\n";
                } else {
                    cout << "Llave no encontrada.\n";
                }
                break;
            case 4:
                cout << "Ingrese una llave alfanumérica a buscar: ";
                cin >> llaveAlfa;
                if (tabla.buscarAlfanumerico(llaveAlfa)) {
                    cout << "Llave alfanumérica \"" << llaveAlfa << "\" encontrada.\n";
                } else {
                    cout << "Llave no encontrada.\n";
                }
                break;
            case 5:
                tabla.mostrarTablaNumerica();
                break;
            case 6:
                tabla.mostrarTablaAlfanumerica();
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 7);

    return 0;
}
