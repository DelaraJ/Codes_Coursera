#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int find_maximum_element (vector<int> a) 
{
  if (a.size()==0) return 0;
  return find_maximum_2(a, 0, a.size()-1);
//   return find_maximum_3(a, 0, a.size()-1);
}
int find_maximum_2 (vector<int> a, int left, int right) {
  if (right==left) return a[left];
  int mid = (left+right)/2;
  return max(find_maximum_2(a, left, mid), find_maximum_2(a, mid+1, right));
}
int find_maximum_3 (vector<int> a, int left, int right) {
  if (right==left) return a[left];
  if(right-left == 1) return max(a[right], a[left]);
  if(right-left == 2) return max(a[right], a[right+1], a[left]);
  int mid1 = (left+right)/3;
  int mid2 = 2*(left+right)/3;
  return max(find_maximum_3(a, left, mid1), find_maximum_3(a, mid1+1, mid2), find_maximum_3(a, mid2+1, right));
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  cout << (find_maximum_element(a)) << '\n';
}
