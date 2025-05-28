//Trabajo colaborativo C++ Equipo numero 04 
#include <iostream>
#include <string>
using namespace std;

// ----------- Lista enlazada de procesos -----------


// ----------- Pila personalizada -----------
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

// ----------- Cola personalizada -----------


// ================= GESTOR DE PROCESOS ===================



// ========== MENÚ PRINCIPAL ORIGINAL ===========