#include <bits/stdc++.h>
using namespace std;
const double EPSILON = 1e-9;
typedef long double LD;
typedef vector<vector<LD>> matrix;
void findSubsetsOfSizeM(const vector<int>& set, int m, vector<unordered_set<int>>& subsets) {
    int n = set.size();
    vector<bool> v(n);
    fill(v.begin(), v.begin() + m, true);  // Create a mask with m ones and (n-m) zeros
    
    do {
        unordered_set<int> subset;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                subset.insert(set[i]);
            }
        }
        subsets.push_back(subset);
    } while (prev_permutation(v.begin(), v.end()));
}

vector<LD> SolveEquation(matrix a, vector<LD> b) {
    int size = a.size();
    for(int i=0; i<size; i++){
        //find first non-zero in ith column
        int row_num = -1;
        for(int j=i; j<size; j++){
            // if(a[j][i] != 0){
            if (fabs(a[j][i]) > EPSILON){
                row_num = j;
                break;
            }
        }
        if(row_num != -1){
            swap(a[i], a[row_num]);
            swap(b[i], b[row_num]);
            LD pivot_num = a[i][i];
            a[i][i] = 1;
            for(int j=i+1; j<size; j++){
                a[i][j]/=pivot_num;
            }
            b[i]/=pivot_num;
            for(int j=0; j<size; j++){
                if(j==i) continue;
                LD x = a[j][i];
                a[j][i] = 0;
                for(int k=0; k<size; k++){
                  if(k==i) continue;
                    a[j][k]-=x*a[i][k];
                }
                b[j]-=x*b[i];
            }

        }
    }
    return b;
}
bool is_an_answer(const matrix& A, const vector<LD>& solution,const vector<LD>& b, int n, int m){
  for(int i=0; i<n; i++){
    // if(solution[i]<0) return false;
    LD tmp =0;
    for(int j=0; j<m; j++){
      tmp+=A[i][j]*solution[j];
    }
    if(b[i] < tmp && (abs(tmp - b[i]) > 1e-3)) return false;
  }
  for(int j=0; j<m; j++){
      if(solution[j]<0) return false;
  }
  return true;
}

void extend_inequalities(matrix& A, vector<LD>& b, int m){
  vector<LD> trash(m, 0);
  for(int i=0; i<m; i++){
    trash[i] = 1;
    A.push_back(trash);
    trash[i] = 0;
    b.push_back(0);
  }
  for(int i=0; i<m; i++) trash[i] = 1;
  A.push_back(trash);
  b.push_back(1e8);
}

void subsetsFinding(int n, int m, vector<unordered_set<int>>& subsets){
  vector<int> set(n+m+1);
  for(int i=0; i<n+m+1; i++) set[i] = i;
  findSubsetsOfSizeM(set, m , subsets);
}

bool Find_possible_answers(int n, int m, vector<unordered_set<int>>& subsets, matrix& A, 
                            vector<LD>& b, pair<LD, vector<LD>>& finalAns, vector<LD>& c){
  bool contains_lastone = false;
  finalAns = {-numeric_limits<LD>::infinity(), vector<LD>()};
  for(int i=0; i<subsets.size(); i++){
    matrix tmp_A(m);
    vector<LD> tmp_b(m);
    int j=0;
    for(auto& s : subsets[i]){
      tmp_A[j] = A[s];
      tmp_b[j] = b[s];
      j++;
    }
    vector<LD> ans = SolveEquation(tmp_A, tmp_b);
    if(is_an_answer(A, ans, b, n , m)) {
      LD tmp = 0;
      for(int i=0; i<m; i++){
        tmp+= ans[i]*c[i];
      }
      if(finalAns.first < tmp) {
        finalAns={tmp, ans};
        if(subsets[i].find(n+m) != subsets[i].end()) contains_lastone = true;
        else contains_lastone = false;
      }
    }
  }
  return contains_lastone;
}

void do_whatever(int n, int m, matrix& A, vector<LD>& b,
                 pair<LD, vector<LD>>& anss, vector<LD>& c, bool& contains_lastone){
  extend_inequalities(A, b, m);
  vector<unordered_set<int>> subsets;
  subsetsFinding(n, m, subsets);
  contains_lastone = Find_possible_answers(n, m, subsets, A, b, anss, c);
}

pair<int, vector<LD>> solve_diet_problem(
  int n, int m, matrix A, vector<LD> b, vector<LD> c) {
  // 0 - (n-1) -> namoadele too matrix
  // n - (n+m-1) -> mahdoodiat har moteghayer
  
  pair<LD, vector<LD>> finalAns;
  bool contains_lastone;
  do_whatever(n, m, A, b, finalAns, c, contains_lastone);

  if(finalAns.second.size() == 0) return {-1, vector<LD>(1, 0)};
  if(contains_lastone /* ||  amount_of_max > 1000000000*/) return {1, vector<LD>(1, 0)};
  return {0, finalAns.second};
}

int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<LD>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<LD> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<LD> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<LD>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i=0; i<ans.second.size(); i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
