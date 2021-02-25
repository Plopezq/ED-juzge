/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1:
  * Estudiante 2:
  *
  */

#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

const int GRADO_MAX = 10000;
/* Define la clase 'Polinomio' aquí */
class Polinomio {
public:
	//Constructor
	Polinomio() {
		//Inicializamos el array a 0
		for (int i = 0; i < GRADO_MAX + 1; i++) {
			coeficientes[i] = 0;
		}
	}

	//Metodos

	void anyadir_monomio(int coef, int exp) {
		this->coeficientes[exp] += coef;
	}
	long evaluar(int valor) {
		long suma = this->coeficientes[0];
		long pot = 1;
		long acum = valor;
		for (int i = 1; i < GRADO_MAX + 1; i++) {
			long aux = acum * this->coeficientes[i];
			suma += aux;
			acum = acum * valor;
			pot++;
		}
		return suma;
	}


private:
	int coeficientes[GRADO_MAX + 1];
	int max_exp;


};

bool tratar_caso() {
	int n, v;
	cin >> n >> v;
	if (n == 0 && v == 0)
		return false;
	Polinomio p;
	int coef, exp;
	for (int i = 0; i < n; ++i) {
		cin >> coef >> exp;
		p.anyadir_monomio(coef, exp);
	}
	cout << p.evaluar(v) << endl;


	return true;

}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}