#include <bits/stdc++.h>

using namespace std;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.

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
    // text = bwt[i] + text;
    preAns[bound-2-j] = bwt[i];
    i = CounterTillNow[letterToIndex(bwt[i])] + index[i];
  }
  string text(preAns.begin(), preAns.end());
  // text.reserve();
  return text;
}

void PreprocessBWT(string bwt, 
                   vector<int>& FirstOccurrence, 
                  //  vector<int>& LastOccurrence,
                   vector<vector<int>>& Count) {
  int bound = bwt.size();
  // vector<int> alphabetCounter(5, 0);
  // vector<int> index(bound, 0);
  for(int i=0; i<bound; i++){
    if(i==0) Count[letterToIndex(bwt[i])][i]++;
    else{
      for(int j=0; j<5; j++){
        if(j == letterToIndex(bwt[i])) Count[j][i] = Count[j][i-1] +1;
        else Count[j][i] = Count[j][i-1];
      }
    }
    // index[i] = alphabetCounter[letterToIndex(bwt[i])];

    // if(FirstOccurrence[letterToIndex(bwt[i])] == -1) FirstOccurrence[letterToIndex(bwt[i])] = i;

    // if(letterToIndex(bwt[i]) == 0 && FirstOccurrence[0]==-1) FirstOccurrence[0] == 0;
    // if(letterToIndex(bwt[i]) == 1){
    //   FirstOccurrence[1] = FirstOccurrence[0]+1;

    // }
    // if(letterToIndex(bwt[i]) == 2){
    //   FirstOccurrence[2] = FirstOccurrence[0]

    // }


    // LastOccurrence[letterToIndex(bwt[i])] = i;
    // alphabetCounter[letterToIndex(bwt[i])]++;
  }
  sort(bwt.begin(), bwt.end());
  int i=0;
  for(int j=0; j<bwt.size(); j++){
    i = letterToIndex(bwt[j]);
    if(FirstOccurrence[i] == -1) FirstOccurrence[i] = j;
  }
  // Implement this function yourself
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const vector<int>& FirstOccurrence, 
                    //  const vector<int>& LastOccurrence,
                     vector<vector<int> >& Count) {
  // Implement this function yourself
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
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  // map<char, int> FirstOccurrence;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  // map<char, vector<int> > Count;
  // Count['A'] = vector(bwt.size(), 0);
  // Count['C'] = vector(bwt.size(), 0);
  // Count['T'] = vector(bwt.size(), 0);
  // Count['G'] = vector(bwt.size(), 0);
  // Count['$'] = vector(bwt.size(), 0);

  vector<vector<int>> Count(5, vector<int>(bwt.size(), 0));

  vector<int> FirstOccurrence(5, -1);
  vector<int> LastOccurrence(5, 0);
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, FirstOccurrence, Count);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, FirstOccurrence, Count);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
