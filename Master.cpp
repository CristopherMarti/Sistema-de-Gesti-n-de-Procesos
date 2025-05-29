// ==============================================
// Proyecto: Gestor de Procesos con Estructuras Propias (Lista, Pila, Cola)
// Semana 10 - Algoritmos de búsqueda, actualización y ordenación
// ==============================================
#include <iostream>
#include <string>
using namespace std;

// ================= ESTRUCTURAS PERSONALIZADAS ===================

// ----------- Lista enlazada de procesos -----------
// Nodo para representar un proceso en la lista enlazada
struct NodoProceso {
    int id;                 // Identificador del proceso
    string nombre;          // Nombre del proceso
    int prioridad;          // Prioridad del proceso
    int tamanoMemoria;      // Tamaño de memoria requerido por el proceso (KB)
    string estado;          // Estado actual del proceso (Ej. Nuevo, En memoria, Listo)
    int memoriaAsignada;    // Cantidad de memoria asignada al proceso (KB)
    NodoProceso* siguiente; // Puntero al siguiente nodo en la lista
};

// Clase para manejar la lista enlazada de procesos
class ListaProcesos {
private:
    NodoProceso* cabeza; // Puntero al primer nodo de la lista

public:
    // Constructor que inicializa la lista vacía
    ListaProcesos() : cabeza(NULL) {}

    // Inserta un nuevo proceso al final de la lista
    void insertar(int id, string nombre, int prioridad, int tamano) {
        NodoProceso* nuevo = new NodoProceso{id, nombre, prioridad, tamano, "Nuevo", 0, NULL};
        if (!cabeza) {  // Si la lista está vacía, el nuevo nodo será la cabeza
            cabeza = nuevo;
        } else {
            // Recorre la lista hasta el último nodo
            NodoProceso* actual = cabeza;
            while (actual->siguiente)
                actual = actual->siguiente;
            // Inserta el nuevo nodo al final
            actual->siguiente = nuevo;
        }
        cout << "Proceso insertado correctamente.\n";
    }

    // Busca un proceso por su ID y devuelve su nodo o NULL si no existe
    NodoProceso* buscar(int id) {
        NodoProceso* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    // Elimina un proceso dado su ID si existe
    void eliminar(int id) {
        if (!cabeza) return;  // Lista vacía, no hacer nada
        if (cabeza->id == id) {  // Si el primer nodo es el que se quiere eliminar
            NodoProceso* temp = cabeza;
            cabeza = cabeza->siguiente;  // Avanza la cabeza
            delete temp;  // Libera memoria del nodo eliminado
            return;
        }
        // Buscar el nodo anterior al que se va a eliminar
        NodoProceso* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id)
            actual = actual->siguiente;
        if (actual->siguiente) {
            NodoProceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;  // Salta el nodo a eliminar
            delete temp;  // Libera memoria
        }
    }

    // Muestra la información de todos los procesos en la lista
    void mostrarTodos() {
        NodoProceso* actual = cabeza;
        while (actual) {
            mostrar(actual);
            cout << "-------------------\n";
            actual = actual->siguiente;
        }
    }

    // Muestra la información de un proceso específico
    void mostrar(NodoProceso* p) {
        if (p) {
            cout << "ID: " << p->id << "\nNombre: " << p->nombre << "\nPrioridad: "
                 << p->prioridad << "\nMemoria: " << p->tamanoMemoria << " KB"
                 << "\nMemoria Asignada: " << p->memoriaAsignada << " KB"
                 << "\nEstado: " << p->estado << "\n";
        }
    }

    // Devuelve la cabeza de la lista
    NodoProceso* getCabeza() { return cabeza; }
};

// ----------- Pila personalizada -----------
// Nodo para la pila, que almacena IDs de procesos
struct Nodo {
    int id;         // ID del proceso almacenado
    Nodo* siguiente; // Puntero al siguiente nodo en la pila
};

// Clase para manejar la pila de memoria
class PilaMemoria {
private:
    Nodo* cima;      // Puntero a la cima de la pila
    int maxTam;      // Tamaño máximo de la pila
    int tamActual;   // Tamaño actual (cantidad de elementos)

public:
    // Constructor que inicializa la pila vacía con límite maxTam
    PilaMemoria(int limite) : cima(NULL), maxTam(limite), tamActual(0) {}

    // Verifica si la pila está llena
    bool estaLlena() { return tamActual >= maxTam; }

    // Verifica si la pila está vacía
    bool estaVacia() { return cima == NULL; }

    // Inserta un nuevo ID en la cima de la pila
    void push(int id) {
        if (estaLlena()) {
            cout << "Pila de memoria llena.\n";
            return;
        }
        Nodo* nuevo = new Nodo{id, cima}; // Nuevo nodo apunta a la cima actual
        cima = nuevo;  // Nueva cima es el nuevo nodo
        tamActual++;   // Incrementa el tamaño actual
    }

    // Elimina el nodo en la cima de la pila
    void pop() {
        if (estaVacia()) return;
        Nodo* temp = cima;
        cima = cima->siguiente; // La cima pasa a ser el siguiente nodo
        delete temp;            // Libera memoria del nodo eliminado
        tamActual--;            // Decrementa el tamaño actual
    }

    // Muestra los IDs de procesos almacenados en la pila
    void mostrar() {
        Nodo* actual = cima;
        cout << "Procesos en memoria (de cima a base):\n";
        while (actual) {
            cout << "Proceso ID: " << actual->id << endl;
            actual = actual->siguiente;
        }
    }
};

// ----------- Cola personalizada -----------
struct NodoCola {
    int id;             // ID del proceso
    int prioridad;      // Prioridad del proceso
    NodoCola* siguiente; // Puntero al siguiente nodo en la cola
};

// Variables globales que representan la cola
NodoCola* frente = NULL;
NodoCola* final = NULL; // No se usa en esta lógica, pero queda declarado igual

// Función para encolar un proceso según su prioridad (de mayor a menor)
void encolar(int id, int prioridad) {
    NodoCola* nuevo = new NodoCola{id, prioridad, NULL};

    if (!frente || prioridad > frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
    } else {
        NodoCola* actual = frente;
        while (actual->siguiente && actual->siguiente->prioridad >= prioridad)
            actual = actual->siguiente;
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

// Función para desencolar el proceso de mayor prioridad (el que está al frente)
void desencolar() {
    if (!frente) {
        cout << "Cola vacía.\n";
        return;
    }
    NodoCola* temp = frente;
    frente = frente->siguiente;
    cout << "Ejecutando proceso con ID: " << temp->id << " y prioridad: " << temp->prioridad << endl;
    delete temp;
}

// Función para mostrar solo el primer proceso en la cola
void mostrar() {
    if (frente) {
        cout << "Proceso ID: " << frente->id << " - Prioridad: " << frente->prioridad << endl;
    } else {
        cout << "Cola vacía." << endl;
    }
}

// Función para saber si la cola está vacía
bool estaVacia() {
    return frente == NULL;
}


// ================= GESTOR DE PROCESOS ===================
// Clase que gestiona la lista de procesos, pila de memoria y cola de prioridad
class GestorProcesos {
private:
    ListaProcesos lista;   // Lista enlazada de procesos
    PilaMemoria pila;      // Pila para gestión de memoria
    ColaPrioridad cola;    // Cola para ejecución según prioridad
    int memoriaTotal;      // Memoria total disponible (KB)
    int memoriaUsada;      // Memoria actualmente asignada (KB)

public:
    // Constructor que inicializa pila con límite 100 y memoria total dada
    GestorProcesos(int memTotal) : pila(100), memoriaTotal(memTotal), memoriaUsada(0) {}

    // Inserta un nuevo proceso, evita IDs duplicados, y lo encola
    void insertarProceso() {
        int id, prioridad, tamano;
        string nombre;

        cout << "Ingrese ID del proceso: "; cin >> id;
        if (lista.buscar(id)) {  // Verifica si ID ya existe
            cout << "Ya existe un proceso con ese ID.\n";
            return;
        }
        cin.ignore();
        cout << "Ingrese nombre del proceso: "; getline(cin, nombre);
        cout << "Ingrese prioridad (1-10): "; cin >> prioridad;
        cout << "Ingrese tamaño de memoria (KB): "; cin >> tamano;

        lista.insertar(id, nombre, prioridad, tamano);  // Inserta en la lista
        cola.encolar(id, prioridad);                      // Encola por prioridad
    }

    // Elimina un proceso dado su ID
    void eliminarProceso() {
        int id;
        cout << "Ingrese ID del proceso a eliminar: "; cin >> id;
        lista.eliminar(id);
        cout << "Proceso eliminado si existía.\n";
    }

    // Busca un proceso por ID y muestra sus datos
    void buscarProceso() {
        int id;
        cout << "Ingrese ID del proceso a buscar: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (p) lista.mostrar(p);
        else cout << "No encontrado.\n";
    }

    // Modifica la prioridad de un proceso existente
    void modificarPrioridad() {
        int id, prioridad;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (p) {
            cout << "Nueva prioridad: "; cin >> prioridad;
            p->prioridad = prioridad;
            cout << "Prioridad actualizada.\n";
        } else {
            cout << "No encontrado.\n";
        }
    }

    // Asigna memoria a un proceso si hay suficiente memoria disponible
    void asignarMemoria() {
        int id;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (!p) {
            cout << "Proceso no encontrado.\n";
            return;
        }
        if (p->memoriaAsignada > 0) {
            cout << "Ya tiene memoria asignada.\n";
            return;
        }
        if (memoriaUsada + p->tamanoMemoria > memoriaTotal) {
            cout << "Memoria insuficiente.\n";
            return;
        }
        memoriaUsada += p->tamanoMemoria;  // Actualiza memoria usada
        p->memoriaAsignada = p->tamanoMemoria;  // Asigna memoria al proceso
        p->estado = "En memoria";  // Cambia estado
        pila.push(p->id);  // Añade proceso a la pila de memoria
        cout << "Memoria asignada.\n";
    }

    // Libera la memoria asignada a un proceso y lo remueve de la pila
    void liberarMemoria() {
        int id;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (!p || p->memoriaAsignada == 0) {
            cout << "Proceso no encontrado o sin memoria asignada.\n";
            return;
        }
        memoriaUsada -= p->memoriaAsignada;  // Reduce memoria usada
        p->memoriaAsignada = 0;               // Libera memoria del proceso
        p->estado = "Listo";                  // Cambia estado a listo
        pila.pop();                          // Remueve de la pila (LIFO)
        cout << "Memoria liberada.\n";
    }

    // Ejecuta todos los procesos en cola según su prioridad
    void ejecutarProcesos() {
        if (cola.estaVacia()) {
            cout << "No hay procesos en cola.\n";
            return;
        }
        cout << "\n== Ejecutando procesos por prioridad ==\n";
        while (!cola.estaVacia()) {
            cola.desencolar();
        }
    }

    // Muestra el estado actual del sistema: memoria, lista, pila y cola
    void mostrarEstados() {
        cout << "\n== ESTADO DEL SISTEMA ==\n";
        cout << "Memoria total: " << memoriaTotal << " KB\n";
        cout << "Memoria usada: " << memoriaUsada << " KB\n";
        cout << "Memoria disponible: " << memoriaTotal - memoriaUsada << " KB\n\n";

        cout << "-- Procesos en lista --\n";
        lista.mostrarTodos();

        cout << "-- Pila de memoria --\n";
        pila.mostrar();

        cout << "-- Cola de prioridad --\n";
        cola.mostrar();
    }
};

// ========== MANTENER MENÚ PRINCIPAL ORIGINAL ===========
// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\n=== Gestor de Procesos ===" << endl;
    cout << "1. Crear nuevo proceso" << endl;
    cout << "2. Eliminar proceso por ID" << endl;
    cout << "3. Buscar proceso" << endl;
    cout << "4. Modificar prioridad de proceso" << endl;
    cout << "5. Asignar memoria a proceso" << endl;
    cout << "6. Liberar memoria de proceso" << endl;
    cout << "7. Ejecutar procesos por prioridad" << endl;
    cout << "8. Mostrar estados del sistema" << endl;
    cout << "9. Salir" << endl;
    cout << "Seleccione una opción: ";
}

// Función principal
int main() {
    GestorProcesos gestor(1024); // Inicializa gestor con 1024 KB de memoria total
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case 1: gestor.insertarProceso(); break;
            case 2: gestor.eliminarProceso(); break;
            case 3: gestor.buscarProceso(); break;
            case 4: gestor.modificarPrioridad(); break;
            case 5: gestor.asignarMemoria(); break;
            case 6: gestor.liberarMemoria(); break;
            case 7: gestor.ejecutarProcesos(); break;
            case 8: gestor.mostrarEstados(); break;
            case 9: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 9);
    return 0;
}
