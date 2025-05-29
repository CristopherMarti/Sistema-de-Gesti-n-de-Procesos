//Trabajo colaborativo C++ Equipo numero 04 
#include <iostream>
#include <string>
using namespace std;

// ----------- Lista enlazada de procesos -----------
struct NodoProceso {
    int id;
    string nombre;
    int prioridad;
    int tamanoMemoria;
    string estado;
    int memoriaAsignada;
    NodoProceso* siguiente;
};

class ListaProcesos {
private:
    NodoProceso* cabeza;

public:
    ListaProcesos() : cabeza(NULL) {}

    void insertar(int id, string nombre, int prioridad, int tamano) {
        NodoProceso* nuevo = new NodoProceso{id, nombre, prioridad, tamano, "Nuevo", 0, NULL};
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            NodoProceso* actual = cabeza;
            while (actual->siguiente)
                actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso insertado correctamente.\n";
    }

    NodoProceso* buscar(int id) {
        NodoProceso* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    void eliminar(int id) {
        if (!cabeza) return;
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

    void mostrarTodos() {
        NodoProceso* actual = cabeza;
        while (actual) {
            mostrar(actual);
            cout << "-------------------\n";
            actual = actual->siguiente;
        }
    }

    void mostrar(NodoProceso* p) {
        if (p) {
            cout << "ID: " << p->id << "\nNombre: " << p->nombre << "\nPrioridad: "
                 << p->prioridad << "\nMemoria: " << p->tamanoMemoria << " KB"
                 << "\nMemoria Asignada: " << p->memoriaAsignada << " KB"
                 << "\nEstado: " << p->estado << "\n";
        }
    }

    NodoProceso* getCabeza() { return cabeza; }
};


// ----------- Pila  -----------
struct Nodo {
    int id;
    Nodo* siguiente;
};

class PilaMemoria {
private:
    Nodo* cima;
    int maxTam;
    int tamActual;

public:
    PilaMemoria(int limite) : cima(NULL), maxTam(limite), tamActual(0) {}

    bool estaLlena() { return tamActual >= maxTam; }
    bool estaVacia() { return cima == NULL; }

    void push(int id) {
        if (estaLlena()) {
            cout << "Pila de memoria llena.\n";
            return;
        }
        Nodo* nuevo = new Nodo{id, cima};
        cima = nuevo;
        tamActual++;
    }

    void pop() {
        if (estaVacia()) return;
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
        tamActual--;
    }

    void mostrar() {
        Nodo* actual = cima;
        cout << "Procesos en memoria (de cima a base):\n";
        while (actual) {
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


