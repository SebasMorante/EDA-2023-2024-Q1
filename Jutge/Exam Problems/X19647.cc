#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

//<pes, VertAdj>
typedef pair<int,int> Arc;
typedef vector<vector<Arc>> Graf;
const int infinit = INT_MAX;

int dijkstra(int ini, int fi, vector<int>& cnit, Graf& G){
    int n = G.size();
    vector<bool> visit(n, false);
    vector<int> dist(n, infinit);
    priority_queue<Arc, vector<Arc>, greater<Arc>> PQ;

    dist[ini] = 0;
    PQ.push({0, ini});

    while (not PQ.empty()){
        int v = PQ.top().second;
        PQ.pop();

        if (v == fi) return dist[fi];

        if (not visit[v]){
            visit[v] = true;

            for (auto w : G[v]){
                int nv = w.second;
                int c = w.first;

                if (nv == fi){
                    if (dist[nv] > dist[v] + c){

                        dist[nv] = dist[v] + c;
                        PQ.push({dist[nv], nv});
                    }                    
                }
                else{
                    if (dist[nv] > dist[v] + cnit[nv] + c){

                        dist[nv] = dist[v]+cnit[nv]+c;
                        PQ.push({dist[nv], nv});
                    }
                } 

            }
        }
    }
    return infinit;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<int> cnit(n);
    for (int i = 0; i < n; ++i) cin >> cnit[i];
    Graf G(n);
    int u, v, c;
    for (int i = 0; i < m; ++i){
        cin >> u >> v >> c;
        G[u].push_back({c, v});
        G[v].push_back({c, u});
    }
    int A, B;
    while (cin >> A >> B){
        int r = dijkstra(A, B, cnit, G);
        if (r != infinit) cout << "c(" << A << "," << B << ") = " << r << endl;
        else cout << "c(" << A << "," << B << ") = +oo" << endl;
    }
}
