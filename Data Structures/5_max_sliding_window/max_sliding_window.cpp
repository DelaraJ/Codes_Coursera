#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
class QueueWithMax {
    vector<int> stack;
    vector<int> maxs;

  public:

    void Push(int value) {
        stack.push_back(value);
        if(maxs.size()==0) maxs.push_back(value);
        else if(maxs.back()<=value) maxs.push_back(value);
    }

    void Pop() {
        assert(stack.size());
        if(stack.back()==maxs.back()) maxs.pop_back();
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return maxs.back();
    }
};

void max_sliding_window_naive(vector<int> const & A, int w) {
    // for (size_t i = 0; i < A.size() - w + 1; ++i) {
    //     int window_max = A.at(i);
    //     for (size_t j = i + 1; j < i + w; ++j)
    //         window_max = max(window_max, A.at(j));

    //     cout << window_max << " ";
    // }

    deque<int> dq;
    int must_remove=0;
    for(int i=0; i< w; i++)
    {
        while(!dq.empty() && A[dq.back()]<A[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }



    for(int i=w; i<A.size(); i++)
    {
        cout << A[dq.front()] << " ";
        if(dq.front()==must_remove) dq.pop_front();
        while(!dq.empty() && A[dq.back()]<A[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        must_remove++;
    }
    cout << A[dq.front()] << " ";


    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
