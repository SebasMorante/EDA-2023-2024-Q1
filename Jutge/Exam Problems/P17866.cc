#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Tauler;
typedef pair<int, int> Pos;
const vector<Pos> dirs = {{1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2,1}, {-1,2}};

bool pos_ok(int& i, int& j, int& f, int& c){
    return (i >= 0 and i < f and j >= 0 and j < c);
}

int cerca_past(int i, int j, Tauler& T){
    int n = T.size();
    int m = T[0].size();
    vector<vector<bool>> visit(n, vector<bool>(m, false));
    vector<vector<int>> dist(n, vector<int>(m, 0));
    queue<Pos> Q;

    Q.push({i,j});
    visit[i][j] = true;

    while (not Q.empty()){
        int io = Q.front().first;
        int jo = Q.front().second;
        Q.pop();

        for (auto d : dirs){
            int ni = io+ d.first;
            int nj = jo + d.second;
            if (pos_ok(ni, nj, n, m) and not visit[ni][nj] and T[ni][nj] != 'X'){
                dist[ni][nj] = dist[io][jo] + 1;
                visit[ni][nj] = true;
                if (T[ni][nj] == 'p') return dist[ni][nj];
                Q.push({ni,nj});
            }
        }
    }
    return -1;

}

int main(){
    int f, c;
    while(cin >> f >> c){
        Tauler T(f, vector<char>(c));
        for (int i = 0; i < f; ++i){
            for (int j = 0; j < c; ++j) cin >> T[i][j];
        }
        int io, jo;
        cin >> io >> jo;
        int r = cerca_past(io-1, jo-1, T);
        if (r != -1) cout << r << endl;
        else cout << "no" << endl;

    }





}