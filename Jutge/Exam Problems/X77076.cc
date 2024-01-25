#include <iostream>
#include <vector>
using namespace std;

int cerca(double& x, const vector<double>& v, int izq, int der){
    if (izq > der) return -1;
    int m = (izq+der)/2;
    if (v[m] < x){
        if (m > 0 and v[m-1] == x) return m-1;
        else return cerca(x, v, m+1, der);
    }
    else {  // v[m] >= x
        int p = cerca(x, v, izq, m-1);
        if (p == -1){   // no lo hemos encontrado por la izquierda
            if (v[m] == x) return m;
              else if(m+1 < v.size() and v[m+1] == x) return m+1;
        }
        return p;
    }
}

int first_occurrence(double x, const vector<double>& v){
    return cerca(x, v, 0, v.size()-1);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << first_occurrence(x, V) << endl;
        }
    }
}