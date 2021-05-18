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
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class AcademiaChino {
public:
  // Definiciones públicas ¡No olvides el coste!
	AcademiaChino() : grupos(7) {}

	void nuevo_estudiante(string const& DNI, int const& grupo) {
		if (estudiantes.count(DNI)) {
			throw std::domain_error("Estudiante existente");
		}
		if (grupo < 1 || grupo > 6) {
			throw std::domain_error("Grupo incorrecto");
		}

		grupos[grupo].push_front(DNI);
		estudiantes[DNI].grupo = grupo;


	}

	void promocionar(string const& DNI) {
		infoEstudiante& info = buscar_alumno(DNI);
		
		
		int grupo_actual = info.grupo;
		list<string>& cola = grupos[grupo_actual]; // seleccionamos el grupo
		auto it = find(cola.begin(), cola.end(), DNI); // buscamos al estudiante

		if (grupo_actual == 6 && !info.graduado) { // si se gradua
			info.graduado = true;
			grad[DNI].grupo= grupo_actual;
			grad[DNI].graduado= true;

		}
		else if (info.graduado) {
			throw std::domain_error("Estudiante ya graduado");
		}
		else {
			cola.erase(it); // lo eliminamos de la cola
			int nuevo_grupo = info.grupo += 1; // le pasamos de grupo
			grupos[nuevo_grupo].push_front(DNI); // le metemos al nuevo grupo
		}

	}

	 int grupo_estudiante(string const& DNI) const{
		//devuelve el grupo del estudiante
		const infoEstudiante& info = buscar_alumno(DNI);
		if (info.graduado) {
			throw std::domain_error("Estudiante ya graduado");
		}
		return info.grupo;

	}

	 vector<string> graduados() const{
		vector<string> result;

		for (const auto& [k, v] : grad) {
			result.push_back(k);
		}
		return result;
	}

	string novato(int const& grupo) {
		if (grupo < 1 || grupo > 6) {
			throw std::domain_error("Grupo incorrecto");
		}
		if (grupos[grupo].empty()) {
			throw std::domain_error("Grupo vacio");
		}

		return grupos[grupo].front();
	}

private:    
  // Definiciones privadas
	struct infoEstudiante {
		int grupo;
		bool graduado;

		infoEstudiante() : graduado(false) {}
	};

	vector<list<string>> grupos;
	map<string, infoEstudiante> estudiantes; // dni, grupo

	map<string, infoEstudiante> grad; // dni, grupo


	const infoEstudiante& buscar_alumno(string const& dni) const {
		auto it_alumno = estudiantes.find(dni);
		if (it_alumno == estudiantes.end()) {
			throw domain_error("Estudiante no existente");
		}
		return it_alumno->second;
	}

	infoEstudiante& buscar_alumno(string const& dni) {
		auto it_alumno = estudiantes.find(dni);
		if (it_alumno == estudiantes.end()) {
			throw domain_error("Estudiante no existente");
		}
		return it_alumno->second;
	}
};

bool tratar_caso() {
  // Implementar
	string operacion;
	cin >> operacion;

	if (!cin) return false;

	string alumno;
	int grupo;

	AcademiaChino acad;

	while (operacion != "FIN") {
		try
		{
			if (operacion == "nuevo_estudiante") {
				cin >> alumno >> grupo;
				acad.nuevo_estudiante(alumno, grupo);
			}
			else if (operacion == "grupo_estudiante") {
				cin >> alumno;

				int grupo = acad.grupo_estudiante(alumno);
				cout << alumno << " " << "esta en el grupo" << " " << grupo << endl;
				
			}
			else if (operacion == "promocionar") {
				cin >> alumno;
				acad.promocionar(alumno);
			}
			else if (operacion == "graduados") {
				
				vector<string> result =acad.graduados();
				cout << "Lista de graduados: ";
				for (const string& alumno : result) {
					cout << alumno << " ";
				}
				cout << "\n";
			}
			else if (operacion == "novato") {
				cin >> grupo;
				string nov = acad.novato(grupo);
				cout << "Novato de " <<  grupo << ": "  << nov << endl;
			}
			
		}
		catch (const std::exception& e)
		{
			cout << "ERROR: "<< e.what() << endl;
		}
		cin >> operacion;
	}
	//Tratamos los datos
	cout << "---\n";
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
  // system("PAUSE");
#endif
  return 0;
}
