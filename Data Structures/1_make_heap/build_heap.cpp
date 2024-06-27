#include <bits/stdc++.h>

using namespace std;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftUp(int i)
  {
    while(i>0 && data_[int((i-1)/2)]>data_[i])
    {
      swap(data_[int((i-1)/2)],data_[i]);
      swaps_.push_back(make_pair(int((i-1)/2), i));
      i=(i-1)/2;
    }
  }

  void SiftDown(int i)
  {
    int indexOfMin = i, size=data_.size();
    int l = 2*i +1;
    int r = 2*i +2;
    if(l<size && data_[l]<data_[indexOfMin]) indexOfMin=l;
    if(r<size && data_[r]<data_[indexOfMin]) indexOfMin=r;
    if (i!=indexOfMin)
    {
      swap(data_[i], data_[indexOfMin]);
      swaps_.push_back(make_pair(i, indexOfMin));
      SiftDown(indexOfMin);
    }

  }

  void GenerateSwaps() {
    swaps_.clear();
    // // The following naive implementation just sorts 
    // // the given sequence using selection sort algorithm
    // // and saves the resulting sequence of swaps.
    // // This turns the given array into a heap, 
    // // but in the worst case gives a quadratic number of swaps.
    // //
    // // TODO: replace by a more efficient implementation
    // for (int i = 0; i < data_.size(); ++i)
    //   for (int j = i + 1; j < data_.size(); ++j) {
    //     if (data_[i] > data_[j]) {
    //       swap(data_[i], data_[j]);
    //       swaps_.push_back(make_pair(i, j));
    //     }
    //   }

    for(int i=int(data_.size()/2); i>=0; i--)
    {
      SiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
