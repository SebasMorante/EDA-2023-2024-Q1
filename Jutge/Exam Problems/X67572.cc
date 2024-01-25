#include <iostream>
#include <vector>
using namespace std;

void crea_sol(int i, int& n, vector<bool>& used, vector<string>& sol, vector<string>& p){
    if (i == n){
        for (int j = 0; j < n; ++j){
            cout << sol[j];
        }
        cout << endl;
    }
    else {
        for (int j = 0; j < n; ++j){
            if (i > 0){
                int lws = sol[i-1].size();
                if (not used[j] and sol[i-1][lws-1] != p[j][0]){
                    sol[i] = p[j];
                    used[j] = true;
                    crea_sol(i+1, n, used, sol, p);
                    used[j] = false;
                }
            }
            else{
                if (not used[j]){
                    sol[i] = p[j];
                    used[j] = true;
                    crea_sol(i+1, n, used, sol, p);
                    used[j] = false;
                }
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<string> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    vector<string> sol(n);
    vector<bool> used(n, false);
    crea_sol(0, n, used, sol, p);
}