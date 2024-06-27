#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

bool compare(const tuple<int, int> &a,const tuple<int, int> &b)
{
  return get<0>(a)<get<0>(b);
}

vector<int> fast_count_segments(vector<tuple<int, int>> segments, vector<tuple<int, int>> points) {
  int pointsCount= points.size();
  int segmentsCount = segments.size();
  vector<int> cnt(pointsCount);
  for(int i=0; i<pointsCount-1; i++)
  {
    int j =0 ; 
    while(get<0>(segments[j])<=get<0>(points[i]) && j<segmentsCount)
    {
      if(segments.empty()) break;
      if(get<1>(segments[j])>=get<1>(points[i]))
      {
        cnt[get<1>(points[i])]++;
        if(get<0>(points[i+1])>get<1>(segments[j])) 
        {
          segments.erase(segments.begin());
          j--;
        }
        else get<0>(segments[j]) = get<0>(points[i+1]);
      }
      j++;
    }
  }
  if(!segments.empty())
  {
    segmentsCount=segments.size();
    int j=0;
    while(get<0>(segments[j])<=get<0>(points[pointsCount-1])  && j<segmentsCount)
    {
      if(get<1>(segments[j])>=get<0>(points[pointsCount-1]))
      {
        cnt[get<1>(points[pointsCount-1])]++;
      }
      j++;
    }
  }

  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  cin >> n >> m;
  // vector<int> starts(n), ends(n);
  vector<tuple<int, int>> segments(n);
  for (size_t i = 0; i < n; i++) {
    int start, end;
    cin >> start >> end;
    segments[i]=make_tuple(start, end);
  }
  vector<tuple<int, int>> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    int trash;
    cin >> trash;
    points[i]=make_tuple(trash, i);
  }
  sort(segments.begin(), segments.end(), compare);
  sort(points.begin(), points.end(), compare);
  vector<int> cnt = fast_count_segments(segments, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    cout << cnt[i] << ' ';
  }
}
