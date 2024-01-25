#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

typedef vector<vector<int>> Graf;
const int infinit = INT_MAX;

void connec_comp(Graf& G){
    int min = infinit;
    int max = -1;
    int n = G.size();
    vector<bool> vist(n, false);
    queue<int> Q;

    //vamos a recorrer todos los vertices del grafo
    for (int i = 0; i < n; ++i){
        int numVert = 0;
        if (not vist[i]){
            Q.push(i);
            while(not Q.empty()){
                int v = Q.front();
                Q.pop();
                if (not vist[v]){
                    vist[v] = true;
                    ++numVert;
                    for (auto nv : G[v]){
                        if (not vist[nv]) Q.push(nv);
                    }                
                }
            }
            //hemos recorrido todos los vertices adjacentes a i
            if (numVert > max) max = numVert;
            if (numVert < min) min = numVert;
        }
    }
    cout << min << " " << max << endl;
}

int main(){
    int n, m;
    while(cin >> n >> m){
        Graf G(n);
        int x, y;
        for (int i = 0; i < m; ++i){
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        connec_comp(G);
    }
}


