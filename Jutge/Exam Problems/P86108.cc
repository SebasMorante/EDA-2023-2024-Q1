#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Tablero;

void calcula_next(int& ni, int& nj, int& n, int& m){
    if( nj < m){
        ++nj;
        if (nj == m){
            nj = 0;
            ++ni;
        }
    }
}

int calcula_lols(int i, int j, int num, Tablero& t, int& n, int& m){
    if (i == n) return num;
    int ni = i;
    int nj = j;
    calcula_next(ni, nj, n, m);

    //Soluciones si colo 'O' en la pos t[i][j]
    t[i][j] = 'O';
    int num_auxO = 0;

    int num_o = calcula_lols(ni, nj, num_auxO+num, t, n, m);

    //soluciones si coloco 'L' en pos t[i][j]
    t[i][j] = 'L';
    int num_auxL = 0;

    // mirar si hay lol en horizontal
    if (j >= 2 and t[i][j-2] == 'L' and t[i][j-1] == 'O') ++num_auxL;

    // mirar si hay en vertical
    if (i >= 2 and t[i-2][j] == 'L' and t[i-1][j] == 'O') ++num_auxL;

    //mirar diagonal izquierda
    if (i >= 2 and j>= 2 and t[i-2][j-2] == 'L' and t[i-1][j-1] == 'O') ++num_auxL;

    //mirar diagonal derecha
    if (i >= 2 and j+2 < m and t[i-1][j+1] == 'O' and t[i-2][j+2] == 'L') ++num_auxL;

    int num_l = calcula_lols(ni, nj, num_auxL+num, t, n, m);    

    return max(num_o, num_l);
}


int main(){
    int n, m;
    while(cin >> n >> m){
        Tablero t(n, vector<char>(m));
        cout << calcula_lols(0, 0, 0, t, n, m) << endl;

    }
}