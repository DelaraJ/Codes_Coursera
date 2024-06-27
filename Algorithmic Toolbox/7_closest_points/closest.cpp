#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>

using namespace std;
#pragma region 
bool comparex(tuple<double, double> &p1, tuple<double, double> &p2)
{
  return get<0>(p1)<get<0>(p2);
}

bool comparey(tuple<double, double> &p1, tuple<double, double> &p2)
{
  return get<1>(p1)<get<1>(p2);
}

// bool equality(tuple<double, double> &p1, tuple<double, double> &p2)
// {
//   return get<0>(p1)<get<0>(p2) && get<1>(p1)==get<1>(p2);
// }
#pragma endregion

double cal_dis(tuple<double, double> p1, tuple<double, double> p2)
{
  return sqrt(pow(get<0>(p1)-get<0>(p2),2)+pow(get<1>(p1)-get<1>(p2),2));
}



int binary_search(const vector<tuple<double, double>> &a, int x, int left, int right, string s) 
{
  // int left = 0, right = (int)a.size()-1; 
  while (right>=left)
  {
    int m = (right+left)/2;
    // int m = left + (right-left)/2;
    if(x>get<0>(a[m])) left=m+1;
    else right=m-1;
  }
  if(s=="left")    while(a[left-1]==a[left]) left-=1;
  else             while(a[left+1]==a[left]) left+=1;
  return left;
}

double minimal_distance(vector<tuple<double, double>> points, int i, int j) 
{
  // if(i>=j) return (double)1000000; 
  if(i==j-2) return min(cal_dis(points[i], points[i+1]), min(cal_dis(points[i], points[i+2]), cal_dis(points[i+1], points[i+2])));
  if(i==j-1) return cal_dis(points[i], points[j]);
  int mid= (i+j)/2;
  double d1 = minimal_distance(points, i, mid);
  double d2 = minimal_distance(points, mid+1, j);
  double d = min(d1, d2);
  // if(d==0) return 0;
  // int tr = (get<0>(points[mid])+get<0>(points[mid+1]))/2;
  int l1 = binary_search(points, (get<0>(points[mid]))-d, i, mid, "left");
  int l2 = binary_search(points, (get<0>(points[mid]))+d, mid+1, j, "right");
  if(l2==points.size()) l2--;

  vector<tuple<double, double>> pind;
  for(int i=l1; i<=l2; i++) pind.push_back(points[i]);
  // sort(pind.begin(), pind.end(), comparey);

  sort(pind.begin(), pind.end(), comparey);
  int sp = l2-l1+1;
  for(int i=0; i<sp; i++)
  {
    for(int j=i+1; j<=i+7; j++)
    {
      if(j>=sp) break;
      d= min(d, cal_dis(pind[i], pind[j]));
      // if(d==0) return 0;
    }
  }

  // for(int i=0; i<pind.size(); i++)
  //   for(int j=0; j<pind.size(); j++)
  //     if(i!=j)
  //       if(abs(get<1>(points[i])-get<1>(points[j]))<=7) 
  //         d = min(d, cal_dis(points[i], points[j]));
  


        
  return d;
}

int main() {
  size_t n;
  cin >> n;
  vector<tuple<double, double>> points(n);
  // vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    double x,y;
    cin >> x >> y;
    points[i] = make_tuple(x,y);
  }
  sort(points.begin(), points.end(), comparex);
  cout << fixed;
  cout << setprecision(9) << minimal_distance(points, 0, points.size()-1) << "\n";

  // const bool hasDuplicates = adjacent_find(points.begin(), points.end(), equality) != points.end();
  // vector<tuple<double, double>>::iterator it = unique(points.begin(), points.end(), equality);
  // bool wasUnique = (it == points.end());
  // cout << fixed;
  // double ans = (wasUnique)? minimal_distance(points, 0, points.size()-1) : 0.0;

}


// double minimal_distance(vector<tuple<double, double, int>> pointsxsorted, vector<tuple<double, double, int>> pointsysorted, int i, int j) 
// {
//   if(i==j) return (double)1000000; 
//   if(i==j-1) return cal_dis(pointsxsorted[i], pointsxsorted[j]);
//   int mid= (i+j)/2;
//   double d1 = minimal_distance(pointsxsorted, pointsysorted, 0, mid);
//   double d2 = minimal_distance(pointsxsorted, pointsysorted, mid+1, j);
//   double d = min(d1, d2);
//   int l1 = binary_search(pointsxsorted, pointsysorted, get<0>(pointsxsorted[mid])-d);
//   int l2 = binary_search(pointsxsorted, pointsysorted, get<0>(pointsxsorted[mid])+d);
//   if(l2==pointsxsorted.size()) l2--;

//   vector<tuple<double, double, int>> pind;
//   for(int i=l1; i<=l2; i++) pind.push_back(pointsxsorted[i]);
//   // sort(pind.begin(), pind.end(), comparey);
//   for(int i=0; i<pind.size(); i++)
//     for(int j=0; j<pind.size(); j++)
//       if(i!=j)
//         if(abs(get<1>(pointsxsorted[i])-get<1>(pointsxsorted[j]))<=7) 
//           d = min(d, cal_dis(pointsxsorted[i], pointsxsorted[j]));
        
//   return d;
// }

// int main() {
//   size_t n;
//   cin >> n;
//   vector<tuple<double, double, int>> pointsxsorted(n);
//   vector<tuple<double, double, int>> pointsysorted(n);
//   // vector<int> y(n);
//   for (size_t i = 0; i < n; i++) {
//     double x,y;
//     cin >> x >> y;
//     pointsxsorted[i] = make_tuple(x, y, i);
//     pointsysorted[i] = make_tuple(x, y, i);
//   }
//   sort(pointsxsorted.begin(), pointsxsorted.end(), comparex);
//   sort(pointsysorted.begin(), pointsysorted.end(), comparey);
//   cout << fixed;
//   cout << setprecision(9) << minimal_distance(pointsxsorted, pointsysorted, 0, pointsxsorted.size()-1) << "\n";
// }
