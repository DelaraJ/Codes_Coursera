#include <iostream>
#include <vector>

using namespace std;


long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  // Merge(newVec(a.begin()+left, a.begin()+ave), newVec(a.begin()+ave+1, a.begin()+right));
  return number_of_inversions;
}


int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> b(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
    b[i]=a[i];
  }
  cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
