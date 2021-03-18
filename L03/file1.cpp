/*
 * Introduce el nombre y apellidos de los/as componentes del grupo:
 *
 * Estudiante 1:
 * Estudiante 2:
 *
 */

//Siendo n el tamaño de las listas
//En el caso peor el Coste O(n^2) 

// Implementa a continuación el método pedido.
void ListLinkedSingle::intersect(const ListLinkedSingle &other) {
    // Completar aquí
    Node *cur;
    Node *prev;
    Node *aux;

    if (other.empty()) {
        this->delete_list(this->head);
        this->head = nullptr;
        return;
    }

    if (this->empty()){
        return;
    }

    cur = this->head;
    prev = nullptr;
    aux = other.head;

    while (cur != nullptr) {

        int v = cur->value;

        while (aux->value < v && aux->next != nullptr) { aux = aux->next;}

        if (v == aux->value) {
            if (prev == nullptr) {
                prev = cur;
            }
            else {
                prev->next = cur;
                prev = cur;
            }
            cur = cur->next;    //AVANZAR
        }
        /*
            if (prev == nullptr) {
                cur = cur->next;    //AVANZAR
                this->pop_front();
            }
            else if (prev->next != nullptr) {
                prev->next = nullptr;
                Node *oldNext = cur;
                cur = cur->next;    //AVANZAR
                delete oldNext;
            }
        */
        else {
            cur = cur->next;    //AVANZAR
            if (prev == nullptr) {
                this->pop_front();
            }
            else if (prev->next != nullptr) {
                prev->next = nullptr;
            }
        }
    }

}

using namespace std;

//Coste lineal con respecto al tamaño de las listas (mSize y otherSize)
void tratar_caso() {
  // Implementar. Aquí se procesa cada caso de prueba
    ListLinkedSingle mListLinkedSingle;
    ListLinkedSingle mOther;
    int mSize;
    int otherSize;

    std::cin >> mSize;
    for (int i = 0; i < mSize; i++) {
        int n;
        std::cin >> n;
        mListLinkedSingle.push_back(n);
    }

    std::cin >> otherSize;
    for (int j = 0; j < otherSize; j++) {
        int n;
        std::cin >> n;
        mOther.push_back(n);
    }

    mListLinkedSingle.intersect(mOther);
    mListLinkedSingle.display();
    std::cout << endl;
}


