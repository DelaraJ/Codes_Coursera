#include <ios>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;
    vector<vector<int>> helper;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n)
    {
      helper.resize(n, vector<int>());
    }

    void printEquisatisfiableSatFormula() {
      set<set<int>> ans;
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        for(int i=0; i<helper.size(); i++){
          if(helper[i].size() == 1){
            if(A[i][helper[i][0]] > b[i]) ans.insert({-(helper[i][0]+1)});
            if(0 > b[i]) ans.insert({(helper[i][0]+1)});
          }
          else if(helper[i].size() == 2){
            if(A[i][helper[i][1]] + A[i][helper[i][0]] > b[i]) ans.insert({-(helper[i][0]+1), -(helper[i][1] + 1)});
            if(A[i][helper[i][0]] > b[i]) ans.insert({-(helper[i][0] + 1), (helper[i][1]+1)});
            if(A[i][helper[i][1]] > b[i]) ans.insert({-(helper[i][1] + 1), (helper[i][0] + 1)});
            if(0 > b[i]) ans.insert({helper[i][0] +1, helper[i][1]+1});
          }
          else if(helper[i].size() == 3){
            if(A[i][helper[i][0]] + A[i][helper[i][1]] + A[i][helper[i][2]] > b[i]) ans.insert({-(helper[i][0] + 1), -(helper[i][1] + 1), -(helper[i][2] + 1)});
            if(A[i][helper[i][0]] + A[i][helper[i][1]] > b[i]) ans.insert({-(helper[i][0] + 1), -(helper[i][1] + 1), helper[i][2]+1});
            if(A[i][helper[i][2]] + A[i][helper[i][1]] > b[i]) ans.insert({-(helper[i][2] + 1), -(helper[i][1] + 1), helper[i][0]+1});
            if(A[i][helper[i][2]] + A[i][helper[i][0]] > b[i]) ans.insert({-(helper[i][2] + 1), -(helper[i][0] + 1), helper[i][1]+1});
            if(A[i][helper[i][0]] > b[i]) ans.insert({-(helper[i][0] + 1), helper[i][1]+1, helper[i][2]+1});
            if(A[i][helper[i][1]] > b[i]) ans.insert({-(helper[i][1] + 1), helper[i][0]+1, helper[i][2]+1});
            if(A[i][helper[i][2]] > b[i]) ans.insert({-(helper[i][2] + 1), helper[i][1]+1, helper[i][0]+1});
            if(0 > b[i]) ans.insert({helper[i][0]+1, helper[i][1]+1, helper[i][2]+1});
          }
          // else helper.erase(helper[i]);
        }


        if(ans.size() != 0){
          cout << ans.size() << " " << A[0].size() << endl;
          for(auto& a : ans){
            for( int x : a){
              cout << x << " ";
            }
            cout << 0 << endl;
          }
        }
        else{
          cout<<"1 1" <<endl;
          cout<<"1 0" << endl;
        }


        // cout << "3 2" << endl;
        // cout << "1 2 0" << endl;
        // cout << "-1 -2 0" << endl;
        // cout << "1 -2 0" << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
        if(converter.A[i][j] != 0) converter.helper[i].push_back(j);
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
