#include <bits/stdc++.h>

using namespace std;

int const Letters =    5;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;
	string s;
	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
  bool isLeaf(){
    return next[0]==NA && next[1]==NA && next[2]==NA && next[3]==NA && next[4]==NA;
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
		case '$': return 4; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> tree;

void make_new_essential_node(tree& t, int &last_index, int& x, string Text, int index){
  last_index++;
  t[x].next[letterToIndex(Text[index])] = last_index;
  t.push_back(Node());
  x= last_index;
  t[x].s = Text.substr(index);
}

void make_middle_node(tree& t, int &last_index, int& x,const string& Text, int index, int suffix_index, string suffix){
  last_index++;
  int k = letterToIndex(t[x].s[suffix_index]);
  t.push_back(Node());
  for(int j =0; j<Letters; j++){
    t[last_index].next[j] = t[x].next[j];
    t[x].next[j] = -1;
  }
  t[x].next[k] = last_index;
  t[last_index].s = t[x].s.substr(suffix_index);

  t[x].s = t[x].s.substr(0, suffix_index);
  last_index++;
  t[x].next[letterToIndex(Text[index])] = last_index;
  t.push_back(Node());
  t[last_index].s = Text.substr(index);
}

void root_swiching(int& x, tree& t, const string &Text, int& index, string& suffix, int& suffix_index){
  x = t[x].next[letterToIndex(Text[index])];
  suffix = t[x].s;
  suffix_index =0;
}

tree build_tree(const string& Text) {
  tree t;
  t.push_back(Node());
  int last_index = 0;
  int TextLength = Text.size();
  for(int i=0; i< TextLength; i++){
	  int index = i;
    int x = 0;
    if(t[x].next[letterToIndex(Text[index])] != NA){
      x = t[x].next[letterToIndex(Text[index])];
      string suffix =t[x].s;
      int suffix_index = 0;
      while(index < TextLength){
        if(suffix_index < t[x].s.size() && Text[index] != suffix[suffix_index]){
          make_middle_node(t,last_index, x, Text, index, suffix_index, suffix);
          break;
        }
        else if(suffix_index >= t[x].s.size()){
          if(t[x].next[letterToIndex(Text[index])] != NA){ //node switch
            root_swiching(x, t, Text, index, suffix, suffix_index);
          }
          else{//nahamahangi
            make_new_essential_node(t, last_index, x, Text, index);
            break;
          }

        }
        suffix_index++;
        index++;
      }
    }
    else if(t[x].next[letterToIndex(Text[index])] == NA){
      make_new_essential_node(t, last_index, x, Text, index);
    }
  }
  return t;
}


vector<string> dfs(tree & t){
	stack<int> st;
	vector<string> res;
  vector<bool> visited(t.size(), false);
  int x =0;
  if(!t[x].isLeaf()){
			for(int i=0; i<Letters; i++){
				if(t[x].next[i]!=-1) st.push(t[x].next[i]);
			}
	}
	while(!st.empty()){
		x = st.top();
		st.pop();
		if(!t[x].isLeaf()){
			for(int i=0; i<Letters; i++){
				if(t[x].next[i]!=-1 && !visited[t[x].next[i]]) st.push(t[x].next[i]);
			}
		}
    if(!visited[x]){
      visited[x] = true;
      res.push_back(t[x].s);
    } 
	}
	return res;
}
vector<string> ComputeSuffixTreeEdges(const string& text) {
  tree t = build_tree(text);
  return dfs(t);
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
