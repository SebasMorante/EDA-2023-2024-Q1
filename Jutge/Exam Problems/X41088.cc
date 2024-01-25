#include <iostream>
#include <vector>
using namespace std;

bool seq_ok(int& left, int& mid, int& right){
    return left+right <= 2*mid;
}

void mostra_sol(vector<int>& sol){
    bool first = true;
    cout << "(";
    for (int i = 0; i < int(sol.size()); ++i){
        if (first) first = false;
        else cout << ",";
        cout << sol[i];
    }
    cout << ")" << endl;
}

void seq_sense_pous(int i, int total, vector<bool>& used, int n, vector<int>& sol){
    if (i == n) mostra_sol(sol);
    else {
        for (int j = 1; j <= n; ++j){
            if (not used[j]){
                if (sol.size() <= 1 or seq_ok(sol[sol.size()-2], sol.back(), j)){
                    sol.push_back(j);
                    used[j] = true;
                    seq_sense_pous(i+1, total+j, used, n, sol);
                    used[j] = false;
                    sol.pop_back();
                }
            }
        }

    }
}


int main(){
    int n;
    cin >> n;
    vector<int> sol;
    vector<bool> used(n+1, false);
    seq_sense_pous(0, 0, used, n, sol);
}