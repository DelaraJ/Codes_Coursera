#include <algorithm>
#include <iostream>
#include <climits>
#include <tuple>
#include <vector>

using namespace std;

// struct Segment {
//   int start, end;
// };

bool compare(const tuple<int,int>& a, const tuple<int, int>& b)
{
  return get<1>(a) > get<1>(b);
}
void check_what_should_remove(vector<tuple<int, int>> &segments, int selected_point, vector<int>& points)
{
  points.push_back(selected_point);
  while((selected_point>=get<0>(segments.back())) &&
        (selected_point<=get<1>(segments.back()))    )
  {
    // points.push_back(get<0>(segments.back()));
    if (segments.size()==1)
    {
      segments.pop_back();
      break;
    }
    segments.pop_back();
  }
  
}
vector<int> optimal_points(vector<tuple<int, int>> &segments) {
  vector<int> points;
  // points.push_back(get<1>(segments.back()));
  while(!segments.empty())
  {
    check_what_should_remove(segments, get<1>(segments.back()), points);
  }
  //write your code here
  // for (size_t i = 0; i < segments.size(); ++i) {
  //   points.push_back(get<0>(segments[i]));
  //   points.push_back(get<1>(segments[i]));
  // }
  return points;
}

int main() {
  int n;
  cin >> n;


  // vector<Segment> segments(n);
  
  
  vector<tuple<int, int>> segments;//=
  // {
  //   make_tuple(4, 7),
  //   make_tuple(1, 3),
  //   make_tuple(2, 5),
  //   make_tuple(5, 6)
  // };
  
  
  for (int i = 0; i < n; i++) {
    int start, end;
    cin >> start >> end;
    segments.push_back(make_tuple(start, end));
  }
  
  sort(segments.begin(), segments.end(), compare);
  vector<int> points = optimal_points(segments);
  cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    cout << points[i] << " ";
  }
}
