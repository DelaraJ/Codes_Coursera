#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  int trash = 1;
  while (n>2*trash)
  {
    n-=trash;
    summands.push_back(trash);
    trash++;
  }
  if (n!=0)
  {
    summands.push_back(n);
  }

  return summands;
}

int main() {
  int n;
  cin >> n;
  vector<int> summands = optimal_summands(n);
  cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    cout << summands[i] << ' ';
  }
}
