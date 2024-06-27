#include <algorithm>
#include <iostream>
#include <vector>

// #include <cstdlib>
using namespace std;
//O(nLogn)
//spaceComplexity: O(n)
int Partition(vector<int> &a, int left, int right) 
{  
  int pivot = a[left];
  int j = left;
  for(int i=left+1; i<=right; i++)
  {
    if(a[i]<=pivot) 
    {
        j++;
        swap(a[j], a[j]);
    }
    swap(a[j],a[i]);
    return j;

  }
}
void QuickSort(vector<int> &a, int left, int right) {
  
  if (right<=left) return;
  int m = Partition(a, left, right);
  QuickSort(a, left, m-1);
  QuickSort(a, m+1, right); 
}
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
//   vector<int> ans = MergeSort(a, 0, a.size());
  QuickSort(a, 0, a.size()-1);
  // for(int i=0; i<ans.size(); i++)
  // {
  //   cout << ans[i] << " ";
  // }
}
