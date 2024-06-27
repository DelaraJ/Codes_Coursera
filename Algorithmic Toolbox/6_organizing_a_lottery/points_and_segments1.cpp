#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <algorithm>
using namespace std;


#pragma region 
tuple<int,int> partition3(vector<int> &a, vector<int> &b, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] < x) {
      j++;
      swap(a[i], a[j]);
      swap(b[i], b[j]);
    }
  }
  swap(a[l], a[j]);
  swap(b[l], b[j]);
  int k=j;
  for (int i = j+1; i <= r; i++) {
    if (a[i] == x) {
      k++;
      swap(a[i], a[k]);
      swap(b[i], b[k]);
    }
  }
  return make_tuple(j, k);
}

void randomized_quick_sort(vector<int> &a, vector<int> &b, int l, int r) {
  if (l >= r) return;
  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  swap(b[l], b[k]);
  tuple<int, int> ms = partition3(a, b, l, r);
  randomized_quick_sort(a, b, l, get<0>(ms) - 1);
  randomized_quick_sort(a, b, get<1>(ms) + 1, r);
}
#pragma endregion


bool compare(const tuple<int, int> &a,const tuple<int, int> &b)
{
  return get<0>(a)<get<0>(b);
}


int binary_search(const vector<tuple<int, int>> &a, int x) 
{
  int left = 0, right = (int)a.size()-1, bePowerful=0; 
  while (right>=left)
  {
    int m = (right+left)/2;
    if(get<0>(a[m])==x) return m;
    else if(x<get<0>(a[m])) right=m-1;
    else 
    {
      left=m+1;
      bePowerful=m;
    }
    
  }
  right = (int)a.size()-1;
  while(get<0>(a[bePowerful])<x && right>bePowerful)
  {
    right--;
    bePowerful++;
  }
  if(bePowerful==0)
  {
    return (get<0>(a[bePowerful])<x)? 0 : -1;
  }
  return (get<0>(a[bePowerful])<x)? bePowerful : (bePowerful-1);
}

// int binary_search2(const vector<tuple<int, int>> &a, int x) 
// {
//   int left = 0, right = (int)a.size()-1, bePowerful=0; 
//   while (right>=left)
//   {
//     int m = (right+left)/2;
//     if(get<0>(a[m])==x) 
//     {
//       // bePowerful=m;
//       break;
//     }
//     else if(x<get<0>(a[m])) right=m-1;
//     else 
//     {
//       left=m+1;
//       bePowerful=m;
//     }
    
//   }
//   right = (int)a.size()-1;
//   while(get<0>(a[bePowerful])<x && right>bePowerful)
//   {
//     right--;
//     bePowerful++;
//   }
//   if(bePowerful==0)
//   {
//     return (get<0>(a[bePowerful])<x)? 0 : -1;
//   }
//   return (get<0>(a[bePowerful])<x)? bePowerful : (bePowerful-1);
// }

vector<int> Merge(vector<int> B, vector<int> C) 
{  
  vector<int> D;
  int right=0, left =0;
  while(!B.empty() && !C.empty())
  {
    int b = B.front();
    int c= C.front();
    if (b<=c)
    {
        D.push_back(b);
        B.erase(B.begin());
    }
    else
    {
        D.push_back(c);
        C.erase(C.begin());
    }
  }
  while(!B.empty())
  {
    D.push_back(B.front());
    B.erase(B.begin());
  }
  while(!C.empty())
  {
    D.push_back(C.front());
    C.erase(C.begin());
  }
  return D;
}
vector<int> MergeSort(vector<int> a, int left, int right) {
  
  if (right==left)
    {
        vector<int> x ;
        x.push_back(a[left]);
        return x;
    }
  int mid = (left+right)/2;
  vector<int> b = MergeSort(a, left, mid);
  vector<int> c = MergeSort(a, mid+1, right);
  return Merge(b, c); 
}
vector<int> MergeSort(vector<int> a) {
    if (a.empty()) return a;
    return MergeSort(a, 0, a.size()-1);
  
}

vector<int> fast_count_segments(vector<tuple<int, int>> segments, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    int s=0,j=0;
    while(get<0>(segments[j])<=points[i] && j<segments.size())
    {
      if(get<0>(segments[j])==points[i])
      {
        if(get<1>(segments[j])==-1) s--;
        cnt[i]++;
      } 
      else s+=get<1>(segments[j]);
      j++;
    }
    cnt[i]+=s;
  }
  return cnt;
}


int main() {
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int>> segments(2*n);
  for (size_t i = 0; i < 2*n; i+=2) {
    int start, end;
    cin >> start >> end;
    segments[i]=make_tuple(start, 1);
    segments[i+1]=make_tuple(end, -1);
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    cin >> points[i];
  }

  sort(segments.begin(), segments.end());

  // sort(segments.begin(), segments.end(), compare);
  // randomized_quick_sort(starts, ends, 0, starts.size()-1);

  vector<int> cnt = fast_count_segments(segments, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    cout << cnt[i] << ' ';
  }
}
