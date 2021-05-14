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
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {
public:
  void nuevo_estado(const string &nombre, int num_compromisarios) {
    // Completar
      if (estados.count(nombre)) {//si esta lanzamos error
          throw std::domain_error("Estado ya existente");
      }
      estados[nombre].compromisarios = num_compromisarios;
     
  }

  void sumar_votos(const string &estado, const string &partido, int num_votos) {
    // Completar
      infoEstado& info = bucar_estado(estado);
    
      if (info.partidos.count(partido)) {
          info.partidos[partido] += num_votos;
         

      }
      else {
          info.partidos[partido] = num_votos;
      }
      //Actualizamos el ganador
      if (info.partidos[partido] > info.ganador.second) {

          if (resultado.count(info.ganador.first)) {
              resultado[info.ganador.first] -= info.compromisarios;
              if (resultado[info.ganador.first] == 0) {
                  resultado.erase(info.ganador.first);
              }
          }

          info.ganador.first = partido;
          info.ganador.second = info.partidos[partido];

          //
          if (resultado.count(info.ganador.first)) {
              resultado[info.ganador.first] += info.compromisarios;
          }
          else {
              resultado[info.ganador.first] = info.compromisarios;

          }
      }
     
  }

  string ganador_en(const string &estado) const {
    // Completar
    const infoEstado& info = bucar_estado(estado);
    return info.ganador.first;
  }

  vector<pair<string,int>> resultados() const {
    // Completar

      vector<pair<string, int>> result;

      
      for (const auto& [k, v] : resultado) {
          pair<string, int> aux;
          aux.first = k;
          aux.second = v;
          result.push_back(aux);
      }
      return result;
  }

private:
  // Completar
    struct infoEstado {
        int compromisarios;
        pair<string, int> ganador; // nombre partido votos

        map<string, int> partidos; // clave: nombre partido, valor el numVotos

        infoEstado() : compromisarios(0),ganador("",0) {}
    };
 
    unordered_map<string, infoEstado> estados;

    map<string, int> resultado;


    infoEstado& bucar_estado(string const& estado) {
        auto it_estado = estados.find(estado);
        if (it_estado == estados.end()) {
            throw std::domain_error("Estado no encontrado");
        }

        return it_estado->second;
    }
    const infoEstado& bucar_estado(string const& estado) const{
        auto it_estado = estados.find(estado);
        if (it_estado == estados.end()) {
            throw std::domain_error("Estado no encontrado");
        }

        return it_estado->second;
    }
};


bool tratar_caso() {
  // Completar
    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    string estado, partido;
    int compromisario, numVotos;

    ConteoVotos conteo;


    while (operacion != "FIN") {
        try
        {
            if (operacion == "nuevo_estado") {
                cin >> estado >> compromisario;
                conteo.nuevo_estado(estado, compromisario);
            }
            else if (operacion == "sumar_votos") {
                cin >> estado >> partido >> numVotos;
                conteo.sumar_votos(estado, partido, numVotos);

            }
            else if (operacion == "ganador_en") {
                cin >> estado;
                string ganador = conteo.ganador_en(estado);
                cout << "Ganador en " + estado + ": " + ganador << endl;

            }
            else if (operacion == "resultados") {
                vector<pair<string, int>> result = conteo.resultados();
                for (int i = 0; i < (int)result.size(); i++) {
                    cout << result[i].first << " " << result[i].second << endl;
                }
            }
        }
        catch (const std::exception& e)
        {
            cout << e.what() << endl;
        }
        cin >> operacion;
    }
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
