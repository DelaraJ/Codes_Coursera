#include <bits/stdc++.h>

using namespace std;

vector<int> lcs2expect(vector<int> &a, vector<int> &b) {
  vector<int> output;
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
      // cout<< D[i][j] << " ";
    }
    // cout<<endl;
  }
  int ans=D[row-1][column-1];
  int tr=row-1, tc=column-1;
  int check=0;
  while(D[tr][tc]>=0 && check==0 && tc>0 && tr>0)
  {
    if(D[tr][tc]==0) 
    {
      check=1;
      output.push_back(a[tr-1]);
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
  // string str(output.begin(), output.end());
  return output;
}

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

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  // vector<int> res1 = lcs2expect(a,b);
  // for (size_t i = 0; i < res1.size(); i++) cout << res1[i];
  // cout<<endl;
  // vector<int> res2 = lcs2expect(b,c);
  // for (size_t i = 0; i < res2.size(); i++) cout << res2[i];
  // cout<<endl;

  // return lcs2(res1, res2);
  int row= a.size()+1, column= b.size()+1, height = c.size()+1;
  int D[row][column][height];

  for(int i=0; i<row; i++)
  {
    for(int j=0; j<column; j++)
    {

      for(int k=0; k<height; k++)
      {
        if(i==0 || j==0 || k==0) D[i][j][k]=0;
        else
        {
          int unknown;
          unknown=(a[i-1]==b[j-1] && b[j-1]==c[k-1])? D[i-1][j-1][k-1]+1 : D[i-1][j-1][k-1];
          D[i][j][k] = max(unknown, max(D[i-1][j][k],max(D[i][j-1][k], D[i][j][k-1])));
        }

      }
    }
  }
  int ans=D[row-1][column-1][height-1];
  return ans;
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
