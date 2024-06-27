#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <tuple>

// using std::vector;
// using std::swap;
using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}
tuple<int,int> partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    // if (a[i] < x) {
    //   j++;
    //   k++;
    //   swap(a[j],a[k]);
    //   swap(a[i], a[j]);
    // }
    // else if(a[i] == x)
    // {
    //   k++;
    //   swap(a[i],a[k]);
    // }
    if (a[i] < x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  int k=j;
  for (int i = j+1; i <= r; i++) {
    if (a[i] == x) {
      k++;
      swap(a[i], a[k]);
    }
  }
  return make_tuple(j, k);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) return;

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  // int m = partition2(a, l, r);
  tuple<int, int> ms = partition3(a,l,r);
  // int m1 = get<0>(ms);
  // int m2 = get<1>(ms);
  // cout<<m1<<"---"<<m2<<endl;
  randomized_quick_sort(a, l, get<0>(ms) - 1);
  randomized_quick_sort(a, get<1>(ms) + 1, r);
}

// void randomized_quick_sort(vector<int> &a) {
//   randomized_quick_sort(a, 0, a.size() - 1);
//   // tuple<int,int> check =partition3(a,0,a.size());
//   // cout<<get<0>(check)<<"---"<<get<1>(check);
// }

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }
}

