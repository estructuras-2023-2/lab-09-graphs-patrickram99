#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

class UnionFind {
private:
  unordered_map<string, string> padre;
  unordered_map<string, int> rango;

public:
  void hacerConjunto(const string& elemento) {
    padre[elemento] = elemento;
    rango[elemento] = 0;
  }

  string encontrar(const string& elemento) {
    if (padre[elemento] != elemento)
      padre[elemento] = encontrar(padre[elemento]);
    return padre[elemento];
  }

  bool unirConjuntos(const string& a, const string& b) {
    string raizA = encontrar(a);
    string raizB = encontrar(b);

    if (raizA == raizB) {
      return false;
    }

    if (rango[raizA] < rango[raizB]) {
      padre[raizA] = raizB;
    } else if (rango[raizA] > rango[raizB]) {
      padre[raizB] = raizA;
    } else {
      padre[raizB] = raizA;
      rango[raizA]++;
    }

    return true;
  }
};

struct Carretera {
  string id;
  string ciudad1;
  string ciudad2;
  int costo;

  Carretera(string i, string c1, string c2, int co = 0) : id(i), ciudad1(c1), ciudad2(c2), costo(co) {}
};

vector<string> split(const string& str, char delimiter) {
  vector<string> result;
  size_t start = 0;
  size_t end = str.find(delimiter);
  while (end != string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }
  result.push_back(str.substr(start));
  return result;
}

string reconstruye(vector<string> listaCarreteras) {
  vector<Carretera> carreterasDeterioradas;
  UnionFind uf;
  set<string> raices; // Conjunto de raíces de conjuntos

  for (const auto& carreteraStr : listaCarreteras) {
    auto elementos = split(carreteraStr, ' ');
    string id = elementos[0];
    string ciudad1 = elementos[1];
    string ciudad2 = elementos[2];

    uf.hacerConjunto(ciudad1);
    uf.hacerConjunto(ciudad2);
    raices.insert(uf.encontrar(ciudad1));
    raices.insert(uf.encontrar(ciudad2));
  }

  for (const auto& carreteraStr : listaCarreteras) {
    auto elementos = split(carreteraStr, ' ');
    string id = elementos[0];
    string ciudad1 = elementos[1];
    string ciudad2 = elementos[2];
    int costo = (elementos.size() > 3) ? stoi(elementos[3]) : 0;

    if (costo == 0) {
      uf.unirConjuntos(ciudad1, ciudad2);
    } else {
      carreterasDeterioradas.emplace_back(id, ciudad1, ciudad2, costo);
    }
  }

  sort(carreterasDeterioradas.begin(), carreterasDeterioradas.end(), [](const Carretera& a, const Carretera& b) {
    if (a.costo != b.costo) {
      return a.costo < b.costo;
    }
    return a.id < b.id;
  });

  set<string> carreterasSeleccionadas;

  for (const auto& carretera : carreterasDeterioradas) {
    if (uf.encontrar(carretera.ciudad1) != uf.encontrar(carretera.ciudad2)) {
      uf.unirConjuntos(carretera.ciudad1, carretera.ciudad2);
      carreterasSeleccionadas.insert(carretera.id);
    }
  }

  if (raices.size() == 1) {
    string resultado;
    for (const auto& id : carreterasSeleccionadas) {
      resultado += id + " ";
    }
    return resultado.empty() ? "" : resultado.substr(0, resultado.length() - 1);
  } else {
    return "IMPOSIBLE";
  }
}
