#include <bits/stdc++.h>

// using std::vector;
// using std::swap;
using namespace std;

int partition2(vector<int> &a, int left, int right) {
  int pivot = a[left];
    int j=left;

  for(int i=left+1; i<=right; i++)
  {
    if(a[i]<= pivot)
    {
        j++;
        swap(a[i], a[j]);
    }
  }
  swap(a[j], a[left]);
  return j;
}

void quick_sort(vector<int> &preAns, int left, int right) 
{
    if(right<=left) return;
    
    // if ((left-right) >= a.size()/4 && (left-right)>2)
    // {
    //   int minimumElement = *min_element(a.begin()+left, a.begin()+right);
    //   if (a[left] == minimumElement) 
    //   {
    //     int wishToMakeEverythingBetter = left + (rand() % (1, left-right +1));
    //     swap(a[wishToMakeEverythingBetter], a[left]);
    //   }
    // }

    int wishToMakeEverythingBetter = left + (rand() % (left-right +1));
    swap(preAns[wishToMakeEverythingBetter], preAns[left]);
    
    int mid = partition2(preAns, left, right);
    quick_sort(preAns, left, mid-1);
    quick_sort(preAns, mid+1, right);
}

void randomized_quick_sort(vector<int> &a) 
{
  int maximumElement = *max_element(a.begin(), a.end());
  vector<int> b(maximumElement+1), preAns;
  for (int i=0; i<a.size(); i++) b[a[i]]++;
  for (int i=0; i<maximumElement+1; i++) if(b[i]!=0) preAns.push_back(i);
  // quick_sort(preAns, 0, preAns.size()-1);
  int k=0;
  for(int i=0; i<preAns.size(); i++)
  {
    for(int j=0; j<b[preAns[i]]; j++)
    {
      a[k]=preAns[i];
      k++;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  randomized_quick_sort(a);
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }
}
