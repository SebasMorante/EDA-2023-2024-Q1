#include <iostream>
#include <vector>
using namespace std;


int to_int(int i, string& sol){
    int fact = 1;
    int sum = 0;
    for (int j = i; j >= 0; --j){
        sum += (sol[j]-'0')*fact;
        fact *= 10;
    }
    return sum;
}

bool es_divisible(int i, string& sol, vector<int>& div){
    int v = to_int(i, sol);
    for (auto d : div){
        if (v%d == 0) return true;
    }
    return false;
}

void crea_sol(int i, int& n, vector<int>& div, string& sol){
    if (i == n) cout << sol << endl;
    else{
        for (int j = 0; j <= 9; ++j){
            if ((i == 0 and j != 0) or i > 0){
                sol[i] = char(j+'0');
                if (not es_divisible(i, sol, div)) crea_sol(i+1, n, div, sol);
            }
        }
    }
}


int main(){
    int n, m;
    while (cin >> n >> m){
        vector<int> div(m);
        string sol(n, ' ');
        for (int i = 0; i < m; ++i) cin >> div[i];
        crea_sol(0, n, div, sol);
        cout << string(10,'-') << endl;
    }
}