#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

typedef pair<int, int> Arc;
typedef vector<vector<Arc>> Graf;

const int infinit = INT_MAX;

int carre_curtes(const Graf& G, int ini, int fin){
    int n = G.size();
    vector<int> dist(n, infinit);
    vector<bool> vis(n, false);
    priority_queue<Arc, vector<Arc>, greater<Arc>> PQ;

    PQ.push({0, ini});
    dist[ini] = 0;

    while(not PQ.empty()){
        int u = PQ.top().second;
        PQ.pop();
        // En dijkstra siempre se para si sale de la cola
        if(u == fin) return dist[u];
        //
        if (not vis[u]){
            vis[u] = true;
            for (Arc uv : G[u]){
                int v = uv.second;
                int c = uv.first;
                int d_max = max(c, dist[u]);
                if(d_max < dist[v]){
                    dist[v] = d_max;
                    PQ.push({d_max, v});
                }
            }
        }
    }
    return infinit;
}

int main(){
    int n, m;
    while (cin >> n >> m){
        Graf G(n);
        for (int i = 0; i < m; ++i){
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({c, y});
        }
        cout << carre_curtes(G, 0, 1) << endl; // 0 punto inicial, 1 punto final
    }
}