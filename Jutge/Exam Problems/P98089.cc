#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int best_cost_so_far;
vector<int> best_sol_so_far;

void compute_best_distribution (const vector<string>& people, const vector<vector<int>>& M,
				vector<int>& sol, int idx, vector<bool>& used, int current_cost) {
  if (current_cost >= best_cost_so_far) return;  
  int n = sol.size();
  if (idx == n) {
    if (current_cost < best_cost_so_far) {
      best_cost_so_far = current_cost;
      best_sol_so_far = sol;
    }    
  }
  else {
    for (int i = 1; i < n; ++i) {
      if (not used[i]) {
	sol[idx] = i;
	used[i] = true;
	compute_best_distribution(people,M,sol,idx+1,used,current_cost + M[sol[idx-1]][i]);
	used[i] = false;	
      }
    }
  }    
}

void write_best_distribution (const vector<string>& people, const vector<vector<int>>& M){
  int n = people.size();
  vector<int> sol(n);
  vector<bool> used(n,false);
  best_cost_so_far = numeric_limits<int>::max();
  sol[0] = 0;
  used[0] = true;
  int idx = 1;
  int current_cost = 0;
  compute_best_distribution(people,M,sol,idx,used,current_cost);
  cout << best_cost_so_far << endl;
  for (int i = 0; i < n; ++i)
    cout << (i > 0 ? " ": "") << people[best_sol_so_far[i]];
  cout << endl;
}

int main ( ){
  int n;
  while (cin >> n) {
    vector<string> people(n);
    for (int i = 0; i < n; ++i) cin >> people[i];
    vector<vector<int>> M(n,vector<int>(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	cin >> M[i][j];
    write_best_distribution(people,M);
  }
}