#include <bits/stdc++.h>

using namespace std;
int AlphabetSize = 5;
vector<char> alphabet({'$', 'A', 'C', 'G', 'T'});

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

vector<int> SortCharacters(const string& S){
  int Ssize = S.size();
  vector<int> order(Ssize);
  unordered_map<char, int> count;
  for(int i=0; i<AlphabetSize; i++){
    count[alphabet[i]] = 0;
  }
  for(int i=0; i<Ssize; i++){
    // if(count.find(S[i]) == count.end()){
    //   count[S[i]] =1;
    // }
    // else 
    count[S[i]]++;
  }
  for(int i=1; i<AlphabetSize; i++){
    count[alphabet[i]] += count[alphabet[i-1]];
  }
  for(int i= Ssize-1; i>=0; i--){
    count[S[i]]--;
    order[count[S[i]]] = i;
  }
  return order;
}

vector<int> SortDoubled(const string& S, int L, vector<int>& order, vector<int>& Class){
  int Ssize = S.size();
  vector<int> count(Ssize, 0), newOrder(Ssize);
  for(int i=0; i<Ssize; i++){
    count[Class[i]]++;
  }
  for(int i=1; i<Ssize; i++){
    count[i] += count[i-1]; 
  }
  for(int i= Ssize-1; i>= 0; i--){
    int start = (order[i] - L + Ssize) % Ssize;
    // int cl = Class[start];
    count[Class[start]]-=1;
    newOrder[count[Class[start]]] = start;
  }
  return newOrder;
}

vector<int> ComputeCharClasses(const string& S, vector<int>& order){
  int Ssize = S.size();
  vector<int> Class(Ssize);
  Class[order[0]] = 0;
  for(int i=1; i<Ssize; i++){
    if(S[order[i]] != S[order[i-1]]){
      Class[order[i]] = Class[order[i-1]] + 1;
    }
    else{
      Class[order[i]] = Class[order[i-1]];
    }
  }
  return Class;
}

vector<int> UpdatingClasses(vector<int>& newOrder, vector<int>& Class, int L){
  int n = newOrder.size();
  vector<int> newClass(n);
  newClass[newOrder[0]] = 0;
  for(int i=01; i<n; i++){
    int cur = newOrder[i];
    int prev = newOrder[i-1];
    int mid = (cur+L)%n, midPrev=(prev+L)%n;
    if((Class[cur] != Class[prev]) || (Class[mid] != Class[midPrev])){
      newClass[cur] = newClass[prev] + 1;
    }
    else
      newClass[cur] = newClass[prev];
  }
  return newClass;
}

vector<int> BuildSuffixArray(const string& text) {
  int t = text.size();
  vector<int> order = SortCharacters(text);
  vector<int> Class = ComputeCharClasses(text, order);
  int L=1;
  while(L<t){
    order = SortDoubled(text, L, order, Class);
    Class = UpdatingClasses(order, Class, L);
    L*=2;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
