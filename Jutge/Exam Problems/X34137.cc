#include <iostream>
#include <vector>
using namespace std;

void dfs(int u, const vector<vector<int>>& g, vector<int>& vis) { 
    if (vis[u]) return; 
    vis[u] = true;
    for (int v : g[u]) dfs(v, g, vis);
}

int main() {
    int n, u, v, m;
    while (cin >> n >> u >> v >> m) {
        vector<vector<int>> g(n); 
        vector<vector<int>> i(n); // Inverted graph (flipped edges) while (m−−)

        while(m--){
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            i[y].push_back(x);
        }

        vector<int> fwd(n, false);
        dfs(u, g, fwd);
        
        if (not fwd[v]) cout << 0 << endl;
        else {

            vector<int> bwd(n, false);
            dfs(v, i, bwd);
            int sum = 0;

            for (int x = 0; x < n; ++x) {
                sum += (fwd[x] and bwd[x]);
            }
            cout << sum - 2 << endl;
        }
    }
}