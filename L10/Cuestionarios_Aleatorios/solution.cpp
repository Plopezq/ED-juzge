/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
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
#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


bool tratar_caso() {

	int N, A, P;
	cin >> N >> A >> P;

	if (N == 0 && A == 0 && P == 0) return false;

	string nombre, id_Pregunta, resu;
	
	/*
		res tiene la siguiente estructura:

		key: id_pregunta -> valor:
								  key: respuesta -> valor:
														  [angel,jorge]

	*/
	unordered_map < string, unordered_map<string, vector<string>>> res;

	//Leemos los datos de los alumnos
	for (int i = 0; i < N; i++) { // cada alumno
		cin >> nombre;

		for (int i = 0; i < A; i++) { // aqui lees las respuestas del alumno
			cin >> id_Pregunta >> resu;
			
			res[id_Pregunta][resu].push_back(nombre); // vamos rellenando el unorder_map
			
		}


	}

	//aqui leemos las respuestas correctas
	pair<string, string> respuesta;
	int i = 0;
	unordered_map<string, int> correctasAlumno(0); // para guardar los alumnos que responden correctamente
	while (i < P) {
		cin >> respuesta.first >> respuesta.second; // first: idPreg, second: res

		auto a = res[respuesta.first][respuesta.second]; //

		for (int i = 0; i < a.size(); i++) {
			correctasAlumno[a[i]] += 1;
		}

		i++;
	}
	
	//tratamos los usuarios correctos
	if (correctasAlumno.empty()) { // si no hay ninguno
		cout << 0 << endl;
	}
	else {
		int cont = 0;
		for (auto [k, v] : correctasAlumno) {
			if (v == A) cont++;
		}
		cout << cont << endl;
	}
	return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
   system("PAUSE");
#endif
  return 0;
}
