#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a, int x) 
{
  int left = 0, right = (int)a.size()-1; 
  while (right>=left)
  {
    int m = (right+left)/2;
    if(a[m]==x) return m;
    else if(x>a[m]) left=m+1;
    else right=m-1;
  }
  // if(right==left && x==a[right]) return right;
  return left;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    cout << binary_search(a, b[i]) << ' ';
  }
}
