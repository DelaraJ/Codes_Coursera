#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ans;
void SiftDown(vector<int> &heap, int i){
    int minIndex = i;
    int r = 2*i+2, l = 2*i +1;
    int size = heap.size()-1;
    if(r<=size && heap[r] < heap[minIndex]){
        minIndex = r;
    }
    if(l<=size && heap[l] < heap[minIndex]){
        minIndex = l;
    }
    if(minIndex != i){
        ans.push_back(make_pair(i, minIndex));
        swap(heap[minIndex], heap[i]);
        SiftDown(heap, minIndex);
    }
}

void BuildHeap(vector<int> &nums){
    for(int i=(nums.size()-1)/2; i>=0; i--){
        SiftDown(nums, i);
    }
}

int main(){
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin>>v[i];
    BuildHeap(v);
    cout<<ans.size()<<endl;
    for(auto it : ans){
        cout<< it.first << " " << it.second <<endl;
    }
}