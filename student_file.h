#include <bits/stdc++.h>
using namespace std;

struct edge {
    string id;
    int u, v, cost;
    bool operator<(const edge& e) const {
        if(cost != e.cost) return cost < e.cost;
        return id < e.id;
    }
};

vector<int> parent;
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

vector<string> reconstructRoads(vector<string> roads) {
    map<string, int> city_to_int;
    vector<edge> edges;
    int city_counter = 0;
    for(string road : roads) {
        stringstream ss(road);
        string id, city1, city2;
        int cost = -1;
        ss >> id >> city1 >> city2;
        if(ss >> cost) {
            if(city_to_int.find(city1) == city_to_int.end()) city_to_int[city1] = city_counter++;
            if(city_to_int.find(city2) == city_to_int.end()) city_to_int[city2] = city_counter++;
            edges.push_back({id, city_to_int[city1], city_to_int[city2], cost});
        }
    }
    sort(edges.begin(), edges.end());
    parent.resize(city_counter);
    for(int i = 0; i < city_counter; i++) make_set(i);
    vector<string> result;
    for(auto e : edges) {
        if(find_set(e.u) != find_set(e.v)) {
            result.push_back(e.id);
            union_sets(e.u, e.v);
        }
    }
    for(int i = 1; i < city_counter; i++) {
        if(find_set(i) != find_set(0)) {
            result.clear();
            result.push_back("IMPOSIBLE");
            break;
        }
    }
    return result;
}

int main() {
    vector<string> roads = {"C1 Lima Trujillo 1", "C2 Tacna Trujillo", "C3 Tacna Arequipa"};
    vector<string> result = reconstructRoads(roads);
    for(string id : result) cout << id << " ";
    cout << endl;
    return 0;
    
}