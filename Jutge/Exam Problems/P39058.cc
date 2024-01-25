#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Tauler;
typedef pair<int, int> Pos;
const vector<Pos> dirs = {{1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2,1}, {-1,2}};

bool pos_ok(int i, int j, int n, int m){
    return (i >= 0 and i < n and j >= 0 and j < m);
}

void cerca_flors(const Tauler& T, Pos& c, int n, int m){
    vector<vector<bool>> vist(n, vector<bool>(m, false));
    vector<vector<int>> dist(n, vector<int>(m, 0));    //distancia de la flor al cavall
    queue<Pos> Q;

    int nf = 0;
    double np = 0;

    int ci = c.first;
    int cj = c.second;
    vist[ci][cj] = true;

    Q.push({ci,cj});

    while (not Q.empty()){
        int poi = Q.front().first;
        int poj = Q.front().second;
        Q.pop();

        for (auto a : dirs){
            int ni = poi + a.first;
            int nj = poj + a.second;

            if (pos_ok(ni, nj, n, m) and not vist[ni][nj] and T[ni][nj] != 'a'){
                vist[ni][nj] =  true;
                dist[ni][nj] = dist[poi][poj] +1;
                if (T[ni][nj] == 'F'){
                    ++nf;
                    np += dist[ni][nj];
                }
                Q.push({ni,nj});
            }
        }

    }
    if (nf != 0){
        cout << "flors accessibles: " << nf << endl;
        cout << "distancia mitjana: " << np/nf << endl;
    }
    else cout << "el cavall no pot arribar a cap flor" << endl;
}




int main(){

    cout.setf(ios::fixed);
    cout.precision(4);

    int n, m;
    cin >> n >> m;

    Tauler t(n, vector<char>(m));
    Pos cav;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> t[i][j];
            if (t[i][j] == 'C'){
                cav = {i,j};
            }
        }
    }
    cerca_flors(t,cav,n,m);
}