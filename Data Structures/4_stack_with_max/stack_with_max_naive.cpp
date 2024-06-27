#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class StackWithMax {
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
        // return *max_element(stack.begin(), stack.end());
        return maxs.back();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}