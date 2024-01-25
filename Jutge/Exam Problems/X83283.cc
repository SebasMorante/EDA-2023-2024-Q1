#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> Graf;

int vertex_all(Graf& G){
    int n = G.size();
    vector<bool> visit(n, false);
    vector<int> dist(n, 0);
    queue<int> Q;

    int Vmax = 0;   //vertex més allunyat
    int Dmax = 0;   //distància al vertex més allunyat

    Q.push(0);
    visit[0] = true;

    while (not Q.empty()){
        int vo = Q.front();
        Q.pop();

        for (auto u : G[vo]){
            if (not visit[u]){

                dist[u] = dist[vo]+1;
                visit[u] = true;

                if (dist[u] > Dmax){
                    Vmax = u;
                    Dmax = dist[u];
                }
                else if (dist[u] == Dmax){
                    if (Vmax > u) Vmax = u;
                }
                Q.push(u);                
            }
        }
    }
    return Vmax;
}


int main(){
    int n, m;
    while (cin >> n >> m){
        Graf G(n);
        int x, y;
        for (int i = 0; i < m; ++i){
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        cout << vertex_all(G) << endl;
    }
}

