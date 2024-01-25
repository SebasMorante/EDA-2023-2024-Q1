#include <iostream>
#include <map>
using namespace std;


int main() {
  map<string, int> M;
  char c;
  while (cin >> c) {
    if (c == 'N') {
      cout << "number: " << M.size() << endl;
    }
    else if (c == 'D') {
      string nif;
      int money;
      cin >> nif >> money;
      auto it = M.find(nif);
      if (it != M.end()){
        M[nif] += money;
      }
      else M[nif] = money;
    }
    else if (c == 'Q') {
      string nif;
      cin >> nif;
      auto it = M.find(nif);
      if (it != M.end()){
        cout << M[nif] << endl;
      }
      else cout << -1 << endl;
    }
    else if (c == 'P') {
        bool first = true;
      for (auto it = M.begin(); it != M.end(); ++it){
        int n = int(it->first[7]-48);
        if (n%2 == 0){
            if (not first) cout << " ";
            else first = false;
            cout << it->first;
        }
      }
      cout << endl;
    }
    else { // c == 'L'
      if (M.size() > 0){
        auto it = M.end();
        --it;
        cout << it->first << " " << it->second << endl;
      }
      else cout << "NO LAST NIF" << endl;
    }
  }
}