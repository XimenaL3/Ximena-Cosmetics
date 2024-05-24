#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Nodo {
    string dato;
    Nodo* siguiente;
};

class ListaSimple {
private:
    Nodo* primero;
    Nodo* ultimo;
    int size;

public:
    ListaSimple() : primero(nullptr), ultimo(nullptr), size(0) {}

    void insertarElemento(string dato) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = dato;
        nuevo->siguiente = nullptr;

        if (primero == nullptr) {
            primero = nuevo;
            ultimo = nuevo;
        }
        else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        size++;
    }

    void mostrarLista() {
        Nodo* actual = primero;
        while (actual != nullptr) {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    void ordenarBurbuja() {
        if (size <= 1)
            return;

        for (Nodo* i = primero; i->siguiente != nullptr; i = i->siguiente) {
            for (Nodo* j = primero; j->siguiente != nullptr; j = j->siguiente) {
                if (j->dato > j->siguiente->dato) {
                    string temp = j->dato;
                    j->dato = j->siguiente->dato;
                    j->siguiente->dato = temp;
                }
            }
        }
    }

    void ordenarInsercion() {
        if (size <= 1)
            return;

        Nodo* i = primero->siguiente;
        while (i != nullptr) {
            Nodo* pos = primero;

            while (pos != i && pos->dato.compare(i->dato) < 0) {
                pos = pos->siguiente;
            }

            if (pos != i) {
                string temp = i->dato;

                while (pos != i) {
                    string temp2 = pos->dato;
                    pos->dato = temp;
                    temp = temp2;
                    pos = pos->siguiente;
                }
                pos->dato = temp;
            }

            i = i->siguiente;
        }
    }

    int busquedaBinaria(string elemento) {
        if (size == 0)
            return -1;

        int inicio = 0;
        int fin = size - 1;

        while (inicio <= fin) {
            int medio = inicio + (fin - inicio) / 2;

            Nodo* actual = primero;
            for (int i = 0; i < medio; ++i)
                actual = actual->siguiente;

            if (actual->dato == elemento)
                return medio;
            else if (actual->dato < elemento)
                inicio = medio + 1;
            else
                fin = medio - 1;
        }

        return -1; // Elemento no encontrado
    }

    bool busquedaSecuencial(string elemento) {
        Nodo* actual = primero;
        while (actual != nullptr) {
            if (actual->dato == elemento)
                return true;
            actual = actual->siguiente;
        }
        return false; // Elemento no encontrado
    }

    void eliminarNodo() {
        string nodoBuscar;
        cout << "\nIngrese el dato a buscar para eliminarlo: ";
        cin >> nodoBuscar;

        Nodo* actual = primero;
        Nodo* anterior = nullptr;
        bool encontrado = false;

        if (primero != nullptr) {
            while (actual != nullptr && !encontrado) {
                if (actual->dato == nodoBuscar) {
                    cout << "\nElemento " << nodoBuscar << " encontrado\n";

                    if (actual == primero) {
                        primero = primero->siguiente;
                    }
                    else if (actual == ultimo) {
                        anterior->siguiente = nullptr;
                        ultimo = anterior;
                    }
                    else {
                        anterior->siguiente = actual->siguiente;
                    }

                    delete actual;
                    encontrado = true;
                    cout << "\nNodo " << nodoBuscar << " eliminado\n";
                }
                else {
                    anterior = actual;
                    actual = actual->siguiente;
                }
            }
            if (!encontrado) {
                cout << "\nElemento no encontrado\n";
            }
        }
        else {
            cout << "La lista se encuentra vacÃ­a\n";
        }
    }

    void modificarNodo() {
        string nodoBuscar;
        cout << "\nIngrese el dato a buscar en la lista: ";
        cin >> nodoBuscar;

        Nodo* actual = primero;
        bool encontrado = false;

        if (primero != nullptr) {
            while (actual != nullptr && !encontrado) {
                if (actual->dato == nodoBuscar) {
                    cout << "\nElemento " << nodoBuscar << " encontrado\n";

                    cout << "\nInserte el nuevo valor: ";
                    cin >> actual->dato;
                    cout << "\nEl dato anterior " << nodoBuscar << " ha sido modificado exitosamente por: " << actual->dato << endl;
                    encontrado = true;
                }
                else {
                    actual = actual->siguiente;
                }
            }
            if (!encontrado) {
                cout << "\nElemento no encontrado\n";
            }
        }
        else {
            cout << "La lista se encuentra vacÃ­a\n";
        }
    }

    void QuickSort() {
        string* arr = new string[size];
        Nodo* temp = primero;
        for (int i = 0; i < size; ++i) {
            arr[i] = temp->dato;
            temp = temp->siguiente;
        }

        QuickSortRecursive(arr, 0, size - 1);

        temp = primero;
        for (int i = 0; i < size; ++i) {
            temp->dato = arr[i];
            temp = temp->siguiente;
        }

        delete[] arr;
    }

    void ordenarSeleccion() {
        Nodo* actual = primero;
        while (actual != nullptr) {
            Nodo* minimo = actual;
            Nodo* siguiente = actual->siguiente;
            while (siguiente != nullptr) {
                if (siguiente->dato < minimo->dato) {
                    minimo = siguiente;
                }
                siguiente = siguiente->siguiente;
            }
            if (minimo != actual) {
                string temp = actual->dato;
                actual->dato = minimo->dato;
                minimo->dato = temp;
            }
            actual = actual->siguiente;
        }
    }

private:
    void QuickSortRecursive(string A[], int primero, int ultimo) {
        if (primero < ultimo) {
            int pivote = Partition(A, primero, ultimo);
            QuickSortRecursive(A, primero, pivote - 1);
            QuickSortRecursive(A, pivote + 1, ultimo);
        }
    }

    int Partition(string A[], int primero, int ultimo) {
        string pivote = A[ultimo];
        int i = primero - 1;
        for (int j = primero; j < ultimo; ++j) {
            if (A[j].compare(pivote) < 0) {
                ++i;
                swap(A[i], A[j]);
            }
        }
        swap(A[i + 1], A[ultimo]);
        return i + 1;
    }

};

int main() {
    ListaSimple lista;

    int opcion, opcion2, opcion3;
    string elemento;
    string elementoBusqueda;

    do {
        cout << "1. Insertar elemento\n";
        cout << "2. Mostrar lista\n";
        cout << "3. Ordenar\n";
        cout << "4. Buscar\n";
        cout << "5. Modificar\n";
        cout << "6. Eliminar\n";
        cout << "7. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            cout << "Ingrese el elemento: ";
            cin >> elemento;
            lista.insertarElemento(elemento);
            break;
        }
        case 2:
            cout << "Lista actual: ";
            lista.mostrarLista();
            break;
        case 3:
            cout << "1. Ordenar con Burbuja\n";
            cout << "2. Ordenar con Insercion\n";
            cout << "3. Ordenar con QuickSort\n";
            cout << "4. Ordenar con Seleccion\n";
            cout << "Opcion: ";
            cin >> opcion2;

            switch (opcion2) {
            case 1:
                cout << "Lista actual: ";
                lista.mostrarLista();
                lista.ordenarBurbuja();
                cout << "Lista ordenada con Burbuja: ";
                lista.mostrarLista();
                break;
            case 2:
                cout << "Lista actual: ";
                lista.mostrarLista();
                lista.ordenarInsercion();
                cout << "Lista ordenada con Insercion: ";
                lista.mostrarLista();
                break;
            case 3:
                cout << "Lista actual: ";
                lista.mostrarLista();
                lista.QuickSort();
                cout << "Lista ordenada con QuickSort: ";
                lista.mostrarLista();
                break;
            case 4:
                cout << "Lista actual: ";
                lista.mostrarLista();
                lista.ordenarSeleccion();
                cout << "Lista ordenada con Seleccion: ";
                lista.mostrarLista();
                break;
            default:
                cout << "Opcion no valida\n";
                break;
            }
            break;
        case 4:
            cout << "1. Busqueda con metodo binario\n";
            cout << "2. Busqueda con metodo secuencial\n";
            cout << "Opcion: ";
            cin >> opcion3;

            switch (opcion3) {
            case 1:
                cout << "Ingrese el elemento a buscar: ";
                cin >> elementoBusqueda;
                if (lista.busquedaBinaria(elementoBusqueda) != -1)
                    cout << "Elemento encontrado: " << lista.busquedaBinaria(elementoBusqueda) << endl;
                else
                    cout << "Elemento no encontrado\n";
                break;
            case 2:
                cout << "Ingrese el elemento a buscar: ";
                cin >> elementoBusqueda;
                if (lista.busquedaSecuencial(elementoBusqueda))
                    cout << "Elemento encontrado\n";
                else
                    cout << "Elemento no encontrado\n";
                break;
            default:
                cout << "Opcion no valida\n";
                break;
            }
            break;
        case 5:
            lista.modificarNodo();
            cout << "Numero Modificado...\n";
            break;
        case 6:
            lista.eliminarNodo();
            cout << "Numero Eliminado...\n";
            break;
        case 7:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no valida\n";
            break;
        }

        cout << endl << endl;
        system("pause");
        system("cls");
    } while (opcion != 7);

    return 0;
}