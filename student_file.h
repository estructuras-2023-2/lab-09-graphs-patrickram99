// union_find.h
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
private:
  map<string, string> padre;
  map<string, int> rango;

public:
  // Inicializa un conjunto con un elemento.
  void hacerConjunto(const string& elemento) {
    padre[elemento] = elemento;
    rango[elemento] = 0;
  }

  // Encuentra el representante del conjunto al que pertenece el elemento.
  string encontrar(const string& elemento) {
    if (padre[elemento] != elemento)
      padre[elemento] = encontrar(padre[elemento]);
    return padre[elemento];
  }

  // Une dos conjuntos, devuelve true si los conjuntos eran diferentes y se unieron.
  bool unirConjuntos(const string& a, const string& b) {
    string raizA = encontrar(a);
    string raizB = encontrar(b);

    if (raizA == raizB)
      return false;

    if (rango[raizA] < rango[raizB])
      padre[raizA] = raizB;
    else if (rango[raizA] > rango[raizB])
      padre[raizB] = raizA;
    else {
      padre[raizB] = raizA;
      rango[raizA]++;
    }

    return true;
  }
};

class Carretera {
public:
  string id;
  string ciudad1;
  string ciudad2;
  int costo;

  Carretera(string i, string c1, string c2, int co = 0) : id(i), ciudad1(c1), ciudad2(c2), costo(co) {}
};

// Reconstruye y devuelve la lista de carreteras seleccionadas.
string reconstruye(vector<string> listaCarreteras) {
  vector<Carretera> carreterasDeterioradas;
  UnionFind uf;
  set<string> ciudades;
  set<string> carreterasSeleccionadas;

  // Inicializa conjuntos para cada ciudad.
  for (const auto& carreteraStr : listaCarreteras) {
    stringstream ss(carreteraStr);
    string id, ciudad1, ciudad2;
    ss >> id >> ciudad1 >> ciudad2;
    uf.hacerConjunto(ciudad1);
    uf.hacerConjunto(ciudad2);
    ciudades.insert(ciudad1);
    ciudades.insert(ciudad2);
  }

  // Clasifica carreteras según su estado.
  for (const auto& carreteraStr : listaCarreteras) {
    stringstream ss(carreteraStr);
    string id, ciudad1, ciudad2;
    int costo = 0;
    ss >> id >> ciudad1 >> ciudad2;
    if (!(ss >> costo)) {
      uf.unirConjuntos(ciudad1, ciudad2);
    } else {
      carreterasDeterioradas.emplace_back(id, ciudad1, ciudad2, costo);
    }
  }

  // Ordena carreteras deterioradas por costo.
  sort(carreterasDeterioradas.begin(), carreterasDeterioradas.end(), [](const Carretera& a, const Carretera& b) {
    if (a.costo != b.costo) {
      return a.costo < b.costo;
    }
    return a.id < b.id;
  });

  // Selecciona carreteras que conectan ciudades diferentes.
  for (const auto& carretera : carreterasDeterioradas) {
    if (uf.encontrar(carretera.ciudad1) != uf.encontrar(carretera.ciudad2)) {
      uf.unirConjuntos(carretera.ciudad1, carretera.ciudad2);
      carreterasSeleccionadas.insert(carretera.id);
    }
  }

  // Verifica que todas las ciudades estén conectadas.
  string raiz = uf.encontrar(*ciudades.begin());
  for (const auto& ciudad : ciudades) {
    if (uf.encontrar(ciudad) != raiz) {
      return "IMPOSIBLE";
    }
  }

  // Construye el resultado.
  string resultado;
  for (const auto& id : carreterasSeleccionadas) {
    resultado += id + " ";
  }

  return resultado.empty() ? "" : resultado.substr(0, resultado.length() - 1);
}
