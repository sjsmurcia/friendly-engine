#include <iostream>
#include <vector>
#include <string>
#include <functional> // Para std::hash
using namespace std;

// Capacidades de las tablas hash
const int TAMANO_TABLA_NUMERICA = 750;
const int TAMANO_TABLA_ALFANUMERICA = 1100;
const int TAMANO_TABLA_HASH_PREDEFINIDA = 100;

// Estructura para almacenar la posición y la llave
struct Entrada {
    string llave;
    bool ocupado;
};

// Algoritmo A: Dispersión para llaves numéricas
int hashNumerico(int llave) {
    return (llave * 3 + 7) % TAMANO_TABLA_NUMERICA;
}

// Algoritmo B: Dispersión para llaves alfanuméricas (sin librerías)
int hashAlfanumerico(const string& llave) {
    int hash = 0;
    int factor = 31;
    for (char c : llave) {
        hash = (hash * factor + c) % TAMANO_TABLA_ALFANUMERICA;
    }
    return hash;
}

// Algoritmo C: Dispersión utilizando std::hash (predefinido)
int hashPredefinido(const string& llave) {
    size_t hashValue = hash<string>{}(llave);
    return hashValue % TAMANO_TABLA_HASH_PREDEFINIDA;
}

// Clase para manejar las tres tablas hash
class TablaHash {
private:
    vector<Entrada> tablaNumerica;
    vector<Entrada> tablaAlfanumerica;
    vector<Entrada> tablaPredefinida;

public:
    // Constructor para inicializar las tablas
    TablaHash() {
        tablaNumerica.resize(TAMANO_TABLA_NUMERICA, {"", false});
        tablaAlfanumerica.resize(TAMANO_TABLA_ALFANUMERICA, {"", false});
        tablaPredefinida.resize(TAMANO_TABLA_HASH_PREDEFINIDA, {"", false});
    }

    // Insertar en tabla numérica
    bool insertarNumerico(int llave) {
        int posicion = hashNumerico(llave);
        if (tablaNumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (numérica): " << posicion << endl;
            return false;
        }
        tablaNumerica[posicion] = {to_string(llave), true};
        cout << "Llave numérica " << llave << " insertada en la posición: " << posicion << endl;
        return true;
    }

    // Insertar en tabla alfanumérica (propia)
    bool insertarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);
        if (tablaAlfanumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (alfanumérica): " << posicion << endl;
            return false;
        }
        tablaAlfanumerica[posicion] = {llave, true};
        cout << "Llave alfanumérica \"" << llave << "\" insertada en la posición: " << posicion << endl;
        return true;
    }

    // Insertar en tabla alfanumérica (predefinida)
    bool insertarPredefinido(const string& llave) {
        int posicion = hashPredefinido(llave);
        if (tablaPredefinida[posicion].ocupado) {
            cout << "Colisión detectada en la posición (predefinida): " << posicion << endl;
            return false;
        }
        tablaPredefinida[posicion] = {llave, true};
        cout << "Llave \"" << llave << "\" insertada en la posición (predefinida): " << posicion << endl;
        return true;
    }

    // Buscar en tabla numérica
    bool buscarNumerico(int llave) {
        int posicion = hashNumerico(llave);
        return tablaNumerica[posicion].ocupado && tablaNumerica[posicion].llave == to_string(llave);
    }

    // Buscar en tabla alfanumérica (propia)
    bool buscarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);
        return tablaAlfanumerica[posicion].ocupado && tablaAlfanumerica[posicion].llave == llave;
    }

    // Buscar en tabla alfanumérica (predefinida)
    bool buscarPredefinido(const string& llave) {
        int posicion = hashPredefinido(llave);
        return tablaPredefinida[posicion].ocupado && tablaPredefinida[posicion].llave == llave;
    }

    // Mostrar todas las tablas
    void mostrarTablas() {
        cout << "\nTabla Numérica:\n";
        for (int i = 0; i < TAMANO_TABLA_NUMERICA; i++) {
            if (tablaNumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llave: " << tablaNumerica[i].llave << endl;
            }
        }
        cout << "\nTabla Alfanumérica:\n";
        for (int i = 0; i < TAMANO_TABLA_ALFANUMERICA; i++) {
            if (tablaAlfanumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llave: " << tablaAlfanumerica[i].llave << endl;
            }
        }
        cout << "\nTabla Predefinida:\n";
        for (int i = 0; i < TAMANO_TABLA_HASH_PREDEFINIDA; i++) {
            if (tablaPredefinida[i].ocupado) {
                cout << "Posición: " << i << " -> Llave: " << tablaPredefinida[i].llave << endl;
            }
        }
    }
};

int main() {
       system("chcp 65001");

    // Configurar el entorno para mostrar caracteres especiales
    setlocale(LC_ALL, "es_ES.UTF-8");

    TablaHash tabla;
    int opcion, llaveNum;
    string llaveAlfa;

    do {
        cout << "\nSeleccione una opción:\n";
        cout << "1. Insertar llave numérica\n";
        cout << "2. Insertar llave alfanumérica (propia)\n";
        cout << "3. Insertar llave alfanumérica (predefinida)\n";
        cout << "4. Buscar llave numérica\n";
        cout << "5. Buscar llave alfanumérica (propia)\n";
        cout << "6. Buscar llave alfanumérica (predefinida)\n";
        cout << "7. Mostrar todas las tablas\n";
        cout << "8. Salir\n";
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
                cout << "Ingrese una llave alfanumérica (predefinida): ";
                cin >> llaveAlfa;
                tabla.insertarPredefinido(llaveAlfa);
                break;
            case 4:
                cout << "Ingrese una llave numérica a buscar: ";
                cin >> llaveNum;
                if (tabla.buscarNumerico(llaveNum)) cout << "Llave numérica encontrada.\n";
                else cout << "Llave no encontrada.\n";
                break;
            case 5:
                cout << "Ingrese una llave alfanumérica a buscar: ";
                cin >> llaveAlfa;
                if (tabla.buscarAlfanumerico(llaveAlfa)) cout << "Llave alfanumérica encontrada.\n";
                else cout << "Llave no encontrada.\n";
                break;
            case 6:
                cout << "Ingrese una llave alfanumérica (predefinida) a buscar: ";
                cin >> llaveAlfa;
                if (tabla.buscarPredefinido(llaveAlfa)) cout << "Llave encontrada.\n";
                else cout << "Llave no encontrada.\n";
                break;
            case 7:
                tabla.mostrarTablas();
                break;
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 8);

    return 0;
}
