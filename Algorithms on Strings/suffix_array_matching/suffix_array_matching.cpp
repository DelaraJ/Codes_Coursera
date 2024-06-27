#include <bits/stdc++.h>

using namespace std;
int AlphabetSize = 5;
vector<char> alphabet({'$', 'A', 'C', 'G', 'T'});

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

int letterToIndex (char letter)
{
	switch (letter)
	{
		case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		default: assert (false); return -1;
	}
}

vector<int> FirstOccurrence(AlphabetSize, 0);
// unordered_map<char, int> counter;
vector<int> SortCharacters(const string& S){
  int Ssize = S.size();
  vector<int> order(Ssize);
  vector<int> counter(AlphabetSize, 0);
  // for(int i=0; i<AlphabetSize; i++){
  //   counter[alphabet[i]] = 0;
  // }
  for(int i=0; i<Ssize; i++){
    // if(counter.find(S[i]) == counter.end()){
    //   counter[S[i]] =1;
    // }
    // else 
    counter[letterToIndex(S[i])]++;
    FirstOccurrence[letterToIndex(S[i])]++;
  }
  for(int i=1; i<AlphabetSize; i++){
    FirstOccurrence[i] += FirstOccurrence[i-1];
    counter[i] += counter[i-1];
  }
  for(int i= Ssize-1; i>=0; i--){
    counter[letterToIndex(S[i])]--;
    order[counter[letterToIndex(S[i])]] = i;
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

// void PatterMatchingWithSuffixArray(string& text, string& pattern){
//   vector<int> SuffixArray = BuildSuffixArray(text);
//   int minIndex =0;
//   int maxIndex = text.size();
//   while(minIndex < maxIndex){
//     int midIndex = (minIndex + maxIndex)/2;
//     if(pattern > text.substr(SuffixArray[midIndex])){
//       minIndex
//     }
//   }
// }

string BuildBWT(const vector<int>& suffixArray, const string& Text, int TextSize){
  vector<char> LC(TextSize);
  for(int i=0; i<suffixArray.size(); i++){
    // FC[i] = Text[suffixArray[i]];
    LC[i] = Text[(suffixArray[i]-1 + TextSize) % TextSize];
  }
  // string firstCol (FC.begin(), FC.end());
  string bwt (LC.begin(), LC.end());
  return bwt;
}



vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array, const string& bwt) {
  vector<vector<int>> Count(5, vector<int>(bwt.size(), 0));
  int bound = bwt.size();
  for(int i=0; i<bound; i++){
    if(i==0) Count[letterToIndex(bwt[i])][i]++;
    else{
      for(int j=0; j<5; j++){
        if(j == letterToIndex(bwt[i])) Count[j][i] = Count[j][i-1] +1;
        else Count[j][i] = Count[j][i-1];
      }
    }
  }
  vector<int> res;
  int top=0, bottom=bound-1;
  int patternIndex = pattern.size()-1;
  while(top<=bottom){
    if(patternIndex >= 0){
      char symbol = pattern[patternIndex];
      patternIndex--;
      if(letterToIndex(symbol)<=0 && letterToIndex(symbol)>=5) return res;
      int tmp = top;
      top = FirstOccurrence[letterToIndex(symbol)] + (Count[letterToIndex(symbol)][top]);
      if(bwt[tmp] == symbol) top--;
      bottom = FirstOccurrence[letterToIndex(symbol)] + Count[letterToIndex(symbol)][bottom] -1;
    }
    else{
      for(int i=top; i<=bottom; i++){
        res.push_back(suffix_array[i]);
      }
    }
  }
  return res;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  string bwt = BuildBWT(suffix_array, text, text.size());
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array, bwt);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
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
