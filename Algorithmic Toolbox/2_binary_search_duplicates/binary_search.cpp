#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size()-1; 

  while(right >= left)
  {
    int m = (left+right)/2;
    if(x==a[m])
    {
      while(x==a[m]) m--;
      return m+1;
    }
    else if (x > a[m]) left = m+1;
    else right = m-1;
  }
  return -1;
  
}


int main() {
  int n;
  cin>>n;
  vector<int> a(n);
  for(size_t i=0; i<a.size(); i++)
  {
    cin>>a[i];
  }
  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
