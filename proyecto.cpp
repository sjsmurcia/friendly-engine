#include <iostream>
#include <vector>
#include <string>
#include <functional> 
#include <list> 
using namespace std;


const int TAMANO_TABLA_NUMERICA = 750;
const int TAMANO_TABLA_ALFANUMERICA = 1100;
const int TAMANO_TABLA_HASH_PREDEFINIDA = 100;


struct Entrada {
    vector<string> llaves;  // Ahora puede almacenar múltiples llaves por posición (para compartimientos)
    bool ocupado;           // Indicador de si la posición está ocupada
};

// Algoritmo A: Dispersión para llaves numéricas (sin librerías)
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

// Función de hash secundaria para manejar colisiones mediante doble dispersión
int hashSecundario(int llave, int i) {
    return (hashPredefinido(to_string(llave)) + i * i) % TAMANO_TABLA_HASH_PREDEFINIDA;
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

    // Insertar en tabla numérica (método de saturación progresiva)
    bool insertarNumerico(int llave) {
        int posicion = hashNumerico(llave);

        // Búsqueda lineal para encontrar una posición libre
        while (tablaNumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (numérica): " << posicion << endl;
            posicion = (posicion + 1) % TAMANO_TABLA_NUMERICA; // Avanzamos a la siguiente posición
        }

        // Insertamos la llave en la posición encontrada
        tablaNumerica[posicion].llaves.push_back(to_string(llave));
        tablaNumerica[posicion].ocupado = true;
        cout << "Llave numérica " << llave << " insertada en la posición: " << posicion << endl;
        return true;
    }

    // Insertar en tabla alfanumérica (método de compartimientos)
    bool insertarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);

        // Si la posición está ocupada, agregamos la nueva llave al compartimiento
        if (tablaAlfanumerica[posicion].ocupado) {
            cout << "Colisión detectada en la posición (alfanumérica): " << posicion << endl;
            tablaAlfanumerica[posicion].llaves.push_back(llave); // Agregar la nueva llave al compartimiento
        } else {
            // Si no hay colisión, insertamos la llave directamente
            tablaAlfanumerica[posicion].llaves.push_back(llave);
            tablaAlfanumerica[posicion].ocupado = true; // Marcamos la posición como ocupada
        }

        cout << "Llave alfanumérica \"" << llave << "\" insertada en la posición: " << posicion << endl;
        return true;
    }

    // Insertar en tabla predefinida (método de doble dispersión)
    bool insertarPredefinido(const string& llave) {
        int posicion = hashPredefinido(llave);
        int intentos = 0;

        // Aplicamos doble dispersión si hay colisión
        while (tablaPredefinida[posicion].ocupado) {
            cout << "Colisión detectada en la posición (predefinida): " << posicion << endl;
            intentos++;  // Incrementamos el contador de intentos
            posicion = hashSecundario(hashPredefinido(llave), intentos); // Usamos la segunda función de hash
        }

        // Insertamos la llave en la posición disponible
        tablaPredefinida[posicion].llaves.push_back(llave);
        tablaPredefinida[posicion].ocupado = true;
        cout << "Llave \"" << llave << "\" insertada en la posición (predefinida): " << posicion << endl;
        return true;
    }

    // Buscar en tabla numérica
    bool buscarNumerico(int llave) {
        int posicion = hashNumerico(llave);
        for (const auto& l : tablaNumerica[posicion].llaves) {
            if (l == to_string(llave)) {
                return true;
            }
        }
        return false;
    }

    // Buscar en tabla alfanumérica
    bool buscarAlfanumerico(const string& llave) {
        int posicion = hashAlfanumerico(llave);
        for (const auto& l : tablaAlfanumerica[posicion].llaves) {
            if (l == llave) {
                return true;
            }
        }
        return false;
    }

    // Buscar en tabla predefinida
    bool buscarPredefinido(const string& llave) {
        int posicion = hashPredefinido(llave);
        for (const auto& l : tablaPredefinida[posicion].llaves) {
            if (l == llave) {
                return true;
            }
        }
        return false;
    }

    // Mostrar todas las tablas
    void mostrarTablas() {
        cout << "\nTabla Numérica:\n";
        for (int i = 0; i < TAMANO_TABLA_NUMERICA; i++) {
            if (tablaNumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llaves: ";
                for (const auto& l : tablaNumerica[i].llaves) {
                    cout << l << " ";
                }
                cout << endl;
            }
        }
        cout << "\nTabla Alfanumérica:\n";
        for (int i = 0; i < TAMANO_TABLA_ALFANUMERICA; i++) {
            if (tablaAlfanumerica[i].ocupado) {
                cout << "Posición: " << i << " -> Llaves: ";
                for (const auto& l : tablaAlfanumerica[i].llaves) {
                    cout << l << " ";
                }
                cout << endl;
            }
        }
        cout << "\nTabla Predefinida:\n";
        for (int i = 0; i < TAMANO_TABLA_HASH_PREDEFINIDA; i++) {
            if (tablaPredefinida[i].ocupado) {
                cout << "Posición: " << i << " -> Llaves: ";
                for (const auto& l : tablaPredefinida[i].llaves) {
                    cout << l << " ";
                }
                cout << endl;
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
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 8);

    return 0;
}
