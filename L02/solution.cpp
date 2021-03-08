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
 * Estudiante 1: Alejandro Casado Benito
 * Estudiante 2: Pablo Lopez Martin
 *
 */
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
  struct Node {
    int value;
    Node *next;
  };

public:
  ListLinkedSingle(): head(nullptr) { }
  ~ListLinkedSingle() {
    delete_list(head);
  }

  ListLinkedSingle(const ListLinkedSingle &other)
    : head(copy_nodes(other.head)) { }

  void push_front(const int &elem) {
    Node *new_node = new Node { elem, head };
    head = new_node;
  }

  void push_back(const int &elem);

  void pop_front() {
    assert (head != nullptr);
    Node *old_head = head;
    head = head->next;
    delete old_head;
  }

  void pop_back();

  int size() const;

  bool empty() const {
    return head == nullptr;
  };

  const int & front() const {
    assert (head != nullptr);
    return head->value;
  }

  int & front() {
    assert (head != nullptr);
    return head->value;
  }

  const int & back() const {
    return last_node()->value;
  }

  int & back() {
    return last_node()->value;
  }

  const int & at(int index) const {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  int & at(int index) {
    Node *result_node = nth_node(index);
    assert (result_node != nullptr);
    return result_node->value;
  }

  void display(std::ostream &out) const;
  void display() const {
    display(std::cout);
  }

  // Nuevo método. Debe implementarse abajo
  void intersect(const ListLinkedSingle &l2);

private:
  Node *head;

  void delete_list(Node *start_node);
  Node *last_node() const;
  Node *nth_node(int n) const;
  Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
    return result;
  } else {
    return nullptr;
  }
}

void ListLinkedSingle::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->next);
    delete start_node;
  }
}

void ListLinkedSingle::push_back(const int &elem) {
  Node *new_node = new Node { elem, nullptr };
  if (head == nullptr) {
    head = new_node;
  } else {
    last_node()->next = new_node;
  }
}

void ListLinkedSingle::pop_back() {
  assert (head != nullptr);
  if (head->next == nullptr) {
    delete head;
    head = nullptr;
  } else {
    Node *previous = head;
    Node *current = head->next;

    while (current->next != nullptr) {
      previous = current;
      current = current->next;
    }

    delete current;
    previous->next = nullptr;
  }
}

int ListLinkedSingle::size() const {
  int num_nodes = 0;

  Node *current = head;
  while (current != nullptr) {
    num_nodes++;
    current = current->next;
  }

  return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
  assert (head != nullptr);
  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
  assert (0 <= n);
  int current_index = 0;
  Node *current = head;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->next;
  }
  return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
  out << "[";
  if (head != nullptr) {
    out << head->value;
    Node *current = head->next;
    while (current != nullptr) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

// ----------------------------------------------------------------
//@ <answer>
/*
*
* En el caso peor, la funcion intersect tendria el O(n*m) siendo n num elemtnos de la lista this
* y m el numero de elementos comunes a ambas
* 
*/
// Implementa a continuación el método pedido.
void ListLinkedSingle::intersect(const ListLinkedSingle& other) {
    // Completar aquí
    Node* curThis = this->head;
    Node* prevThis = nullptr;
    Node* result = nullptr;
    Node* curOther = other.head;
    bool primera = true;

    while (curThis->next != nullptr) {
        if (curOther->value > curThis->value) {
            //Node* oldCurrent = curThis;
            curThis = curThis->next;
            //delete oldCurrent;
        }
        else if (curOther->value < curThis->value) {
            curOther = curOther->next;
        }
        else {
            if (primera) {
                this->head = curThis;
                prevThis = curThis;
                curThis = curThis->next;
                curOther = curOther->next;
                //this->head->next = nullptr;
                primera = false;
            }
            else {
                //this->push_back(curThis->value);
                //El coste del metodo push_back es O(n) siendo n el numero de elementos comunes
                prevThis->next = curThis;
                curThis = curThis->next;
                curOther = curOther->next;
            }
        }
    }
    if (primera) { //No se encuentra ningun valor igual, dejamos la
        // lista interseccion como vacia
        this->head = nullptr;
    }
}

using namespace std;


void tratar_caso() {
  // Implementar. Aquí se procesa cada caso de prueba
    int numNodos = -1;
    cin >> numNodos;
    ListLinkedSingle thisLista;
    for (int i = 0; i < numNodos; i++) {
        int aux = -1;
        cin >> aux;
        thisLista.push_back(aux);
    }
    cin >> numNodos;
    ListLinkedSingle otherLista;
    for (int i = 0; i < numNodos; i++) {
        int aux = -1;
        cin >> aux;
        otherLista.push_back(aux);
    }
    //interseccion y output
    thisLista.intersect(otherLista);
    cout << endl;

    thisLista.display();

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
