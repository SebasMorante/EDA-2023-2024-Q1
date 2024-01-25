#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool es_vocal(char c){
    return (c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u');
}

void crea_com(int i, string& sol, set<char>& ll, int n, int m){
    if (i == n) cout << sol << endl;
    else {
        for (set<char>::iterator it = ll.begin(); it != ll.end(); ++it){
            if (i == 0){
                sol[i] = *it;
                crea_com(i+1, sol, ll, n, m);
            }
            else {
                if (not es_vocal(sol[i-1]) or not es_vocal(*it)){
                    sol[i] = *it;
                    crea_com(i+1, sol, ll, n, m);
                }
            }
        }
    }
}

int main(){
    int n, m;
    while (cin >> n >> m){
        set<char> ll;
        string sol(n, ' ');
        char c;
        for (int i = 0; i < m; ++i){
            cin >> c;
            ll.insert(c);
        }
        crea_com(0, sol, ll, n, m);
        cout << string(10, '-') << endl;
    }
}
