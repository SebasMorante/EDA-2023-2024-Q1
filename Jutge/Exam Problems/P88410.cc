#include <iostream>
#include <vector>

using namespace std;

void rosers (int n, vector<int>& sol, int idx, vector<int>& comptador, bool hi_ha_consec) {
  if (idx == 3*n) {
    if (hi_ha_consec) {
      for (int x : sol) cout << x;
      cout << endl;
    }
  }
  else {
    for (int c = 1; c <= 3; ++c) {
      //      if (comptador[c] < n and aixo no em crea mes d'un parell consecutiu) {
      if (comptador[c] < n and (not hi_ha_consec or idx == 0 or sol[idx-1] != c)) {
	sol[idx] = c;
	++comptador[c];
	rosers(n,sol,idx+1,comptador,hi_ha_consec or (idx > 0 and sol[idx-1] == c));
	--comptador[c];
      }
    }
  }
}

void rosers (int n) {
  vector<int> sol(3*n);
  vector<int> comptador(4,0); // comptador[0] no s'utilitza.
  // comptador[i] = k si i només si en la solució parcial porto k rosers de color i
  int idx = 0;
  bool hi_ha_consec = false;
  rosers(n,sol,idx,comptador,hi_ha_consec);
}

int main ( ){
  int n;
  while (cin >> n) {
    rosers(n);
    cout << string(10,'*') << endl;
  }
}