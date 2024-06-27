#include <bits/stdc++.h>

using namespace std;


int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}

	int endOfTheWord = NA;
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

trie build_trie(const string& Text) {
  trie t;
  t.push_back(Node());
  int last_index = 0;
  int TextLength = Text.size();
  for(int i=0; i< TextLength; i++){
	int index = i;
    int x = 0; // root
    while(index<TextLength){
    // for(int j=i; j<TextLength; j++){
    //   auto it = t[x].find(Text[index]);
      if(t[x].next[letterToIndex(Text[index])] != NA){
        x = t[x].next[letterToIndex(Text[index])];
		index++;
      }
      else{
        //make node
        while(index<TextLength){
          last_index++;
          t[x].next[letterToIndex(Text[index])] = last_index;
          t.push_back(Node());
          x= last_index;
          index++;
        }
		t[x].endOfTheWord = i;
        break;
      }
    }
	t[x].endOfTheWord = i;
  }
  return t;
}

set<int> dfs(const trie & t, const int& index){
	stack<int> st;
	set<int> res;
	st.push(index);
	while(!st.empty()){
		int x = st.top();
		st.pop();
		if(t[x].endOfTheWord != -1) res.insert(t[x].endOfTheWord);
		if(!t[x].isLeaf()){
			for(int i=0; i<4; i++){
				if(t[x].next[i]!=-1) st.push(t[x].next[i]);
			}
		}
	}
	return res;
}

set <int> solve (const string& text, int n, const vector <string>& patterns)
{
	set <int> result;
	trie t = build_trie(text);
	bool found = true;
	// write your code here
	for(const string& s : patterns){
		int index =0;
		for(int i=0; i<s.size(); i++){
			if(!found){
				found = true;
				break;
			}
			if(t[index].next[letterToIndex(s[i])] == -1){
				found = false;
			}
			else if(i==s.size()-1){
				index = t[index].next[letterToIndex(s[i])];
				set<int> locs = dfs(t, index);
				for(int loc : locs){
					result.insert(loc);
				}
			}
			else
			{
				index = t[index].next[letterToIndex(s[i])];
			} 
		}
	}
	// sort(result.begin(), result.end());
	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	set <int> ans;
	ans = solve (text, n, patterns);
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
