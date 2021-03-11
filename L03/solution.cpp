/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no será corregida.
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


class ListLinkedDouble {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }

  ~ListLinkedDouble() { delete_nodes(); }

  void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const int &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }

  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }

  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }

  int size() const { return num_elems; }

  bool empty() const { return num_elems == 0; };

  const int &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  int &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const int &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  int &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const int &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  int &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }

  void partition(int pivot);

  void display(std::ostream &out) const;
  void display_reverse(std::ostream &out) const;

  void display() const { display(std::cout); }
  void display_reverse() const { display_reverse(std::cout); }

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
  void detach(Node *node);
  void attach(Node *node, Node *position);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedDouble::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;

  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

void ListLinkedDouble::display_reverse(std::ostream &out) const {
  out << "[";
  if (head->prev != head) {
    out << head->prev->value;
    Node *current = head->prev->prev;
    while (current != head) {
      out << ", " << current->value;
      current = current->prev;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

// ----------------------------------------------------------------
//@ <answer>

// Implementa a continuación los métodos pedidos:

//El coste de la funcion detach es constante, O(1)
void ListLinkedDouble::detach(Node *node) {
  
    node->prev->next = node->next;
    node->next->prev = node->prev;

    //¿Hacemos algo co el nuestro? -> NO
}
//El coste de la funcion attach es constante, O(1)
void ListLinkedDouble::attach(Node *node, Node *position) {
    //Hay que ponerlo antes de position
    Node* old_prev = position->prev;
    position->prev->next = node;
    position->prev = node;

    node->next = position;
    node->prev = old_prev;
}

void ListLinkedDouble::partition(int pivot) {
  //[5,10,9,7,4,6] ---> [5,7,4,6,10,9]
    
    Node* prev = head->next;//Primer nodo a tratar
    Node* iterator = head->next;
    while (iterator != head) {
        if (iterator->value > pivot) { //Se va al final
            detach(iterator);
            attach(iterator, head);
        }//else { //Se queda
        iterator = iterator->next;
    }
}

using namespace std;

void tratar_caso() {
    ListLinkedDouble lista;
    int aux;
    cin >> aux;
    while (aux != 0) {
        lista.push_back(aux);
        cin >> aux;
    }
    int pivote;
    cin >> pivote;
    lista.partition(pivote);

    lista.display();
    cout << endl;
    lista.display_reverse();
    cout << endl;

}


//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  // Leemos el número de casos de prueba que vendrán a continuación
  int num_casos;
  cin >> num_casos;

  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif
  return 0;
}
