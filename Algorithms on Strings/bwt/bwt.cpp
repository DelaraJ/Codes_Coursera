#include <bits/stdc++.h>
using namespace std;

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

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}