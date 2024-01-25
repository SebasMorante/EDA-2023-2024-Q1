#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> ArcP; // <peso,v.adjacente>
typedef vector<vector<ArcP>> GrafP;

int prim(const GrafP& G, int& n){
    priority_queue<ArcP, vector<ArcP>, greater<ArcP>> CP;
    vector<bool> visto(n, false);
    visto[0] = true;

    for (ArcP uv: G[0]) CP.push(uv);
    int c = 1;  // vertices visitados
    int suma = 0;  // suma minima de pesos

    while(c != n){
        int coste = CP.top().first;
        int v = CP.top().second;
        CP.pop();
        if (not visto[v]){
            visto[v] = true;
            suma += coste;
            ++c;

            for (ArcP vu: G[v]) CP.push(vu);
        }
    }
    return suma;
}

int main(){
    int n, m;
    while(cin >> n >> m){
        int x, y, p;
        GrafP G(n);
        int total = 0;

        for (int i = 0; i < m; ++i){
            cin >> x >> y >> p;
            G[x].push_back({p, y});
            G[y].push_back({p,x});
            total += p;
        }
        cout << total - prim(G, n) << endl;
    }
}