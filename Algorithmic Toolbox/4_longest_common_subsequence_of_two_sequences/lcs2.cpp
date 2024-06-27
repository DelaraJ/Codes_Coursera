#include <bits/stdc++.h>

using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
  int row= a.size()+1, column= b.size()+1; 
  vector<vector<int>> D(row, vector<int>(column, 0));
  for(int i=1; i<row; i++)
  {
    for(int j=1; j<column; j++)
    {
      int unknown;
      unknown=(a[i-1]==b[j-1])? D[i-1][j-1]+1 : D[i-1][j-1];
      D[i][j] = max(unknown, max(D[i-1][j], D[i][j-1]));
    }
  }
  int ans=D[row-1][column-1];
  return ans;
}
vector<char> lcs2expect(string &a, string &b) {
  vector<char> output;
  int row= a.size()+1, column= b.size()+1; 
  vector<vector<int>> D(row, vector<int>(column, 0));
  for(int i=0; i<row; i++)
  {
    for(int j=0; j<column; j++)
    {
      if(i!=0 && j!=0)
      {
        int unknown;
        unknown=(a[i-1]==b[j-1])? D[i-1][j-1]+1 : D[i-1][j-1];
        D[i][j] = max(unknown, max(D[i-1][j], D[i][j-1]));
      }
      cout<< D[i][j] << " ";
    }
    cout<<endl;
  }
  int ans=D[row-1][column-1];
  int tr=row-1, tc=column-1;
  int check=0;
  while(D[tr][tc]>=0 && check==0)
  {
    if(D[tr][tc]==0) 
    {
      check=1;
      output.push_back(D[tr][tc]);
    }    
    if(tr!=0 && tc!=0 && D[tr-1][tc-1]==D[tr][tc]-1) 
    {
      output.push_back(a[tr-1]);
      tr-=1;
      tc-=1;
    }
    else if(tr!=0 && D[tr-1][tc]==D[tr][tc]-1) 
    {
      output.push_back(a[tr-1]);
      tr-=1;
    }
    else if(tc!=0 && D[tr][tc-1]==D[tr][tc]-1) 
    {
      output.push_back(a[tr-1]);
      tc-=1;
    }
    else
    {
      tr-=1;
      tc-=1;
    }
  }
  reverse(output.begin(), output.end());
  return output;
}

int main() {
  
  string a, b;
  
  cin>>a;
  cin>>b;

  vector<char> output=lcs2expect(a,b);
  for(int i=0; i<output.size(); i++)
  {
    cout<<output[i];
  }

  // size_t n;
  // cin >> n;
  // vector<int> a(n);
  // for (size_t i = 0; i < n; i++) {
  //   cin >> a[i];
  // }

  // size_t m;
  // cin >> m;
  // vector<int> b(m);
  // for (size_t i = 0; i < m; i++) {
  //   cin >> b[i];
  // }
}
