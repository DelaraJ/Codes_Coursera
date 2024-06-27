#include <bits/stdc++.h>

using namespace std;


int AlphabetSize = 5;
vector<char> alphabet({'$', 'A', 'C', 'G', 'T'});

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



pair<int,int> bs(int start, int end, 
                       vector<int>& suf_arr, 
                       const string& pattern, 
                       const string& text){
    int start_index= -1, end_index = -1;
    int mid;
    while(start <= end){
        mid = (start + end) /2;
        string tmp = text.substr(suf_arr[mid], pattern.size());
        if(pattern < tmp){
            end = mid - 1;
        }
        else if(pattern > tmp){
            start = mid + 1;
        }
        else{
            start_index = mid;
            end = mid -1;
        }
    }
    start =0, end = suf_arr.size()-1;
    while(start <= end){
        mid = (start + end) /2;
        string tmp = text.substr(suf_arr[mid], pattern.size());
        if(pattern < tmp){
            end = mid - 1;
        }
        else if(pattern > tmp){
            start = mid + 1;
        }
        else{
            end_index = mid;
            start = mid +1;
        }
    }
    return {start_index, end_index};
}

pair<int, int> FindOccurrences(const string& pattern, const string& text, vector<int>& suf_arr) {
    int e = suf_arr.size() - 1;
    return bs(0, e, suf_arr, pattern, text);
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suf_arr = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    pair<int, int> occurrences = FindOccurrences(pattern, text, suf_arr);
    if(occurrences.first != -1){
        for (int j=occurrences.first; j<=occurrences.second; j++) {
        occurs[suf_arr[j]] = true;
        }
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
