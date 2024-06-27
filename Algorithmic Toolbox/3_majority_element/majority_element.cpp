#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int Count(vector<int> &a, int left, int right, int target)
{
  int res=0;
  for(int i =left; i<=right; i++)
  {
    if(a[i]==target) res++;
  }
  return res;
}
// int Count(vector<int> &a, int target)
// {
//   return Count(a, 0, a.size()-1, target);
// }
// vector<int> Merge(vector<int> B, vector<int> C) 
// {  
//   vector<int> D;
//   int right=0, left =0;
//   while (left!=B.size() || right != C.size())
//   {
//     if(right == C.size())
//     {
//         D.push_back(B[left]);
//         left++;
//     }
//     else if(left == B.size())
//     {
//         D.push_back(C[right]);
//         right++;
//     }
//     else if(B[left] <= C[right])
//     {
//         D.push_back(B[left]);
//         left++;
//     }
//     else
//     {
//         D.push_back(C[right]);
//         right++;
//     }
//   }
//   return D;
// }
// vector<int> MergeSort(vector<int> a, int left, int right) {
  
//   if (right==left)
//     {
//         vector<int> x ;
//         x.push_back(a[left]);
//         return x;
//     }
//   int mid = (left+right)/2;
//   vector<int> b = MergeSort(a, left, mid);
//   vector<int> c = MergeSort(a, mid+1, right);
//   return Merge(b, c); 
// }
// vector<int> MergeSort(vector<int> a) {
//     if (a.empty()) return a;
//     return MergeSort(a, 0, a.size()-1);
  
// }
int get_majority_element(vector<int> &a, int left, int right) {
  // int s= a.size();
  if (-1 == right) return -1; // if its empty
  if (left == right) return a[left]; // if there is only one element
  int m = (right+left)/2;
  int leftAns = get_majority_element(a, left, m);
  int rightAns = get_majority_element(a, m+1, right);
  if (leftAns==rightAns) return leftAns;
  int lCount = Count(a, left, right, leftAns);
  int rCount = Count(a, left, right, rightAns);
  return (lCount>rCount)? leftAns : rightAns;
  // if (right - left == 1) 
  #pragma region 
  // int maxCount=1, currentmax=1, currentcheck=a.front(), i=0;
  // a.erase(a.begin());
  
  // while(!a.empty())
  // {
  //   while(i<a.size())
  //   {
  //     if(currentcheck==a[i]) 
  //     {
  //       currentmax++;
  //       a.erase(a.begin()+i);
  //     }
  //     else i++;
  //   }
  //   if(currentmax>maxCount) maxCount=currentmax;
  //   currentmax=1;
  //   currentcheck = a.front();
  //   i=0;
  //   a.erase(a.begin());
  // }
  // return (maxCount>(s/2))? 1 : 0;
  #pragma endregion
}
int get_majority(vector<int> &a, int left, int right) {
  int finalAns = get_majority_element(a, 0, a.size()-1);
  return (Count(a, 0 , a.size()-1, finalAns)>(a.size()/2))? 1: 0;
}

// int get_majority(vector<int> &a, int left, int right)
// {
//   vector<int> ans = MergeSort(a);
//   int maybeAns = ans[(left+right)/2];
//   return (Count(ans, maybeAns)>(a.size()/2))? 1:0;
// }

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  // cout << (get_majority(a, 0, a.size()-1) /*!= -1*/) << '\n';
  cout << (get_majority(a, 0, a.size()-1) /*!= -1*/) << '\n';
  // return 0;
}
