#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> move_dirs = {{0,1},{0,-1},{-1,0},{1,0}};

vector<pair<int,int>> all_dirs = {{0,1},{0,-1},{-1,0},{1,0},
				  {1,1},{1,-1},{-1,1},{-1,-1}};


bool safe_pos (const vector<vector<char>>& M, int i, int j) {
  for (auto& d : all_dirs)
    if (M[i + d.first][j + d.second] == 'F') return false;
  return true;
}

bool reachable (vector<vector<char>>& M, int i, int j) {
  if (M[i][j] == 'X') return false;
  if (not safe_pos(M,i,j)) return false;    
  if (M[i][j] == 'B') return true;

  M[i][j] = 'X';
  for (auto& d : move_dirs) {
    int n_i = i + d.first;
    int n_j = j + d.second;
    if (reachable(M,n_i,n_j)) return true;
  }
  return false;
}

int main ( ){
  int f, c;
  while (cin >> f >> c) {
    vector<vector<char>> M(f,vector<char>(c));
    int ini_i = -1, ini_j = -1;
    for (int i = 0; i < f; ++i) 
      for (int j = 0; j < c; ++j) {
	cin >> M[i][j];
	if (M[i][j] == 'P') {ini_i = i; ini_j = j;}
      }
    if (reachable(M,ini_i,ini_j)) cout << "si" << endl;
    else cout << "no" << endl;
  }
}