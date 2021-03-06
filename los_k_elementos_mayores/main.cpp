#include<iostream>
#include <cassert>
#include <iomanip>
#include <fstream>

const int MAX = 1000;

using namespace std;

class conjuntoInt {
public:
	conjuntoInt(): num_elems(0){}
	void anyadir(int num) { //Anyade de forma ordenada
		int i = 0;
		while (i < num_elems && elems[i] > num) {
			i++;
		}
		if (i < num_elems && elems[i] != num) {//no hay elementos repetidos
			assert(num_elems < MAX);
			for (int j = num_elems; j > i; j--) { //Desplazamos a la derecha para anyadir por la izq
				elems[num_elems] = elems[num_elems - 1];
			}
		}
		elems[i] = num;
		num_elems++;
	}
	int tamanyo() {
		return num_elems;
	}
	void eliminar_menor() {
		//Como estan ordenados de MAYOR a MENOR, con quitar el ultimo es suficiente
		assert(num_elems > 0);
		num_elems--;
	}
	int menor() const {
		assert(num_elems > 0);
		return elems[num_elems - 1];
	}


private:
	int elems[MAX];
	int num_elems;
};

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 
	conjuntoInt conjunto;


	char tipo;
	std::cin >> tipo;
	int num_elementos;
	std::cin >> num_elementos;
	int aux;
	cin >> aux;
	while(aux != -1){
		conjunto.anyadir(aux);
		cin >> aux;
	}


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}












