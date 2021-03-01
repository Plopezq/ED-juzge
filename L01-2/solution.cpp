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
  * Estudiante 1: Pablo Lopez Martin
  * Estudiante 2: Alejandro Casado Benito
  *
  */

#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

const int MAX_MONOMIOS = 10000;
/* Define la clase 'Polinomio' aquí */
class Polinomio {
public:
	//Constructor

	/*
	* COSTE constructor --> El coste es lineal respecto a MAX_MONOMIOS
	*	O(MAX_MONOMIOS)
	*/
	Polinomio() {
		//Inicializamos el array a 0
		for (int i = 0; i < MAX_MONOMIOS; i++) {
			this->monomios[i].coeficiente = 0;
			this->monomios[i].exponente = -1;
		}
		this->num_monomios = 0;
		this->exp_max = 0;
	}

	//Metodos
	/*
	* COSTE anyadir_monomio --> El coste es constante ya que son operaciones aritméticas
	*	O(1)
	*/
	void anyadir_monomio(int coef, int exp) {
		monomios[exp].coeficiente += coef;
		if (monomios[exp].exponente != exp) {
			//Hay un nuevo monomio
			num_monomios++;
			monomios[exp].exponente = exp;
		}
		if (exp > this->exp_max) {
			this->exp_max = exp;
		}
	}
	/*
	* COSTE evaluar --> El coste es lineal respecto al exp_max 
	* que es el maximo exponente del polinomio
	*	O(exp_max)
	*/
	long evaluar(int valor) {
		long suma = monomios[0].coeficiente;
		long pot = 1;
		long acum = valor;
		for (int i = 1; i < exp_max + 1; i++) {
			long aux = acum * monomios[i].coeficiente;
			suma += aux;
			acum = acum * valor;
			pot++;
		}
		return suma;
	}


private:
	struct Monomio {
		int coeficiente;
		int exponente;
	};
	Monomio monomios[MAX_MONOMIOS];
	int num_monomios;
	int exp_max;
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