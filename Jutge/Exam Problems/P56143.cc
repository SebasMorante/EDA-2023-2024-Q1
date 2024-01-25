#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Tauler;
typedef pair<int, int> Pos;

const vector<Pos> dirs = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};


bool pos_ok(int& i, int& j, int& n, int& m){
    return i >= 0 and i < n and j >= 0 and j < m;
}

vector<Pos> cerca_pages(Pos& cab, int& n, int& m, Tauler& t){
   vector<vector<bool>> visit(n, vector<bool>(m, false));
   vector<vector<Pos>> prev(n, vector<Pos>(m));
   queue<Pos> Q;
   vector<Pos> cami;

   visit[cab.first][cab.second] = true;
   Q.push(cab);

   while(not Q.empty()){
       int io = Q.front().first;
       int jo = Q.front().second;
       Q.pop();

       for (auto d : dirs){
           int ni = io + d.first;
           int nj = jo + d.second;

           if (pos_ok(ni, nj, n, m) and t[ni][nj] != 'X' and not visit[ni][nj]){
               visit[ni][nj] = true;
               prev[ni][nj] = {io,jo};
               if (t[ni][nj] == 'F'){
                   //he trobat el pages retorno el cami
                    Pos aux = {ni,nj};
                    cami.push_back(aux);
                    while(aux != cab){
                        cami.push_back(prev[aux.first][aux.second]);
                        aux = prev[aux.first][aux.second];
                    }
                    return cami;
               }
               Q.push({ni,nj});
           }
       }
   }
   return cami;
}

void mostra_sol(vector<Pos>& cami){
    if (cami.size() == 0) cout << "0" << endl;
    else{
        int mc = cami.size();
        cout << mc << "  ";
        for (int i = mc-1; i >= 0; --i){
            if (i != mc-1) cout << "  ";
            cout << cami[i].first << " " << cami[i].second;
        }
        cout << endl;
    }
}


int main(){
    int n, m;
    while (cin >> n >> m){
        Tauler t(n, vector<char>(m));
        vector<Pos> cami;
        Pos cab;

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                cin >> t[i][j];
                if (t[i][j] == 'K'){
                    cab.first = i;
                    cab.second = j;
                }
            }
        }
        cami = cerca_pages(cab, n, m, t);
        mostra_sol(cami);
    }
}