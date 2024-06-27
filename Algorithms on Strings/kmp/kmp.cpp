#include <bits/stdc++.h>

using namespace std;

void ComputePrefixFunction(string& P, vector<int>& s){
  int Psize = P.size();
  s[0] = 0;
  int border = 0;
  for(int i = 1; i<Psize; i++){
    while(border>0 && P[i]!=P[border]){
      border = s[border - 1];
    }
    if(P[i]==P[border]){
      border++;
    }
    else{
      border = 0;
    }
    s[i] = border;
  }
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  string S = pattern + '$' + text;
  int Ssize = S.size(), Psize = pattern.size();
  vector<int> prefixFunction(Ssize);
  ComputePrefixFunction(S, prefixFunction);
  for(int i=Psize+1; i<Ssize; i++){
    if(prefixFunction[i] == Psize) result.push_back(i-(2*Psize));
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
