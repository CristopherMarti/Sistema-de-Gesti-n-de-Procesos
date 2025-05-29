#include <iostream>
#include <string>
using namespace std;

// ================= ESTRUCTURAS PERSONALIZADAS ===================

// ----------- Lista enlazada de procesos -----------

// Estructura que representa un proceso en el sistema.
struct NodoProceso {
    int id;                 // Identificador único del proceso
    string nombre;          // Nombre del proceso
    int prioridad;          // Prioridad del proceso (puede usarse para planificadores)
    int tamanoMemoria;      // Tamaño total de memoria que necesita el proceso
    string estado;          // Estado del proceso (ej. "Nuevo", "Listo", "Ejecutando")
    int memoriaAsignada;    // Cantidad de memoria asignada actualmente
    NodoProceso* siguiente; // Puntero al siguiente proceso en la lista enlazada
};

// Clase ListaProcesos que representa una lista enlazada simple de procesos.
class ListaProcesos {
private:
    NodoProceso* cabeza; // Puntero al primer nodo de la lista

public:
    ListaProcesos() : cabeza(NULL) {}

    // Inserta un nuevo proceso al final de la lista.
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

    // Busca un proceso en la lista por su ID.
    NodoProceso* buscar(int id) {
        NodoProceso* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    // Elimina un proceso de la lista según su ID.
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

    // Muestra todos los procesos de la lista llamando a la función mostrar().
    void mostrarTodos() {
        NodoProceso* actual = cabeza;
        while (actual) {
            mostrar(actual);
            cout << "-------------------\n";
            actual = actual->siguiente;
        }
    }

    // Muestra los datos de un solo proceso recibido como parámetro.
    void mostrar(NodoProceso* p) {
        if (p) {
            cout << "ID: " << p->id << "\nNombre: " << p->nombre << "\nPrioridad: "
                 << p->prioridad << "\nMemoria: " << p->tamanoMemoria << " KB"
                 << "\nMemoria Asignada: " << p->memoriaAsignada << " KB"
                 << "\nEstado: " << p->estado << "\n";
        }
    }

    // Retorna un puntero al primer proceso de la lista.
    NodoProceso* getCabeza() { return cabeza; }
};

// ----------- Cola personalizada -----------

struct NodoCola {
    int id;                // Identificador del proceso
    int prioridad;         // Prioridad del proceso
    NodoCola* siguiente;   // Puntero al siguiente nodo en la cola
};

class ColaPrioridad {
private:
    NodoCola* frente;      // Puntero al primer nodo de la cola (mayor prioridad)
    NodoCola* final;       // Puntero al último nodo de la cola (no se usa en este código)

public:
    ColaPrioridad() : frente(NULL), final(NULL) {}

    // Inserta un nuevo proceso en la cola respetando el orden de prioridad (mayor primero)
    void encolar(int id, int prioridad) {
        NodoCola* nuevo = new NodoCola{id, prioridad, NULL};  // Crear nuevo nodo

        if (!frente || prioridad > frente->prioridad) {
            nuevo->siguiente = frente;  // Insertar al inicio
            frente = nuevo;
        } else {
            NodoCola* actual = frente;
            while (actual->siguiente && actual->siguiente->prioridad >= prioridad)
                actual = actual->siguiente;

            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    // Elimina y procesa el nodo con mayor prioridad (el frente)
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

    // Muestra todos los nodos de la cola con sus IDs y prioridades
    void mostrar() {
        NodoCola* actual = frente;
        int pos = 1;
        while (actual) {
            cout << pos++ << ". Proceso ID: " << actual->id << " - Prioridad: " << actual->prioridad << endl;
            actual = actual->siguiente;
        }
    }

    // Retorna true si la cola está vacía
    bool estaVacia() { return frente == NULL; }
};

// ================= GESTOR DE PROCESOS ===================

class GestorProcesos {
private:
    ListaProcesos lista;
    ColaPrioridad cola;
    int memoriaTotal;
    int memoriaUsada;

public:
    GestorProcesos(int memTotal) : memoriaTotal(memTotal), memoriaUsada(0) {}

    // Opción para insertar un nuevo proceso
    void insertarProceso() {
        int id, prioridad, tamano;
        string nombre;

        cout << "Ingrese ID del proceso: "; cin >> id;
        if (lista.buscar(id)) {
            cout << "Ya existe un proceso con ese ID.\n";
            return;
        }

        cin.ignore();
        cout << "Ingrese nombre del proceso: "; getline(cin, nombre);
        cout << "Ingrese prioridad (1-10): "; cin >> prioridad;
        cout << "Ingrese tamaño de memoria (KB): "; cin >> tamano;

        lista.insertar(id, nombre, prioridad, tamano);
        cola.encolar(id, prioridad);
    }

    // Opción para eliminar un proceso
    void eliminarProceso() {
        int id;
        cout << "Ingrese ID del proceso a eliminar: "; cin >> id;
        lista.eliminar(id);
        cout << "Proceso eliminado si existía.\n";
    }

    // Opción para buscar un proceso por su ID
    void buscarProceso() {
        int id;
        cout << "Ingrese ID del proceso a buscar: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (p) lista.mostrar(p);
        else cout << "No encontrado.\n";
    }

    // Opción para modificar la prioridad de un proceso
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

    // Opción para asignar memoria a un proceso
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
        cout << "Memoria asignada.\n";
    }

    // Opción para liberar memoria de un proceso
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
        p->estado = "Nuevo";
        cout << "Memoria liberada.\n";
    }

    // Opción para ejecutar el proceso con mayor prioridad
    void ejecutarProceso() {
        if (cola.estaVacia()) {
            cout << "No hay procesos en la cola.\n";
            return;
        }
        cola.desencolar();
    }

    // Mostrar la lista completa de procesos
    void mostrarLista() {
        lista.mostrarTodos();
    }

    // Mostrar la cola de procesos con prioridad
    void mostrarCola() {
        cola.mostrar();
    }
};

// ================= FUNCION PRINCIPAL ===================

int main() {
    GestorProcesos gestor(1024); // 1024 KB de memoria total
    int opcion;

    do {
        cout << "\nGestor de Procesos\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Asignar memoria\n";
        cout << "6. Liberar memoria\n";
        cout << "7. Ejecutar proceso\n";
        cout << "8. Mostrar lista de procesos\n";
        cout << "9. Mostrar cola de prioridad\n";
        cout << "10. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: gestor.insertarProceso(); break;
            case 2: gestor.eliminarProceso(); break;
            case 3: gestor.buscarProceso(); break;
            case 4: gestor.modificarPrioridad(); break;
            case 5: gestor.asignarMemoria(); break;
            case 6: gestor.liberarMemoria(); break;
            case 7: gestor.ejecutarProceso(); break;
            case 8: gestor.mostrarLista(); break;
            case 9: gestor.mostrarCola(); break;
            case 10: break;
            default: cout << "Opción no válida.\n"; break;
        }
    } while (opcion != 10);

    return 0;
}
