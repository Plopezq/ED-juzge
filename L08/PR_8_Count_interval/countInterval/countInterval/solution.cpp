/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
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
 * Estudiante 1:
 * Estudiante 2:
 *
 */
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

template <typename T> class SetTree {
public:
  SetTree() : root_node(nullptr), num_elems(0) {}
  SetTree(const SetTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  ~SetTree() { delete_nodes(root_node); }

  void insert(const T &elem) {
    auto [new_root, inserted] = insert(root_node, elem);
    root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const T &elem) const { return search(root_node, elem); }

  void erase(const T &elem) {
    auto [new_root, removed] = erase(root_node, elem);
    root_node = new_root;
    if (removed) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  SetTree &operator=(const SetTree &other) {
    if (this != &other) {
      num_elems = other.num_elems;
      delete_nodes(root_node);
      root_node = copy_nodes(other.root_node);
    }
    return *this;
  }

  void display(std::ostream &out) const {
    out << "{";
    display(root_node, out);
    out << "}";
  }
  
  // Nuevo método a implementar. La implementación se encuentra más adelante.
  int count_interval(const T &lower, const T &upper) const;



private:
  struct Node {
    T elem;
    Node *left, *right;

    Node(Node *left, const T &elem, Node *right)
        : left(left), elem(elem), right(right) {}
  };

  Node *root_node;
  int num_elems;

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->elem,
                      copy_nodes(node->right));
    }
  }

  static void delete_nodes(const Node *node) {
    if (node != nullptr) {
      delete_nodes(node->left);
      delete_nodes(node->right);
      delete node;
    }
  }

  static std::pair<Node *, bool> insert(Node *root, const T &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (elem < root->elem) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (root->elem < elem) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  static bool search(const Node *root, const T &elem) {
    if (root == nullptr) {
      return false;
    } else if (elem == root->elem) {
      return true;
    } else if (elem < root->elem) {
      return search(root->left, elem);
    } else {
      return search(root->right, elem);
    }
  }

  static std::pair<Node *, bool> erase(Node *root, const T &elem) {
    if (root == nullptr) {
      return {root, false};
    } else if (elem < root->elem) {
      auto [new_root_left, erased] = erase(root->left, elem);
      root->left = new_root_left;
      return {root, erased};
    } else if (root->elem < elem) {
      auto [new_root_right, erased] = erase(root->right, elem);
      root->right = new_root_right;
      return {root, erased};
    } else {
      return {remove_root(root), true};
    }
  }

  static Node *remove_root(Node *root) {
    Node *left_child = root->left, *right_child = root->right;
    delete root;
    if (left_child == nullptr && right_child == nullptr) {
      return nullptr;
    } else if (left_child == nullptr) {
      return right_child;
    } else if (right_child == nullptr) {
      return left_child;
    } else {
      auto [lowest, new_right_root] = remove_lowest(right_child);
      lowest->left = left_child;
      lowest->right = new_right_root;
      return lowest;
    }
  }

  static std::pair<Node *, Node *> remove_lowest(Node *root) {
    assert(root != nullptr);
    if (root->left == nullptr) {
      return {root, root->right};
    } else {
      auto [removed_node, new_root_left] = remove_lowest(root->left);
      root->left = new_root_left;
      return {removed_node, root};
    }
  }

  static void display(Node *root, std::ostream &out) {
   
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->elem;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }
  //Metodo auxiliar
  void count_interval_2(const Node* root, const T& lower, const T& upper) const;

};

template <typename T>
std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
  set.display(out);
  return out;
}


using namespace std;

// --------------------------------------------------------------
//@ <answer>

//
// Implementa a continuación el método pedido
// ¡No te olvides de indicar el coste!
//


template <typename T>
int SetTree<T>::count_interval(const T &lower, const T &upper) const {
  // ...
    count_interval_2(this->root_node, lower, upper);

    return 0;
}
template <typename T>
void SetTree<T>::count_interval_2(const Node* root, const T& lower, const T& upper) const {
    // ...
    int cont = 0;
    if (root == nullptr)
        //return 0;
    if (lower < root->elem) { // entramos en el hijo iz
        count_interval_2(root->left, lower, upper);
        cout << root->elem <<" ";
    }
    if ( upper > root->elem ) { // entramos en el hijo dr        
        count_interval_2(root->right, lower, upper);
        cout << root->elem << " ";;
    }

  
    

    //return 0;
}
// 
// Si necesitas métodos auxiliares privados, puedes poner su cabecera en la
// definición de la clase SetTree (aunque esté fuera de las etiquetas <answer>..</answer>)
// pero su implementación ha de estar aquí
//

// ... Métodos auxiliares ...


// 
// Implementa a continuación la función que trata un caso de prueba.
//

bool tratar_caso() {
  // Leemos los dos primeros números.
  int num_elems, num_consultas;
  cin >> num_elems >> num_consultas;
  if (cin.eof()) {
    return false;
  }
  SetTree<int> result;
  int aux;
  for (int i = 0; i < num_elems; i++) {
      cin >> aux;
      result.insert(aux);
  }
 // result.display(cout);
  /*
  vector<pair<int, int>> consultas(num_consultas);
  // first tendra el valor min del intervalo
  // second tendra el valor max del intervalo;
  for (int i = 0; i < num_consultas; i++) {
      cin >> consultas[i].first >> consultas[i].second;
  }*/
  int lower, upper;
  for (int i = 0; i < num_consultas; i++) {
 
      cin >> lower >> upper;
      cout << result.count_interval(lower, upper);
      cout << '\n';
  }

  cout << "---";

  // Continuar aquí...
  
  return true;
}


//@ </answer>
// --------------------------------------------------------------


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
