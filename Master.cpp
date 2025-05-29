//Trabajo colaborativo C++ Equipo numero 04 
#include <iostream>
#include <string>
using namespace std;

// ----------- Lista enlazada de procesos -----------
// Estructura que representa un proceso en el sistema.
// Contiene información básica como id, nombre, prioridad, tamaño de memoria, 
// estado, cantidad de memoria asignada y un puntero al siguiente nodo.
struct NodoProceso {
    int id;                 // Identificador único del proceso
    string nombre;          // Nombre del proceso
    int prioridad;          // Prioridad del proceso (puede usarse para planificadores)
    int tamanoMemoria;      // Tamaño total de memoria que necesita el proceso
    string estado;          // Estado del proceso (ej. "Nuevo", "Listo", "Ejecutando")
    int memoriaAsignada;    // Cantidad de memoria asignada actualmente
    NodoProceso* siguiente; // Puntero al siguiente proceso en la lista enlazada
};

//Clase ListaProcesos que representa una lista enlazada simple de procesos.
//Permite insertar, buscar, eliminar y mostrar procesos.

class ListaProcesos {
private:
    NodoProceso* cabeza; // Puntero al primer nodo de la lista

public:
    // Constructor: inicializa la lista vacía
    ListaProcesos() : cabeza(NULL) {}

    //Inserta un nuevo proceso al final de la lista.
    //Recibe como parámetros los atributos del proceso.

    void insertar(int id, string nombre, int prioridad, int tamano) {
        NodoProceso* nuevo = new NodoProceso{id, nombre, prioridad, tamano, "Nuevo", 0, NULL};
        if (!cabeza) {
            // Si la lista está vacía, el nuevo proceso es la cabeza
            cabeza = nuevo;
        } else {
            // Recorre la lista hasta el último nodo y lo enlaza
            NodoProceso* actual = cabeza;
            while (actual->siguiente)
                actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso insertado correctamente.\n";
    }

    //Busca un proceso en la lista por su ID.
    //Retorna un puntero al nodo si lo encuentra, o NULL si no existe.

    NodoProceso* buscar(int id) {
        NodoProceso* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    //Elimina un proceso de la lista según su ID.
    //Ajusta los punteros para mantener la integridad de la lista.

    void eliminar(int id) {
        if (!cabeza) return; // Lista vacía

        // Si el proceso a eliminar está al inicio
        if (cabeza->id == id) {
            NodoProceso* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }

        // Recorre la lista buscando el nodo anterior al que se desea eliminar
        NodoProceso* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id)
            actual = actual->siguiente;

        // Si se encontró el nodo a eliminar
        if (actual->siguiente) {
            NodoProceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
        }
    }

    //Muestra todos los procesos de la lista llamando a la función mostrar().

    void mostrarTodos() {
        NodoProceso* actual = cabeza;
        while (actual) {
            mostrar(actual);
            cout << "-------------------\n";
            actual = actual->siguiente;
        }
    }

    //Muestra los datos de un solo proceso recibido como parámetro.

    void mostrar(NodoProceso* p) {
        if (p) {
            cout << "ID: " << p->id << "\nNombre: " << p->nombre << "\nPrioridad: "
                 << p->prioridad << "\nMemoria: " << p->tamanoMemoria << " KB"
                 << "\nMemoria Asignada: " << p->memoriaAsignada << " KB"
                 << "\nEstado: " << p->estado << "\n";
        }
    }

    //Retorna un puntero al primer proceso de la lista.
    //Útil para recorridos externos u operaciones adicionales.

    NodoProceso* getCabeza() { return cabeza; }
};


// ----------- Pila  -----------
// Definición de una estructura Nodo que representa un proceso en memoria.
// Cada nodo contiene un identificador de proceso (id) y un puntero al siguiente nodo.
struct Nodo {
    int id;           // Identificador del proceso.
    Nodo* siguiente;  // Puntero al siguiente nodo en la pila.
};

// Definición de la clase PilaMemoria que simula una pila para gestionar procesos en memoria.
class PilaMemoria {
private:
    Nodo* cima;       // Puntero al nodo en la cima de la pila (último nodo agregado).
    int maxTam;       // Tamaño máximo permitido para la pila (límite de procesos en memoria).
    int tamActual;    // Número actual de procesos en la pila.

public:
    // Constructor: inicializa la pila vacía y define el límite de procesos.
    PilaMemoria(int limite) : cima(NULL), maxTam(limite), tamActual(0) {}

    // Método para verificar si la pila está llena.
    bool estaLlena() { return tamActual >= maxTam; }

    // Método para verificar si la pila está vacía.
    bool estaVacia() { return cima == NULL; }

    // Método para agregar un nuevo proceso (nodo) a la pila.
    void push(int id) {
        if (estaLlena()) {
            cout << "Pila de memoria llena.\n"; // Mensaje si ya no se pueden agregar procesos.
            return;
        }
        // Se crea un nuevo nodo con el id proporcionado y se enlaza a la cima actual.
        Nodo* nuevo = new Nodo{id, cima};
        cima = nuevo;   // La cima ahora apunta al nuevo nodo.
        tamActual++;    // Se incrementa el contador de procesos.
    }

    // Método para eliminar el proceso en la cima de la pila (último que entró).
    void pop() {
        if (estaVacia()) return;  // Si la pila está vacía, no hay nada que eliminar.
        Nodo* temp = cima;        // Se guarda el nodo actual de la cima para eliminarlo.
        cima = cima->siguiente;   // La cima ahora apunta al nodo siguiente.
        delete temp;              // Se libera la memoria del nodo anterior.
        tamActual--;              // Se decrementa el contador de procesos.
    }

    // Método para mostrar todos los procesos actualmente en la pila.
    void mostrar() {
        Nodo* actual = cima;  // Comienza desde la cima.
        cout << "Procesos en memoria (de cima a base):\n";
        while (actual) {      // Recorre la pila hasta llegar al fondo (NULL).
            cout << "Proceso ID: " << actual->id << endl;
            actual = actual->siguiente;
        }
    }
};
// ----------- Cola -----------
struct NodoCola {
    int id;
    int prioridad;
    NodoCola* siguiente;
};

class ColaPrioridad {
private:
    NodoCola* frente;
    NodoCola* final;

public:
    ColaPrioridad() : frente(NULL), final(NULL) {}

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

    void mostrar() {
        NodoCola* actual = frente;
        int pos = 1;
        while (actual) {
            cout << pos++ << ". Proceso ID: " << actual->id << " - Prioridad: " << actual->prioridad << endl;
            actual = actual->siguiente;
        }
    }

    bool estaVacia() { return frente == NULL; }
};
// ================= GESTOR DE PROCESOS ===================



// ========== MENÚ PRINCIPAL ORIGINAL ===========


