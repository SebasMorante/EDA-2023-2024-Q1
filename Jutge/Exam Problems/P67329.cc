#include <iostream>
#include <vector>
using namespace std;

void crea_sol(int i, string& adn, string& sol){
    if (i == sol.size()) cout << sol << endl;
    else{
        for (int j = 0; j < adn.size(); ++j){
        sol[i] = adn[j];
        crea_sol(i+1, adn, sol);
    }
    }
}

int main(){
    int n;
    cin >> n;
    string adn = "ACGT";
    string sol(n,' ');
    crea_sol(0, adn, sol);
}