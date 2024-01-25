#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

typedef pair<int, int> Pos;
typedef vector<vector<int>> Tauler;
typedef pair<int, Pos> pesVertex;

const vector<Pos> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
const int infinit = INT_MAX;

bool pos_ok(int& i, int& j, int& n){
    return (i >= 0 and i < n and j >= 0 and j < n);
}

bool es_vora(int& i, int& j, int& n){
    return (i == 0 or i == n-1 or j == 0 or j == n-1);
}

int cami_minim(Tauler& t){
    int n = t.size();
    vector<vector<bool>> visit(n, vector<bool>(n, false));
    vector<vector<int>> dist(n, vector<int>(n, infinit));
    priority_queue<pesVertex, vector<pesVertex>, greater<pesVertex>> PQ;

    int i = n/2;
    int j = n/2;
    visit[i][j] = true;
    dist[i][j] = t[i][j];

    PQ.push({dist[i][j],{i, j}});
    while(not PQ.empty()){
        int io = PQ.top().second.first;
        int jo = PQ.top().second.second;
        PQ.pop();
        if (es_vora(io, jo, n)) return dist[io][jo];
        

        for (auto d : dirs){
            int ni = io + d.first;
            int nj = jo + d.second;

            if (pos_ok(ni, nj, n)){
                visit[ni][nj] = true;
                if (dist[ni][nj] > dist[io][jo] + t[ni][nj]){
                    dist[ni][nj] = dist[io][jo] + t[ni][nj];
                    PQ.push({dist[ni][nj],{ni, nj}});
                }
            }
        }
    }
    return -1;
}

int main(){
    int n; 
    while (cin >> n){
        Tauler t(n, vector<int>(n));
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) cin >> t[i][j];
        }
        cout << cami_minim(t) << endl;
    }
}