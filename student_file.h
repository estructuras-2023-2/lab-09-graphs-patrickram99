#include <bits/stdc++.h>
using namespace std;

struct Edge {
    string id, u, v;
    int cost;
    bool operator<(const Edge& rhs) const {
        if(cost != rhs.cost) return cost < rhs.cost;
        return id < rhs.id;
    }
};

string find(map<string, string>& parent, string i) {
    if(parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void Union(map<string, string>& parent, string x, string y) {
    string xset = find(parent, x);
    string yset = find(parent, y);
    parent[xset] = yset;
}

string solve(vector<string> roads) {
    vector<Edge> edges;
    map<string, string> parent;
    for(string road : roads) {
        stringstream ss(road);
        string id, u, v;
        int cost = INT_MAX;
        ss >> id >> u >> v;
        if(ss >> cost);
        else continue; // Skip the road if it's not damaged
        edges.push_back({id, u, v, cost});
        parent[u] = u;
        parent[v] = v;
    }
    sort(edges.begin(), edges.end());
    vector<string> res;
    int totalCost = 0;
    for(Edge e : edges) {
        string x = find(parent, e.u);
        string y = find(parent, e.v);
        if (x != y) {
            res.push_back(e.id);
            totalCost += e.cost;
            Union(parent, x, y);
        }
    }
    for(auto it = parent.begin(); it != parent.end(); it++)
        if(find(parent, it->first) != find(parent, parent.begin()->first))
            return "IMPOSIBLE";
    sort(res.begin(), res.end());
    string result = "";
    for(string id : res) result += id + " ";
    return result.substr(0, result.size()-1);
}

int main() {
    vector<string> roads = {"T1 Tumbes Quito", "C1 Iquitos StMartin 1000"};
    cout << solve(roads) << endl;
    return 0;
}
