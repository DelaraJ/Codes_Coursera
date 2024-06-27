#include <bits/stdc++.h>

using namespace std;

int const Letters =    5;
int const NA      =   -1;

struct Node
{
	Node* next [Letters];
	bool patternEnd;
	string s;
	Node ()
	{
		fill (next, next + Letters, nullptr);
		patternEnd = false;
	}
  bool isLeaf(){
    return next[0]==nullptr && next[1]==nullptr && next[2]==nullptr && next[3]==nullptr && next[4]==nullptr;
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

typedef vector<Node*> tree;
typedef Node* root;

void node_swiching(root& x, const string& Text, int& suffix_index, int& index){
  x = x->next[letterToIndex(Text[index])];
  suffix_index =0;
}

void make_new_essential_node(root& x, const string& Text, int& index){
  x->next[letterToIndex(Text[index])] = new Node;      
  x = x->next[letterToIndex(Text[index])];
  x->s = Text.substr(index);
}

void make_middle_node(root& x, const string& Text, int& suffix_index, int& index){

  x->next[letterToIndex(x->s[suffix_index])] = new Node;
  x->next[letterToIndex(x->s[suffix_index])]->s = x->s.substr(index);
  x->s = x->s.substr(0, suffix_index);
  x->next[letterToIndex(Text[index])] = new Node;
  x->next[letterToIndex(Text[index])]->s = x->s.substr(index);
}

void build_tree(const string& Text, Node* &t) {
  int TextLength = Text.size();
  root x = t;
  for(int i=0; i< TextLength; i++){
	int index = i;
    x = t;
    char check2 = Text[index];
    int check = letterToIndex(check2);
      if(x->next[check] != nullptr){
        x = x->next[check];
        string suffix =x->s;
        int suffix_index = 0;
        while(index < TextLength){
          if(suffix_index < x->s.size() && Text[index] != suffix[suffix_index]){
            make_middle_node(x, Text, suffix_index, index);
            break;
          }
          else if(suffix_index >= x->s.size()){
            if(x->next[letterToIndex(Text[index])] != nullptr){ //node switch
              node_swiching(x, Text, suffix_index, index);
            }
            else{//nahamahangi
              make_new_essential_node(x, Text, index);
              break;
            }

          }
          suffix_index++;
          index++;
        }
      }
      else if(x->next[letterToIndex(Text[index])] == nullptr){
        make_new_essential_node(x, Text, index);
      }
  }
//   return t;
}


vector<string> dfs(root& t){
    stack<Node*> st;
    vector<string> res;
    auto x = t;
    if(!x->isLeaf()){
        for(int i=0; i<Letters; i++){
            if(x->next[i] != nullptr) st.push(x->next[i]);
        }
	}
	while(!st.empty()){
		x = st.top();
		st.pop();
		// if(t[x].endOfTheWord != -1) res.insert(t[x].endOfTheWord);
		if(!x->isLeaf()){
			for(int i=0; i<Letters; i++){
				if(x->next[i]!=nullptr){
                    st.push(x->next[i]);
                    x->next[i]= nullptr;
                }
			}
		}
        else{
            res.push_back(x->s);
        } 
	}
	return res;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  // vector<string> result;
  root t = new Node;
  build_tree(text, t);
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
