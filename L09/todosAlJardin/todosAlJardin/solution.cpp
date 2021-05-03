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
 * Estudiante 1: Alejandro Casado Benito
 * Estudiante 2: Pablo López Martín
 *
 */
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <stack>
#include <tuple>
#include <utility>

/*
 * Implementación del TAD Diccionario mediante árboles binarios
 * de búsqueda.
 */

template <typename K, typename V, typename ComparatorFunction = std::less<K>>
class MapTree {
private:
  template <typename S> class iterator_gen;

public:
  struct MapEntry {
    const K key;
    V value;

    MapEntry(K key, V value) : key(key), value(value) {}
    MapEntry(K key) : key(key), value() {}
  };

  using const_iterator = iterator_gen<const MapEntry>;
  using iterator = iterator_gen<MapEntry>;

  MapTree() : root_node(nullptr), num_elems(0) {}
  MapTree(ComparatorFunction less_than)
      : root_node(nullptr), num_elems(0), less_than(less_than) {}
  MapTree(const MapTree &other)
      : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
  ~MapTree() { delete_nodes(root_node); }

  void insert(const MapEntry &entry) {
    auto [new_root, inserted] = insert(root_node, entry);
    this->root_node = new_root;
    if (inserted) {
      num_elems++;
    }
  }

  bool contains(const K &key) const {
    return search(root_node, key) != nullptr;
  }

  const V &at(const K &key) const {
    Node *result = search(root_node, key);
    assert(result != nullptr);
    return result->entry.value;
  }

  V &at(const K &key) {
    Node *result = search(root_node, key);
    assert(result != nullptr);
    return result->entry.value;
  }

  V &operator[](const K &key) {
    auto [inserted, new_root, found_node] = search_or_insert(root_node, key);
    this->root_node = new_root;
    if (inserted)
      num_elems++;
    return found_node->entry.value;
  }

  void erase(const K &key) {
    auto [new_root, erased] = erase(root_node, key);
    this->root_node = new_root;
    if (erased) {
      num_elems--;
    }
  }

  int size() const { return num_elems; }
  bool empty() const { return num_elems == 0; }

  MapTree &operator=(const MapTree &other) {
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

  iterator begin() { return iterator(root_node); }

  iterator end() { return iterator(); }

  const_iterator begin() const { return const_iterator(root_node); }

  const_iterator end() const { return const_iterator(); }

  const_iterator cbegin() { return const_iterator(root_node); }

  const_iterator cend() { return const_iterator(); }

private:
  struct Node {
    MapEntry entry;
    Node *left, *right;

    Node(Node *left, const MapEntry &entry, Node *right)
        : left(left), entry(entry), right(right) {}
  };

  Node *root_node;
  int num_elems;
  ComparatorFunction less_than;

  template <typename S> class iterator_gen {
  public:
    S &operator*() const {
      assert(!st.empty());
      return st.top()->entry;
    }

    S *operator->() const { return &operator*(); }

    iterator_gen &operator++() {
      assert(!st.empty());
      Node *top = st.top();
      st.pop();
      descend_and_push(top->right, st);
      return *this;
    }

    iterator_gen operator++(int) {
      iterator_gen previous = *this;
      ++(*this);
      return previous;
    }

    bool operator==(const iterator_gen &other) { return st == other.st; }

    bool operator!=(const iterator_gen &other) {
      return !this->operator==(other);
    }

  private:
    friend class MapTree;

    iterator_gen() {}

    iterator_gen(Node *root) { descend_and_push(root, st); }

    std::stack<Node *> st;

    static void descend_and_push(Node *node, std::stack<Node *> &st) {
      Node *current = node;
      while (current != nullptr) {
        st.push(current);
        current = current->left;
      }
    }
  };

  static Node *copy_nodes(const Node *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new Node(copy_nodes(node->left), node->entry,
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

  std::pair<Node *, bool> insert(Node *root, const MapEntry &elem) {
    if (root == nullptr) {
      return {new Node(nullptr, elem, nullptr), true};
    } else if (less_than(elem.key, root->entry.key)) {
      auto [new_root_left, inserted] = insert(root->left, elem);
      root->left = new_root_left;
      return {root, inserted};
    } else if (less_than(root->entry.key, elem.key)) {
      auto [new_root_right, inserted] = insert(root->right, elem);
      root->right = new_root_right;
      return {root, inserted};
    } else {
      return {root, false};
    }
  }

  std::tuple<bool, Node *, Node *> search_or_insert(Node *root, const K &key) {
    if (root == nullptr) {
      Node *new_node = new Node(nullptr, {key}, nullptr);
      return {true, new_node, new_node};
    } else if (less_than(key, root->entry.key)) {
      auto [inserted, new_root, found_node] = search_or_insert(root->left, key);
      root->left = new_root;
      return {inserted, root, found_node};
    } else if (less_than(root->entry.key, key)) {
      auto [inserted, new_root, found_node] =
          search_or_insert(root->right, key);
      root->right = new_root;
      return {inserted, root, found_node};
    } else {
      return {false, root, root};
    }
  }

  std::pair<Node *, bool> erase(Node *root, const K &key) {
    if (root == nullptr) {
      return {root, false};
    } else if (less_than(key, root->entry.key)) {
      auto [new_root_left, erased] = erase(root->left, key);
      root->left = new_root_left;
      return {root, erased};
    } else if (less_than(root->entry.key, key)) {
      auto [new_root_right, erased] = erase(root->right, key);
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

  Node *search(Node *root, const K &key) const {
    if (root == nullptr) {
      return nullptr;
    } else if (less_than(key, root->entry.key)) {
      return search(root->left, key);
    } else if (less_than(root->entry.key, key)) {
      return search(root->right, key);
    } else {
      return root;
    }
  }

  static void display(Node *root, std::ostream &out) {
    if (root != nullptr) {
      if (root->left != nullptr) {
        display(root->left, out);
        out << ", ";
      }
      out << root->entry.key << " -> " << root->entry.value;
      if (root->right != nullptr) {
        out << ", ";
        display(root->right, out);
      }
    }
  }
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &out, const MapTree<K, V> &map) {
  map.display(out);
  return out;
}
 
 
using namespace std;

// --------------------------------------------------------------
//@ <answer>

// Escribe tu solución a partir de esta línea.
// Puedes definir las funciones auxiliares que creas.
// No está permitido modificar la clase MapTree.


//Busca el siguiente despacho disponible para los empleados
int buscarDespachoEmpleado( MapTree<int, int>& persDespacho, int aux, int C) {
    ++aux; // incrementamos al siguiente despacho
    while (persDespacho[aux] >= C) {
        ++aux;
    }
    return aux;
}

//Busca el siguiente despacho disponible para los jefes
int buscarDespachoJefe(MapTree<int, int>& persDespacho, int aux, int C) {
    ++aux; // incrementamos al siguiente despacho
    while (persDespacho[aux] == C+1) {
        ++aux;
    }
    return aux;
}

//Reubicamos empleados
void reubicarEmpleados(MapTree<int, int>& persDespacho, int despacho,int aux, int C) {
    while (persDespacho[despacho] > 0) {//meter a los demas
        ++aux; // incrementamos al siguiente despacho
        while (persDespacho[aux] >= C) {
            ++aux;
        }
        persDespacho[aux] += 1; // añadimos al siguiente disponible
        persDespacho[despacho] -= 1; // lo eliminamos del actual
        aux = despacho;
    }
    persDespacho[despacho] = C + 1;// metemos al jefe
}

//colocamos a los empleados
void colocarEmpleados(MapTree<int,int> &persDespacho, int aux, int C) {

    if (!persDespacho.contains(aux)) { //No hay nadie con ese despacho lo aggregamos
              // lo insertamos
        persDespacho[aux] = 1;
    }
    else if (persDespacho[aux] < C) { // ya existe ese despacho y quedan huecos
        persDespacho[aux] += 1;
    }
    else {// Reubicamos en el siguiente disponible

        int nuevoDespacho = buscarDespachoEmpleado(persDespacho, aux, C);
        persDespacho[nuevoDespacho] += 1;

    }
}


bool tratar_caso() {
  // Función que lee y procesa un caso de prueba
  //
    /*
        C: num despachos
        N: num empleados
        M: num jefes
    */
    int C, N, M;
    cin >> C >> N >> M;

    // Si lee la marca de fin de entrada (tres ceros), ha de devolver false
    if (C == 0 && N == 0 && M == 0) return false;
    
    MapTree<int, int> persDespacho; //  key: int con el num Despacho y valor: numPersonas

    int aux;
    for (int i = 0; i < N; ++i) { // Leemos los despachos de los empleados
        cin >> aux;
        colocarEmpleados(persDespacho, aux, C);
    }
   //comprobamos si no hay empleado
    if (persDespacho.empty()) {
        cin >> aux;
    }
    // Para los jefes
    for (int i = 0; i < M; ++i) {
       
        cin >> aux;
        if (!persDespacho.contains(aux)) { //No hay nadie con ese despacho lo aggregamos
              // lo insertamos
            persDespacho[aux] = C+1; // C+1 es para controlar que sea jefe
        }
        else  { // meter al jefe y reubicar a los demas

            if (persDespacho[aux] == C + 1) {// si hay un jefe

                int despachoJefe = buscarDespachoJefe(persDespacho,aux,C);
                reubicarEmpleados(persDespacho, despachoJefe,aux, C);

            }
            else { // si no es un jefe
                int despacho = aux;
                reubicarEmpleados(persDespacho, despacho, aux, C);
               
            }
           
        }
       
     
    }
    //persDespacho.display(cout);


    for (auto [k, v] : persDespacho) {
        
        if (v == C + 1) {
            cout << k << " " << "JEFE\n";
        }
        else {
            cout << k << " " << v << '\n';
        }
    }
    cout << "---\n";
   
  // En caso contrario, devuelve true
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
