#include <bits/stdc++.h>

using namespace std;

int const Letters =    6;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	int parent = -1;
	int endOfTheWord = NA;
	string s;
	string sign = "Leaf";
	Node ()
	{
		fill (next, next + Letters, NA);
	}
  bool isLeaf(){
    return next[0]==NA && next[1]==NA && next[2]==NA && next[3]==NA && next[4]==NA && next[5]==NA;
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
		case '#': return 5; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> tree;

void make_new_essential_node(tree& t, int &last_index, int& x, string Text, int index, int start_index){
  last_index++;
  t[x].next[letterToIndex(Text[index])] = last_index;
  t.push_back(Node());
  t[last_index].parent = x;
  x= last_index;
  t[x].s = Text.substr(index);
  t[x].endOfTheWord = start_index;
}

void make_middle_node(tree& t, int &last_index, int& x,const string& Text, int index, int suffix_index, string suffix){
  last_index++;
  t.push_back(Node());
  for(int j =0; j<Letters; j++){
    t[last_index].next[j] = t[x].next[j];
	t[t[x].next[j]].parent = last_index;
    t[x].next[j] = -1;
  }
  t[x].next[letterToIndex(t[x].s[suffix_index])] = last_index;
  t[last_index].parent = x;
  t[last_index].s = t[x].s.substr(suffix_index);

  t[x].s = t[x].s.substr(0, suffix_index);
  
  last_index++;
  t[x].next[letterToIndex(Text[index])] = last_index;
  t.push_back(Node());
  t[last_index].parent = x;
  t[last_index].s = Text.substr(index);
}

void root_swiching(int& x, tree& t, const string &Text, int& index, string& suffix, int& suffix_index){
  x = t[x].next[letterToIndex(Text[index])];
  suffix = t[x].s;
  suffix_index =0;
}

tree build_tree(const string& first_text, const string& second_text) {
  tree t;
  t.push_back(Node());
  int last_index = 0;
  //build tree from first_text
  int first_textLength = first_text.size();
  for(int i=0; i< first_textLength; i++){
	  int index = i;
    int x = 0;
    if(t[x].next[letterToIndex(first_text[index])] != NA){
      x = t[x].next[letterToIndex(first_text[index])];
      string suffix =t[x].s;
      int suffix_index = 0;
      while(index < first_textLength){
        if(suffix_index < t[x].s.size() && first_text[index] != suffix[suffix_index]){
          make_middle_node(t,last_index, x, first_text, index, suffix_index, suffix);
          break;
        }
        else if(suffix_index >= t[x].s.size()){
          if(t[x].next[letterToIndex(first_text[index])] != NA){ //node switch
            root_swiching(x, t, first_text, index, suffix, suffix_index);
          }
          else{//nahamahangi
            make_new_essential_node(t, last_index, x, first_text, index, i);
            break;
          }

        }
        suffix_index++;
        index++;
	  }
    }
    else if(t[x].next[letterToIndex(first_text[index])] == NA){
      make_new_essential_node(t, last_index, x, first_text, index, i);
    }
  }

  //build tree from second_text
  int second_textLength = second_text.size();
  for(int i=0; i< second_textLength; i++){
	int index = i;
    int x = 0;
    if(t[x].next[letterToIndex(second_text[index])] != NA){
      x = t[x].next[letterToIndex(second_text[index])];
      string suffix =t[x].s;
      int suffix_index = 0;
      while(index < second_textLength){
        if(suffix_index < t[x].s.size() && second_text[index] != suffix[suffix_index]){
          make_middle_node(t,last_index, x, second_text, index, suffix_index, suffix);
          break;
        }
        else if(suffix_index >= t[x].s.size()){
          if(t[x].next[letterToIndex(second_text[index])] != NA){ //node switch
            root_swiching(x, t, second_text, index, suffix, suffix_index);
          }
          else{//nahamahangi
            make_new_essential_node(t, last_index, x, second_text, index, i+ first_textLength);
            break;
          }

        }
        suffix_index++;
        index++;
	  }
    }
    else if(t[x].next[letterToIndex(second_text[index])] == NA){
      make_new_essential_node(t, last_index, x, second_text, index, i+ first_textLength);
    }
  }


  return t;
}


void dfs(tree& t, int first_textLength, int second_textLength, vector<bool>& visited, int x, set<int>& ans_condidate){
  if(visited[x]) return;
  visited[x] = true;
  for(int i=0; i<Letters; i++){
  	if(t[x].next[i]!=-1 && !visited[t[x].next[i]]){
  		dfs(t, first_textLength, second_textLength, visited, t[x].next[i], ans_condidate);
  	}
  }
	bool first= false, second= false;
		if(t[x].isLeaf()){
			if(t[x].endOfTheWord < first_textLength){
        t[x].sign = "X";
        if(t[x].s != "#") ans_condidate.insert(x);
      }
			else t[x].sign = "Y";
		}
		else{
			for(int i=0; i<Letters; i++){
				if(t[x].next[i]!=-1){
					if(t[t[x].next[i]].sign == "X") first = true;
					else second = true;
				}
			}
			if(first && second) t[x].sign = "XY";
			else if(first){
        t[x].sign = "X";
        ans_condidate.insert(x);
      }
			else t[x].sign = "Y";
			first = second = false;
		}
}

void initial_dfs(tree& t, int first_textLength, int second_textLength, set<int>& ans_condidate){
  vector<bool> visited(t.size() , false);
  dfs(t, first_textLength, second_textLength, visited, 0, ans_condidate);
}

void bfs(tree& t, string& result){
	queue<int> Q;
	Q.push(0);
	int x=0;
	while(!Q.empty()){
		x = Q.front();
		Q.pop();
		if(t[x].s == "#") continue;
		if(t[x].sign == "X"){
			while(t[x].parent != -1){
				result = t[x].s + result;
				x = t[x].parent;
			}
			break;
		}
		if(!t[x].isLeaf()){
			for(int i=0; i<Letters; i++){
				if(t[x].next[i]!=-1){
					Q.push(t[x].next[i]);
				}
			}
		}
	}
}

string making_answer(tree& t, set<int>& ans_condidate){
  vector<bool> visited(t.size(), false);
  // vector<string> anss;
  string ans = "";
  int min = INT32_MAX, index = -1;
  for(int a : ans_condidate){
    if(visited[t[a].parent] == true) continue;
    string s="";
    int aa=a;
    if(t[aa].parent!=-1){
      if(t[aa].s[t[aa].s.size()-1] != '#') s=t[aa].s + s;
      else s=t[aa].s[0] + s;
      aa= t[aa].parent;
    }
    while(t[aa].parent!=-1){
      s=t[aa].s + s;
      aa= t[aa].parent; 
    }
    // anss.push_back()
    if(s.size()<min){
      min = s.size();
      index = a;
      ans = s;
    }
    visited[a]=true;
  }
  return ans;
}


string solve (string p, string q)
{
  set<int> ans_condidate;
	string result = "";
	tree t = build_tree(p, q);
	initial_dfs(t, p.size(), q.size(), ans_condidate);
	// bfs(t, result);
	// return  (result[result.size()-1] == '#' || result[result.size()-1] == '$')? result.substr(0, result.size()-1) : result;
  return making_answer(t, ans_condidate);
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p+'#', q+'$');

	cout << ans << endl;

	return 0;
}
