#include <iostream>
#include <vector>
using namespace std;

const string ll = "xyz";

bool no_seq_ant(int i, char cll, string& sol, int& n, int& c){
    if (i < c) return true;
    else if ((i - c >= 0) and sol[i-c] != cll) return true;
    else{
        bool found = false;
        int j = 1;
        while (j <= c and (i - j > 0) and not found){
            if (sol[i-j] != cll) found = true;
            ++j;
        }
        return found;
    }
}


void crea_com(int i, string& sol, int& n, int& c){
    if (i == n) cout << sol << endl;
    else{
        if ((i == 0) or (c >= n)){
            for (int j = 0; j < ll.size(); ++j){
                sol[i] = ll[j];
                crea_com(i+1, sol, n, c);
            }
        }
        else{
            // i es mas grande que 0 and c < n
            for (int j = 0; j < ll.size(); ++j){
                if ((sol[i-1] != ll[j])){
                    sol[i] = ll[j];
                    crea_com(i+1, sol, n, c);
                }
                else{
                    if (no_seq_ant(i, ll[j], sol, n, c)){
                        sol[i] = ll[j];
                        crea_com(i+1, sol, n, c);
                    }
                }
            }

        }
    }
}

int main(){
    int n, c;
    while(cin >> n >> c){
        string sol(n, ' ');
        crea_com(0, sol, n, c);
        cout << string(20, '-') << endl;
    }
}