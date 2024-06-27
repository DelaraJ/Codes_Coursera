#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(vector<string> & patterns) {
  trie t;
  int last_index = 0;
  t.push_back({});
  for(const string &s : patterns){
    int index = 0;
    int x = 0; // root
    while(index<s.size()){
      auto it = t[x].find(s[index]);
      if(it!=t[x].end()){
        x = (*it).second;
        index++;
      }
      else{
        //make node
        while(index<s.size()){
          last_index++;
          t[x].insert({s[index], last_index});
          t.push_back({});
          x= last_index;
          index++;
        }
        break;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}