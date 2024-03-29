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
    /*
          E -> numero de estados

          P -> resultados, num Partidos distintos entre todos los estados
    */ 

  //coste:  O(1)
  void nuevo_estado(const string &nombre, int num_compromisarios) {
    // Completar
      if (estados.count(nombre)) {//si esta lanzamos error O(1)
          throw std::domain_error("Estado ya existente");
      }
      estados[nombre].compromisarios = num_compromisarios; // O(1)
     
  }

  //coste: O(log P)
  void sumar_votos(const string &estado, const string &partido, int num_votos) {
    // Completar
      infoEstado& info = bucar_estado(estado); //O(1)
    
      if (info.partidos.count(partido)) { // O(log P)
          info.partidos[partido] += num_votos; // O(log P)
      }
      else {
          info.partidos[partido] = num_votos; // O(log P)
      }
      //Actualizamos el ganador
      if (info.partidos[partido] > info.ganador.second) {

          if (resultado.count(info.ganador.first)) { // O(log P)
              resultado[info.ganador.first] -= info.compromisarios; // O(log P)
              if (resultado[info.ganador.first] == 0) { // O(log P)
                  resultado.erase(info.ganador.first); // O(log P)
              }
          }

          info.ganador.first = partido;
          info.ganador.second = info.partidos[partido];

          // 
          if (resultado.count(info.ganador.first)) { // O(log P)
              resultado[info.ganador.first] += info.compromisarios; // O(log P)
          }
          else {
              resultado[info.ganador.first] = info.compromisarios; // O(log P)

          }
      }
     
  }

  // coste O(1)
  string ganador_en(const string &estado) const {
    // Completar
    const infoEstado& info = bucar_estado(estado); // O(1)
    return info.ganador.first;
  }

  // coste: O(P)
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

    map<string, int> resultado; // recuentos de los votos 

    //coste:  O(1)
    infoEstado& bucar_estado(string const& estado) {
        auto it_estado = estados.find(estado);
        if (it_estado == estados.end()) {
            throw std::domain_error("Estado no encontrado");
        }

        return it_estado->second;
    }
    //coste: O(1)
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
