#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//O(nLogn)
//spaceComplexity: O(n)
vector<int> Merge(vector<int> B, vector<int> C, int& ans) 
{  

  vector<int> D;
  int right=0, left =0, mid = B.size();
  while (!B.empty() || right != C.size())
  {
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
        ans+=B.size();
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
  }
  return D;
}
vector<int> MergeSort(vector<int> a, int left, int right, int& ans) {
  
  if (right==left)
    {
        vector<int> x ;
        x.push_back(a[left]);
        return x;
    }
  int mid = (left+right)/2;
  vector<int> b = MergeSort(a, left, mid, ans);
  vector<int> c = MergeSort(a, mid+1, right, ans);
  vector<int> D= Merge(b, c, ans); 
  return D;
}
vector<int> MergeSort(vector<int> a, int& ans) {
    if (a.empty()) return a;
    return MergeSort(a, 0, a.size()-1, ans);
  
}
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  int ans = 0;
//   vector<int> ans = MergeSort(a, 0, a.size());
  vector<int> anss = MergeSort(a, ans);
  cout<<ans;
  // for(int i=0; i<ans.size(); i++)
  // {
  //   cout << ans[i] << " ";
  // }
}
