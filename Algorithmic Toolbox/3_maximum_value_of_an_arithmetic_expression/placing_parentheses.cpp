#include <bits/stdc++.h>

using namespace std;

long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
  return 0;
}

void MinAndMax(int i, int j, vector<vector<long>> &m, vector<vector<long>> &M,const vector<char> &op)
{
 for(int k=i; k<j; k++)
 {
  long a = eval(M[i][k],M[k+1][j], op[k]);
  long b = eval(M[i][k],m[k+1][j], op[k]);
  long c = eval(m[i][k],M[k+1][j], op[k]);
  long d = eval(m[i][k],m[k+1][j], op[k]);
  m[i][j]=min(m[i][j], min(a, min(b, min(c, d))));
  M[i][j]=max(M[i][j], max(a, max(b, max(c, d))));
 } 
}

long long parentheses(const string &exp)
{

  int n = exp.length()/2 +1;
  int es = exp.length();
  vector<int> d(n);
  vector<char> op(n-1);
  for(int i=0; i<es; i+=2) d[i/2] = (int)exp[i]-(int)'0';
  for(int i=1; i<es; i+=2) op[i/2] = (char)exp[i];
  vector<vector<long>> m (n, vector<long>(n,1000000));
  vector<vector<long>> M (n, vector<long>(n,-1000000));



  for(int i=0; i<n; i++)
  {
    m[i][i]=d[i];
    M[i][i]=d[i];
  }
  for(int s=0; s<n; s++)
  {
    for(int i=0; i<n-s; i++)
    {
      int j = i+s;
      MinAndMax(i,j, m, M, op);
    }
  }
  return M[0][n-1];
}


// long long get_maximum_value(const string &exp) {
//   //write your code here
//   return 0;
// }

int main() {
  string s;
  std::cin >> s;
  std::cout << parentheses(s) << '\n';
}
