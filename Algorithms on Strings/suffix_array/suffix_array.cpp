#include <bits/stdc++.h>

using namespace std;

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

string BWT(string& text) {
  string result = "";
  int bound = text.size();
  vector<string> BWT(bound);
  for(int i=0; i<bound; i++){
    string preans = text.substr(i);
    preans += text.substr(0, i);
    BWT[i] = preans;
  }
  sort(BWT.begin(), BWT.end());
  for(int i=0; i<bound; i++){
    result+= BWT[i][bound-1];
  }
  return result;
}

vector<int> BuildSuffixArray(string& text) {
  string bwt = BWT(text);
  int bound = bwt.size();
  vector<int> result(bound, 0);
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
  
  int i = 0, x = bound-1;
  for(int j=0; j<bound; j++){
    result[i] = x;
    x--;
    i = CounterTillNow[letterToIndex(bwt[i])] + index[i];
  }
  return result;
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
