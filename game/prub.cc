#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Mat;

struct Pos{
    int i;
    int j;
};

const vector<Pos> dirs = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{0,0}};



bool pos_ok_bfs(Pos& op, int n, Pos& np){
    return (np.i >= op.i-n and np.i <= op.i+n and np.j >= op.j-n and np.j <= op.j+n);
}

bool pos_ok(Pos& p, int& f, int& c){ 
    return (p.i >= 0 and p.i < f and p.j >= 0 and p.j < c);
}

  bool bfs_perill(Mat& m, Pos& p, int r, char c){
    int nf = m.size();
    int nc = m[0].size();
    vector<vector<bool>> visitat(nf, vector<bool>(nc, false));
    queue<Pos> Q;

    Pos orig = p;
    Q.push(orig);
    //visitat[orig.i][orig.j] = true; 

    while(not Q.empty()){
      Pos np = Q.front();
      Q.pop();

      for (auto d : dirs){
        Pos aux;
        aux.i = np.i+d.i;
        aux.j = np.j+d.j;
        // miramos que aux este en el tablero y que el BFS no vaya más alla de donde queremos
        // que aux no sea una roca, y que la casilla ya no este vistada
        if (pos_ok(aux, nf, nc) and pos_ok_bfs(orig, r, aux) and m[aux.i][aux.j] != 'R' and not visitat[aux.i][aux.j]){
            if (m[aux.i][aux.j] == c) return true;
            else {
            Q.push(aux);
            visitat[aux.i][aux.j] = true;
            }
        }
      }
    }
    return false;
  }

  int main(){
    int f, c;
    cin >> f >> c;
    Mat m(f, vector<char>(c));
    for (int i = 0; i < f; ++i){
        for (int j = 0; j < c; ++j) cin >> m[i][j];
    }
    Pos p;
    char ca;
    int r;
    cin >> p.i >> p.j >> r >> ca;

    if (bfs_perill(m, p, r, ca)) cout << "CARACTER ENCONTRADO" << endl;
    else cout << "NO ENCONTRADO" << endl;
  }