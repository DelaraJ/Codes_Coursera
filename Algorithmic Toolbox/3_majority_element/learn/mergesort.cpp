#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
//O(nLogn)
//spaceComplexity: O(n)
vector<int> Merge(vector<int> B, vector<int> C) 
{  
  vector<int> D;
  int right=0, left =0;
  while (left!=B.size() || right != C.size())
  {
    if(right == C.size())
    {
        D.push_back(B[left]);
        left++;
        cout<<0;
    }
    else if(left == B.size())
    {
        D.push_back(C[right]);
        right++;
        cout<<1;
    }
    else if(B[left] <= C[right])
    {
        D.push_back(B[left]);
        left++;
        cout<<0;
    }
    else
    {
        D.push_back(C[right]);
        right++;
        cout<<1;
    }
  }
//   while(!B.empty() && !C.empty())
//   {
//     int b = B.front();
//     int c= C.front();
//     if (b<=c)
//     {
//         D.push_back(b);
//         B.erase(B.begin());
//     }
//     else
//     {
//         D.push_back(c);
//         C.erase(C.begin());
//     }
//   }
//   while(!B.empty())
//   {
//     D.push_back(B.front());
//     B.erase(B.begin());
//   }
//   while(!C.empty())
//   {
//     D.push_back(C.front());
//     C.erase(C.begin());
//   }
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
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
//   vector<int> ans = MergeSort(a, 0, a.size());
  vector<int> ans = MergeSort(a);
  // for(int i=0; i<ans.size(); i++)
  // {
  //   cout << ans[i] << " ";
  // }
}
