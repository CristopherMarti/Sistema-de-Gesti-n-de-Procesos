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


// ----------- Pila personalizada -----------


// ----------- Cola personalizada -----------


// ================= GESTOR DE PROCESOS ===================



// ========== MENÚ PRINCIPAL ORIGINAL ===========


