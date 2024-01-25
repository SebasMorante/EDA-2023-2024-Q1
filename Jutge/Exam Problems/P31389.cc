#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Tauler;

void torres(int i, vector<bool> col, int& f, int& c, Tauler& t){
    if (i == f){
        for(int i = 0; i < f; ++i){
            for (int j = 0; j < c; ++j){
                cout << t[i][j];
            }
            cout << endl;
        }
        cout << endl;        
    }
    else{
        for (int j = 0; j < c; ++j){
            if (not col[j]){
                t[i][j] = 'R';
                col[j] = true;
                torres(i+1, col, f, c, t);
                t[i][j] = '.';
                col[j] = false;
            }
        }
    }
}

int main(){
    int f, c;
    cin >> f >> c;
    vector<bool> v(c, false);
    Tauler t(f, vector<char>(c, '.'));
    torres(0, v, f, c, t);
}