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
class GestorProcesos {
private:
    ListaProcesos lista;   // Aquí se guarda la lista de todos los procesos registrados
    PilaMemoria pila;      // Esta pila nos ayuda a controlar la memoria que se va asignando a los procesos
    ColaPrioridad cola;    // Cola para gestionar los procesos según su prioridad
    int memoriaTotal;      // Capacidad total de memoria del sistema
    int memoriaUsada;      // Cuánta memoria está actualmente en uso

public:
    // Constructor que inicializa la memoria total y define la capacidad de la pila
    GestorProcesos(int memTotal) : pila(100), memoriaTotal(memTotal), memoriaUsada(0) {}

    // Permite ingresar un nuevo proceso con sus datos: ID, nombre, prioridad y tamaño
    void insertarProceso() {
        int id, prioridad, tamano;
        string nombre;

        cout << "Ingrese ID del proceso: "; cin >> id;

        // Verificamos que no se repita el ID
        if (lista.buscar(id)) {
            cout << "Ya existe un proceso con ese ID.\n";
            return;
        }

        cin.ignore();  // Limpiamos el buffer del teclado
        cout << "Ingrese nombre del proceso: "; getline(cin, nombre);
        cout << "Ingrese prioridad (1-10): "; cin >> prioridad;
        cout << "Ingrese tamaño de memoria (KB): "; cin >> tamano;

        // Insertamos el proceso en la lista y lo agregamos a la cola de prioridad
        lista.insertar(id, nombre, prioridad, tamano);
        cola.encolar(id, prioridad);
    }

    // Elimina un proceso existente según su ID
    void eliminarProceso() {
        int id;
        cout << "Ingrese ID del proceso a eliminar: "; cin >> id;
        lista.eliminar(id);
        cout << "Proceso eliminado si existía.\n";
    }

    // Permite buscar un proceso por su ID y mostrar sus datos si lo encuentra
    void buscarProceso() {
        int id;
        cout << "Ingrese ID del proceso a buscar: "; cin >> id;
        NodoProceso* p = lista.buscar(id);
        if (p) lista.mostrar(p);
        else cout << "No encontrado.\n";
    }

    // Modifica la prioridad de un proceso ya existente
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

    // Asigna memoria a un proceso si hay suficiente disponible
    void asignarMemoria() {
        int id;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);

        if (!p) {
            cout << "Proceso no encontrado.\n";
            return;
        }

        // Verificamos si ya se le asignó memoria antes
        if (p->memoriaAsignada > 0) {
            cout << "Ya tiene memoria asignada.\n";
            return;
        }

        // Validamos que haya suficiente memoria disponible
        if (memoriaUsada + p->tamanoMemoria > memoriaTotal) {
            cout << "Memoria insuficiente.\n";
            return;
        }

        // Se le asigna memoria al proceso y se actualizan los valores
        memoriaUsada += p->tamanoMemoria;
        p->memoriaAsignada = p->tamanoMemoria;
        p->estado = "En memoria";
        pila.push(p->id); // Guardamos el proceso en la pila de memoria
        cout << "Memoria asignada.\n";
    }

    // Libera la memoria que estaba usando un proceso específico
    void liberarMemoria() {
        int id;
        cout << "Ingrese ID del proceso: "; cin >> id;
        NodoProceso* p = lista.buscar(id);

        if (!p || p->memoriaAsignada == 0) {
            cout << "Proceso no encontrado o sin memoria asignada.\n";
            return;
        }

        // Se libera la memoria usada y se actualiza el estado del proceso
        memoriaUsada -= p->memoriaAsignada;
        p->memoriaAsignada = 0;
        p->estado = "Listo";
        pila.pop(); // Quitamos el proceso de la pila de memoria
        cout << "Memoria liberada.\n";
    }

    // Ejecuta los procesos que están en la cola de prioridad, uno por uno
    void ejecutarProcesos() {
        if (cola.estaVacia()) {
            cout << "No hay procesos en cola.\n";
            return;
        }

        cout << "\n== Ejecutando procesos por prioridad ==\n";
        while (!cola.estaVacia()) {
            cola.desencolar();  // Ejecuta (o más bien "saca") el proceso con mayor prioridad
        }
    }

    // Muestra el estado general del sistema: memoria, procesos, pila y cola
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


// ========== MENÚ PRINCIPAL ORIGINAL ===========

void mostrarMenu() {
    // Este menú se muestra cada vez que el usuario debe elegir una acción
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

    } while (opcion != 9); // Repetimos el menú hasta que el usuario elija salir

    return 0; // Fin del programa
}

