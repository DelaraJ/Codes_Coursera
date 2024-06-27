#include<bits/stdc++.h>
using namespace std;

int edit_distance(const string &str1, const string &str2) {
  int row= str1.size()+1, column= str2.size()+1; 
  vector<vector<int>> D(row, vector<int>(column, 0));
  for(int i=1; i<column; i++) D[0][i]=i;
  for(int i=1; i<row; i++) D[i][0]=i;
  for(int i=1; i<row; i++)
  {
    for(int j=1; j<column; j++)
    {
      int unknown;
      unknown=(str1[i-1]==str2[j-1])? D[i-1][j-1] : D[i-1][j-1]+1;
      D[i][j] = min(unknown, min(D[i-1][j]+1, D[i][j-1]+1)); 
    }
  }
  int ans=D[row-1][column-1];
  return ans;
}

int main() {
  string str1;
  string str2;
  cin >> str1 >> str2;
  cout << edit_distance(str1, str2) << endl;
  return 0;
}
