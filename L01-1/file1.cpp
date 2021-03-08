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
#include <cmath>
using namespace std;


  /* Define la clase 'Polinomio' aquí */
const int MAX_MONOMIOS = 10000;
/*I(p) = 0 ≤ p.num_monomios ≤ MAX_MONOMIOS
∧ ∀i : 0 ≤ i < p.num_monomios ⇒ p.monomios[i].coeficiente != 0 //Ningun hueco vacio
∧ ∀i,j : 0 ≤ i < j < p.num_monomios ⇒ p.monomios[i].exponente < p.monomios[j].exponente*/ //Ordenador


/*
Constructora :  Creación del objeto polinomio con coste constante 0(1) en cualquier caso

Anyadir_monomio : Añadir en un array de monomios el monomio del fichero, si sale un monomio de exponente repetido
se le suma el coeficiente respectivo, en el caso que se vuelva 0 hay que eliminarlo de la lista, 
si no es igual busca su posicion donde deba ir ,en el caso que su sitio sea el ultimo se introduce al final del array
tiene un coste lineal respecto al tamaño del array  en el caso peor, 0(n), siendo n = num_monomios 
dentro de sus iteraciones tiene siempre asignaciones de coste constante 0(1)

Evaluar:  // Recorrido del array con coste lineal respecto al tamaño del array,es decir, n= num_monomios con orden de 0(n*k),
siendo n el numero de monomios introducidos en el array y k el exponente del monomio de la posicion [num_monomios], dentro del bucle hay asignaciones de coste constante 0(1)

*/
class Polinomio {
public:     
	Polinomio() : num_monomios(0) {}     
	void anyadir_monomio(int coef, int exp) {
		if (coef != 0) {
			int i = 0;
			bool introducido = false; 
			bool igual = false;
				while (i < num_monomios && !introducido && !igual) {
					if (monomios[i].exponente == exp) {     //Si es repetido el exponente se le suma 
						if (monomios[i].coeficiente + coef != 0) {
							monomios[i].coeficiente += coef;
							igual = true;
						}
						else {
							for (int j = i; j < num_monomios; j++) {   //En el caso que el exponente se pone a 0 se elimina del array
								monomios[j] = monomios[j+1];
							}
							num_monomios--;
							igual = true;    //Utilizamos otro booleano porque si el exponente es igual cuando termine su operacion queremos que no haga nada mas
						}
					}
					else if (monomios[i].exponente > exp) {      //Si no es igual se le busca en la posicion que debería ir
						introducido = true;
					}
					else i++;



				}
				if (!igual) {  //Si no eran iguales estudie que caso es o al final del array o una posicion especifica 
					if (i == num_monomios && !introducido) {    // Si ha llegado al final del array y no ha introducido el monomio lo introduce al final
						monomios[num_monomios].coeficiente = coef;
						monomios[num_monomios].exponente = exp;
						num_monomios++;
					}
					else if (monomios[i].exponente > exp) {   // En el caso que haya encontrado su posicion adecuada empuja hacia la derecha todos los monomios
						for (int j = num_monomios - 1; j >= i; j--) {
							monomios[j + 1] = monomios[j];
						}
						monomios[i].coeficiente = coef;  //Y lo introduce en su posicion
						monomios[i].exponente = exp;
						num_monomios++;
					}
				}
		}
		
	}
	long evaluar(int valor) const {   
		long exponenteResult = 1;   
		int j = 0;
		long evaluado = 0;
		for (int i = 0; i < num_monomios; i++) {
			while(j< monomios[i].exponente){
				exponenteResult *= valor;
				j++;
			}
			evaluado += exponenteResult * monomios[i].coeficiente;
	
		}
		return evaluado;
	}
private:
	struct Monomio {
		int coeficiente;
		int exponente;
	};
	Monomio monomios[MAX_MONOMIOS];//polinomio
	// 0 < num_monomios < MAX_MONOMIOS
	int num_monomios;
};

bool tratar_caso() {
	Polinomio p;
	int valor;
	int parejas;
	cin >> parejas;
	cin >> valor;
	if (parejas == 0 && valor == 0) return false;

		int coef, exp;
		int i = 0;
		while (i < parejas) {
			cin >> coef;
			cin >> exp;
			p.anyadir_monomio(coef, exp);
			i++;
		}
	
	cout << p.evaluar(valor) << endl;
	

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