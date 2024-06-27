#include <bits/stdc++.h>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;

trie build_trie(const vector<string> & patterns) {
  trie t;
  t.push_back(Node());
  int last_index = 0;
  for(const string &s : patterns){
	int index = 0;
    int x = 0; // root
    while(index<s.size()){
      if(t[x].next[letterToIndex(s[index])] != NA){
        x = t[x].next[letterToIndex(s[index])];
		index++;
      }
      else{
        //make node
        while(index<s.size()){
          last_index++;
          t[x].next[letterToIndex(s[index])] = last_index;
          t.push_back(Node());
          x= last_index;
          index++;
        }
		t[x].patternEnd = true;
        break;
      }
    }
	t[x].patternEnd=true;
  }
  return t;
}

set<int> solve (string text, int n, vector <string> patterns)
{
	set <int> result;
	trie t = build_trie(patterns);
	bool found = false;
	int TextLength = text.size();
    for(int i=0; i< TextLength; i++){
		int textIndex =i;
        int x = 0; // root
        while(textIndex<TextLength){
            if(t[x].next[letterToIndex(text[textIndex])] == -1) break;
			else{
                // if(textIndex!=TextLength-1 && t[x].patternEnd){
                //     result.insert(i);
                // }
				x = t[x].next[letterToIndex(text[textIndex])];
                if(t[x].patternEnd)  result.insert(i);
                textIndex++;
			}
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	set<int> ans;
	ans = solve (t, n, patterns);

	int i=0;
	for (int x : ans)
	{
		cout << x;
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
		i++;
	}

	return 0;
}
