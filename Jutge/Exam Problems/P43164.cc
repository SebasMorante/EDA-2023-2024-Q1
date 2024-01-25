#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Tauler;
typedef pair<int, int> Pos;
const vector<Pos> dirs = {{0,-1},{1,0},{0,1},{-1,0}};

bool pos_ok(int& i, int& j, int& n, int& m){
    return (i >= 0 and i < n and j >= 0 and j < m);
}

int cerca_tresor(Pos& po, Tauler& t){
    int n = t.size();
    int m = t[0].size();
    vector<vector<bool>> visit(n, vector<bool>(m));
    vector<vector<int>> dist(n, vector<int>(m, 0));
    queue<Pos> Q;

    int pd = -1;     //penúltima distancia
    int ld = -1;    //última distancia

    int i = po.first;
    int j = po.second;

    visit[i][j] = true;
    Q.push(po);

    while (not Q.empty()){
        int poi = Q.front().first;
        int poj = Q.front().second;
        Q.pop();

        for (auto np : dirs){
            int ni = poi+np.first;
            int nj = poj+np.second;

            if (pos_ok(ni, nj, n, m) and not visit[ni][nj] and t[ni][nj] != 'X'){
                visit[ni][nj] = true;
                dist[ni][nj] = dist[poi][poj] + 1;
                if (t[ni][nj] == 't'){
                    pd = ld;
                    ld = dist[ni][nj];
                }
                Q.push({ni, nj});
            }
        }
    }
    return pd;
}


int main(){
    int n, m;
    cin >> n >> m;
    Tauler t(n, vector<char>(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> t[i][j];
    }
    int io, jo;
    cin >> io >> jo;
    Pos po = {(io-1),(jo-1)};
    int r = cerca_tresor(po, t);
    if (r == -1) cout << "no es pot arribar a dos o mes tresors" << endl;
    else cout << "segona distancia maxima: " << r << endl;

}