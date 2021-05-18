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
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class AcademiaChino {
public:
  // Definiciones públicas ¡No olvides el coste!

	//coste: O(N) siendo N el numero de grupos de la academia
	AcademiaChino(int num_grupos) : grupos(num_grupos+1), num_grupos(num_grupos) {} // grupos(num_grupos+1) porque empieza en 1

	//coste: O(1)
	void nuevo_estudiante(string const& DNI, int const& grupo) {
		if (estudiantes.count(DNI)) {
			throw std::domain_error("Estudiante existente");
		}
		if (grupo < 1 || grupo > num_grupos) {
			throw std::domain_error("Grupo incorrecto");
		}

		grupos[grupo].push_front(DNI); // la cola
		estudiantes[DNI].grupo = grupo; // unordermap
		estudiantes[DNI].it_estudiante = grupos[grupo].begin(); // apuntamos
	}

	//coste: O(1)
	void promocionar(string const& DNI) {
		infoEstudiante& info = buscar_alumno(DNI);
		if (info.graduado) {
			throw std::domain_error("Estudiante ya graduado");
		}
	
		int grupo_actual = info.grupo;
		list<string>& cola = grupos[grupo_actual]; // seleccionamos el grupo
		
		//auto it = find(cola.begin(), cola.end(), DNI); // buscamos al estudiante
		
		if (grupo_actual == 6) { // si se gradua
			grupos[info.grupo].erase(info.it_estudiante); // lo eliminamos de los grupos
			grad[DNI].grupo = grupo_actual; // lo añadimos a los graduados
			info.graduado = true;
		}
		
		else {
			cola.erase(info.it_estudiante); // lo eliminamos de la cola
			int nuevo_grupo = info.grupo += 1; // le pasamos de grupo
			grupos[nuevo_grupo].push_front(DNI); // le metemos al nuevo grupo
			info.it_estudiante = grupos[nuevo_grupo].begin(); // actualizamos
		}

	}

	//coste: O(1)
	 int grupo_estudiante(string const& DNI) const{
		//devuelve el grupo del estudiante
		const infoEstudiante& info = buscar_alumno(DNI);
		if (info.graduado) {
			throw std::domain_error("Estudiante ya graduado");
		}
		return info.grupo;

	}

	 //coste: O(N) siendo N el numero de alumnos que se han graduado
	 list<string> graduados() const{
		list<string> result;
		
		for (const auto& [k, v] : grad) {
			result.push_back(k);
		}
		return result;
	}
 
	//coste: O(1)
	string novato(int const& grupo) const{
		if (grupo < 1 || grupo > num_grupos) {
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
		list<string>::iterator it_estudiante;

		infoEstudiante() : graduado(false) {}
	};

	vector<list<string>> grupos;

	unordered_map<string, infoEstudiante> estudiantes; // dni, grupo

	map<string, infoEstudiante> grad; // dni, grupo
	int num_grupos;

	//coste: O(1)
	const infoEstudiante& buscar_alumno(string const& dni) const {
		auto it_alumno = estudiantes.find(dni);
		if (it_alumno == estudiantes.end()) {
			throw domain_error("Estudiante no existente");
		}
		return it_alumno->second;
	}

	//coste: O(1)
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

	AcademiaChino acad(6);

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
				
				list<string> result =acad.graduados();
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
