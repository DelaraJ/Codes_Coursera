#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

bool compare(const tuple<double, double>& a, const tuple<double, double>& b)
{
  return get<0>(a)/get<1>(a) < get<0>(b)/get<1>(b);
}

double get_optimal_value(double capacity, vector<tuple<double, double>> things) {
  double value = 0.0;
  while(capacity>0 && !things.empty())
  {
    double choose = min(capacity, get<1>(things.back()));
    double preVal = choose/get<1>(things.back());

    value += preVal*get<0>(things.back());
    capacity -= choose;
    things.pop_back();
  }
  
  return value;
}

int main() {
  #pragma region  
  int n;
  double capacity=50;
  cin >> n >> capacity;
  vector<tuple<double, double>> tuples;
  for (int i = 0; i < n; i++) {
    int value, weight;
    cin >> value >> weight;
    tuples.push_back(make_tuple(value, weight));
  }
  #pragma endregion
  // vector<tuple<double, double>> tuples = {
  //       make_tuple(100, 50),
  //       make_tuple(60, 20),
  //       make_tuple(120, 30)
  //   };
  sort(tuples.begin(), tuples.end(), compare);
  // for (const auto& tuple : tuples) {
  //       std::cout << std::get<0>(tuple) << " " << std::get<1>(tuple) << std::endl;
  //   }
  double optimal_value = get_optimal_value(capacity, tuples);


  cout.precision(10);
  cout << optimal_value << endl;
  return 0;
}
