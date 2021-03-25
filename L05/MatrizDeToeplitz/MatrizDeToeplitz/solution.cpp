/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */
 
 
/*
 * Introduce el nombre y apellidos de los/as componentes del grupo:
 *
 * Estudiante 1: Alejandro Casado Benito
 * Estudiante 2: Pablo López Martín
 *
 */

#include <iostream>
#include <fstream>
#include <list>


using namespace std;

/*
	El coste de la funcion es_Toeplitz en el caso peor es O(n*m) siend0 n la longitud de la lista principal y m 
	la longitud de cada lista interior.
	Por ejemplo:
				[ [3,2,1,4] , [4,3,2,5], [5,4,3,6] ]

				n sería = tamaño lista principal que es 3  y  m sería = tamaño las listas internas que es 4

*/
bool es_toeplitz( list<list<int>> &matriz) {
  // Implementar
	
	list<list<int>>::iterator itPadre = matriz.begin(); // pos 1
	list<list<int>>::iterator itPadre2 = ++matriz.begin(); // pos sig
	bool isToeplitz = true;
	// [ [3,2,1] , [4,3,2], [5,4,3] ]

	while (itPadre2 != matriz.end() && isToeplitz) { // Fila principal [ 3, 2, 1]
		list<int>::iterator itHija = itPadre->begin();
		list<int>::iterator itHija2 = ++itPadre2->begin(); // [4,3,2]
		//
		while (itHija2 != itPadre2->end() && isToeplitz) { // Fila interiores 
			if (*itHija != *itHija2) {
				isToeplitz = false;
			}
			++itHija;
			++itHija2;
		}
		++itPadre;
		++itPadre2;
	}
	
	
	return isToeplitz;
}

bool tratar_caso() {
  // Implementar
	int num;
	cin >> num;
	if (num == 0) return false;
	list<int> lectura;
	lectura.push_back(num);
	list<list<int>> matriz;
	cin >> num;
	while (num != 0) {
		while (num != 0) {
			lectura.push_back(num);
			cin >> num;
		}
		matriz.push_back(lectura);
		lectura.clear();
		cin >> num;
	}
	if (es_toeplitz(matriz)) cout << "SI\n";
	else cout << "NO\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif

  return 0;
}