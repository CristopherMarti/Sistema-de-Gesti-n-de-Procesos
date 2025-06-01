// ==============================================
// Proyecto: Gestor de Procesos con Estructuras Propias (Lista, Pila, Cola)
// Semana 10 - Algoritmos de búsqueda, actualización y ordenación
// ==============================================

#include <iostream>     // Para entrada y salida estándar
#include <string>       // Para usar la clase string
using namespace std;

// ================= ESTRUCTURAS PERSONALIZADAS ===================

// ----------- Lista enlazada de procesos -----------

// Estructura de un nodo de la lista de procesos
struct NodoProceso {
    int id;                     // Identificador del proceso
    string nombre;              // Nombre del proceso
    int prioridad;              // Prioridad del proceso
    int tamanoMemoria;          // Tamaño requerido de memoria
    string estado;              // Estado del proceso ("Nuevo", "En memoria", etc.)
    int memoriaAsignada;        // Memoria actualmente asignada
    NodoProceso* siguiente;     // Puntero al siguiente nodo en la lista
};

// Clase que maneja la lista enlazada de procesos
class ListaProcesos {
private:
    NodoProceso* cabeza;        // Puntero al primer nodo

public:
    ListaProcesos() : cabeza(NULL) {} // Constructor: lista vacía

    // Inserta un nuevo proceso al final de la lista
    void insertar(int id, string nombre, int prioridad, int tamano) {
        NodoProceso* nuevo = new NodoProceso{id, nombre, prioridad, tamano, "Nuevo", 0, NULL}; // Crear nuevo nodo
        if (!cabeza) {
            cabeza = nuevo; // Si la lista está vacía, nuevo nodo es la cabeza
        } else {
            NodoProceso* actual = cabeza;
            while (actual->siguiente)       // Recorrer hasta el final
                actual = actual->siguiente;
            actual->siguiente = nuevo;      // Insertar al final
        }
        cout << "Proceso insertado correctamente.\n";
    }

    // Buscar proceso por ID
    NodoProceso* buscar(int id) {
        NodoProceso* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual; // Encontrado
            actual = actual->siguiente;
        }
        return NULL; // No encontrado
    }

    // Eliminar proceso por ID
    void eliminar(int id) {
        if (!cabeza) return; // Lista vacía
        if (cabeza->id == id) {
            NodoProceso* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }
        NodoProceso* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id)
            actual = actual->siguiente;
        if (actual->siguiente) {
            NodoProceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
        }
    }

    // Mostrar todos los procesos
    void mostrarTodos() {
        NodoProceso* actual = cabeza;
        while (actual) {
            mostrar(actual); // Mostrar datos de un proceso
            cout << "-------------------\n";
            actual = actual->siguiente;
        }
    }

    // Mostrar información de un solo proceso
    void mostrar(NodoProceso* p) {
        if (p) {
            cout << "ID: " << p->id << "\nNombre: " << p->nombre << "\nPrioridad: "
                 << p->prioridad << "\nMemoria: " << p->tamanoMemoria << " KB"
                 << "\nMemoria Asignada: " << p->memoriaAsignada << " KB"
                 << "\nEstado: " << p->estado << "\n";
        }
    }

    // Obtener el primer nodo de la lista
    NodoProceso* getCabeza() { return cabeza; }
};

// ----------- Pila personalizada -----------

// Nodo para la pila (almacena solo ID)
struct Nodo {
    int id;
    Nodo* siguiente;
};

// Clase que representa una pila de IDs
class PilaMemoria {
private:
    Nodo* cima;         // Puntero a la cima
    int maxTam;         // Tamaño máximo de la pila
    int tamActual;      // Elementos actuales

public:
    PilaMemoria(int limite) : cima(NULL), maxTam(limite), tamActual(0) {}

    // Verifica si la pila está llena
    bool estaLlena() { return tamActual >= maxTam; }

    // Verifica si está vacía
    bool estaVacia() { return cima == NULL; }

    // Insertar un ID a la pila
    void push(int id) {
        if (estaLlena()) {
            cout << "Pila de memoria llena.\n";
            return;
        }
        Nodo* nuevo = new Nodo{id, cima}; // Crear nuevo nodo
        cima = nuevo;
        tamActual++;
    }

    // Eliminar el elemento superior
    void pop() {
        if (estaVacia()) return;
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
        tamActual--;
    }

    // Mostrar todos los IDs en la pila
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

// Nodo de la cola que contiene ID y prioridad
struct NodoCola {
    int id;
    int prioridad;
    NodoCola* siguiente;
};

// Cola de prioridad basada en inserción ordenada
class ColaPrioridad {
private:
    NodoCola* frente;   // Inicio de la cola
    NodoCola* final;    // No se usa directamente en esta implementación

public:
    ColaPrioridad() : frente(NULL), final(NULL) {}

    // Encolar un proceso ordenado por prioridad descendente
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

    // Desencolar el primer proceso (más prioritario)
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

    // Mostrar la cola de prioridad
    void mostrar() {
        NodoCola* actual = frente;
        int pos = 1;
        while (actual) {
            cout << pos++ << ". Proceso ID: " << actual->id << " - Prioridad: " << actual->prioridad << endl;
            actual = actual->siguiente;
        }
    }

    // Verificar si la cola está vacía
    bool estaVacia() { return frente == NULL; }
};

// ================= GESTOR DE PROCESOS ===================

class GestorProcesos {
private:
    ListaProcesos lista;       // Lista de procesos
    PilaMemoria pila;          // Pila de procesos en memoria
    ColaPrioridad cola;        // Cola de procesos por prioridad
    int memoriaTotal;          // Total de memoria disponible
    int memoriaUsada;          // Memoria actualmente utilizada

public:
    GestorProcesos(int memTotal) : pila(100), memoriaTotal(memTotal), memoriaUsada(0) {}

    // Crear e insertar nuevo proceso
    void insertarProceso() {
        int id, prioridad, tamano;
        string nombre;

        cout << "Ingrese ID del proceso: "; cin >> id;
        if (lista.buscar(id)) {
            cout << "Ya existe un proceso con ese ID.\n";
            return;
        }
        cin.ignore(); // Limpiar buffer
        cout << "Ingrese nombre del proceso: "; getline(cin, nombre);
        cout << "Ingrese prioridad (1-10): "; cin >> prioridad;
        cout << "Ingrese tamaño de memoria (KB): "; cin >> tamano;

        lista.insertar(id, nombre, prioridad, tamano); // Insertar en lista
        cola.encolar(id, prioridad);                   // Encolar en cola de prioridad
    }

    // Eliminar proceso por ID
    void eliminarProceso() {
        int id;
        cout << "Ingrese ID del proceso a eliminar: "; cin >> id;
        lista.eliminar(id);
        cout << "Proceso eliminado si existía.\n";
    }

    // Buscar proceso por ID
    void buscarProceso() {
        int id;
        cout << "Ingrese ID del proceso a buscar: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (p) lista.mostrar(p);
        else cout << "No encontrado.\n";
    }

    // Cambiar prioridad de un proceso
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

    // Asignar memoria a un proceso
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
        memoriaUsada += p->tamanoMemoria;
        p->memoriaAsignada = p->tamanoMemoria;
        p->estado = "En memoria";
        pila.push(p->id);
        cout << "Memoria asignada.\n";
    }

    // Liberar memoria de un proceso
    void liberarMemoria() {
        int id;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (!p || p->memoriaAsignada == 0) {
            cout << "Proceso no encontrado o sin memoria asignada.\n";
            return;
        }
        memoriaUsada -= p->memoriaAsignada;
        p->memoriaAsignada = 0;
        p->estado = "Listo";
        pila.pop();
        cout << "Memoria liberada.\n";
    }

    // Ejecutar todos los procesos en la cola
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

    // Mostrar estado completo del sistema
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

// ========== MENÚ PRINCIPAL ==========

// Mostrar opciones del menú principal
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

// Función principal que ejecuta el programa
int main() {
    GestorProcesos gestor(1024); // Creamos un objeto del gestor con 1024 KB de memoria disponible
    int opcion;

    // Este ciclo se repite hasta que el usuario elige salir (opción 9)
    do {
        mostrarMenu();       // Mostramos el menú con las opciones
        cin >> opcion;       // Leemos la opción que el usuario ingresó

        // Según la opción seleccionada, llamamos al método correspondiente
        switch (opcion) {
            case 1: gestor.insertarProceso(); break;         // Crea un nuevo proceso
            case 2: gestor.eliminarProceso(); break;         // Elimina un proceso existente
            case 3: gestor.buscarProceso(); break;           // Busca un proceso por ID
            case 4: gestor.modificarPrioridad(); break;      // Cambia la prioridad de un proceso
            case 5: gestor.asignarMemoria(); break;          // Asigna memoria a un proceso
            case 6: gestor.liberarMemoria(); break;          // Libera la memoria de un proceso
            case 7: gestor.ejecutarProcesos(); break;        // Ejecuta los procesos por prioridad
            case 8: gestor.mostrarEstados(); break;          // Muestra el estado actual del sistema
            case 9: cout << "Saliendo...\n"; break;          // Cierra el programa
            default: cout << "Opción inválida.\n"; break;    // Si se ingresa una opción incorrecta
        }
    } while (opcion != 9); // Ejecutar hasta que el usuario decida salir
    return 0;
}