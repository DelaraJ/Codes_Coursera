#include <bits/stdc++.h>

using namespace std;

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

string InverseBWT(const string& bwt) {
  int bound = bwt.size();
  vector<int> alphabetCounter(5, 0);
  vector<int> CounterTillNow(5, 0);
  vector<int> index(bound, 0);
  for(int i=0; i<bound; i++){
    index[i] = alphabetCounter[letterToIndex(bwt[i])];
    alphabetCounter[letterToIndex(bwt[i])]++;
  }
  CounterTillNow[0] = 0;
  CounterTillNow[1] = alphabetCounter[0];
  for(int i=2; i<5; i++){
    CounterTillNow[i] = CounterTillNow[i-1] + alphabetCounter[i-1];
  }
  vector<char> preAns(bound);
  preAns[bound-1] = '$';
  int i = 0;
  for(int j=0; j<bound-1; j++){
    preAns[bound-2-j] = bwt[i];
    i = CounterTillNow[letterToIndex(bwt[i])] + index[i];
  }
  string text(preAns.begin(), preAns.end());
  return text;
}

void PreprocessBWT(string& bwt, 
                   vector<int>& FirstOccurrence, 
                   vector<vector<int>>& Count) {
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
  sort(bwt.begin(), bwt.end());
  int i=0;
  for(int j=0; j<bwt.size(); j++){
    i = letterToIndex(bwt[j]);
    if(FirstOccurrence[i] == -1) FirstOccurrence[i] = j;
  }
}

int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const vector<int>& FirstOccurrence, 
                     vector<vector<int> >& Count) {
  int top=0, bottom=bwt.size()-1;
  int patternIndex = pattern.size()-1;
  while(top<=bottom){
    if(patternIndex >= 0){
      char symbol = pattern[patternIndex];
      patternIndex--;
      if(letterToIndex(symbol)<=0 && letterToIndex(symbol)>=5) return 0;
      int tmp = top;
      top = FirstOccurrence[letterToIndex(symbol)] + (Count[letterToIndex(symbol)][top]);
      if(bwt[tmp] == symbol) top--;
      bottom = FirstOccurrence[letterToIndex(symbol)] + Count[letterToIndex(symbol)][bottom] -1;
    }
    else{
      return bottom - top +1;
    }
  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
//   int pattern_count;
//   cin >> pattern_count;
  vector<vector<int>> Count(5, vector<int>(bwt.size(), 0));

  vector<int> FirstOccurrence(5, -1);
  vector<int> LastOccurrence(5, 0);
  PreprocessBWT(bwt, FirstOccurrence, Count);
  int bound = bwt.size();
  for (int pi = 0; pi < bound; ++pi) {
    // string pattern = bwt;
    // cin >> pattern;
    int occ_count = CountOccurrences(bwt.substr(pi), bwt, FirstOccurrence, Count);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
