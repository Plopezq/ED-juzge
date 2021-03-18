/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas no será
 * corregida.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

//@ <answer>
/*
 * Introduce el nombre y apellidos de los/as componentes del grupo:
 *
 * Estudiante 1: Pablo Lopez Martin
 * Estudiante 2: Alejandro Casado Benito
 *
 */
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/stack_array/stack_array.h
// Colas: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/queue_array/queue_array.h
// Colas dobles: https://github.com/manuelmontenegro/ED-2021/blob/master/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).

#ifndef __STACK_ARRAY_H
#define __STACK_ARRAY_H

const int DEFAULT_CAPACITY = 10;

template <typename T> class StackArray {
public:
    StackArray(int initial_capacity = DEFAULT_CAPACITY)
        : num_elems(0), capacity(initial_capacity), elems(new T[capacity]) {}

    ~StackArray() { delete[] elems; }

    StackArray(const StackArray& other);
    StackArray& operator=(const StackArray<T>& other);

    void push(const T& elem) {
        if (num_elems == capacity) {
            resize_array(capacity * 2);
        }

        elems[num_elems] = elem;
        num_elems++;
    }

    void pop() {
        assert(num_elems > 0);
        num_elems--;
    }

    const T& top() const {
        assert(num_elems > 0);
        return elems[num_elems - 1];
    }

    T& top() {
        assert(num_elems > 0);
        return elems[num_elems - 1];
    }

    bool empty() const { return num_elems == 0; }

private:
    int num_elems;
    int capacity;
    T* elems;

    void resize_array(int new_capacity);
};

template <typename T>
StackArray<T>::StackArray(const StackArray<T>& other)
    : num_elems(other.num_elems), capacity(other.capacity),
    elems(new T[other.capacity]) {
    for (int i = 0; i < num_elems; i++) {
        elems[i] = other.elems[i];
    }
}

template <typename T> void StackArray<T>::resize_array(int new_capacity) {
    T* new_elems = new T[new_capacity];

    for (int i = 0; i < num_elems; i++) {
        new_elems[i] = elems[i];
    }

    delete[] elems;
    elems = new_elems;
    capacity = new_capacity;
}

template <typename T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& other) {
    if (this != &other) {
        if (capacity < other.num_elems) {
            delete[] elems;
            elems = new T[other.capacity];
            capacity = other.capacity;
        }
        num_elems = other.num_elems;
        for (int i = 0; i < num_elems; i++) {
            elems[i] = other.elems[i];
        }
    }

    return *this;
}

#endif
// ----------------------------------------------------------------
//@ <answer>
bool tratar_caso() {
    StackArray<int> pila(100);

    int num;
    cin >> num;
    pila.push(num); //Primer caso
    cout << "NO HAY" << endl;
    while (num != -1) {
        cin >> num;
        if (pila.top() > num) {
            cout << pila.top() << endl;
            pila.push(num);
        }
        else { //pila.top() < num
            while (pila.top() < num) {
                pila.pop();
            }
            cout << pila.top() << endl;
            pila.push(num);
        }
    }
    
    return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
