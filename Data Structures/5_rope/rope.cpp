#include <bits/stdc++.h>
using namespace std;
#define COUNT 10
struct Vertex {
  char key;
  int sum;
  int rightnodes, leftnodes;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, int sum, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), sum(sum), left(left), right(right), parent(parent) {rightnodes=0; leftnodes=0;}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->leftnodes = v->left? v->left->sum:0ll;
  v->rightnodes = v->right?  v->right->sum : 0ll;
  v->sum = (v->leftnodes) + (v->rightnodes) + 1; 
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
    
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}
void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

Vertex* find(Vertex*& root, int index) {
  Vertex* v = root;
  Vertex* last = root;
  Vertex* next = NULL;
  while (v != NULL) {
    if (v->leftnodes +1 >= index && (next == NULL || v->sum-(v->leftnodes +1) < next->sum)) {
      next = v;
    }
    last = v;
    if (v->leftnodes +1 == index) {
      break;      
    }
    if (v->leftnodes +1 < index) {
      index -= (v->leftnodes +1);
      v = v->right;
    } else {
      v = v->left;
    }
  }
  splay(root, v);
  return v;
}
void split(Vertex* root, int i, Vertex*& left, Vertex*& right) {
  right = find(root, i);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right, *helper = left;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

Vertex* root = NULL;
void insert(int index, char x) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  split(root, index+1, left, right);
  new_vertex = new Vertex(x, 1, NULL, NULL, NULL);
  root = merge(root, new_vertex);
}

class Rope {
	string s;
public:
	Rope(const string &s) : s(s) {
  Vertex* new_vertex = NULL, *helper;
    for(int i=0; i<s.size(); i++){
			insert(i, s[i]);
		}
	}

	void process( int i, int j, int k ) {
		Vertex *left, *middle, *right, *ans;
    i++;j++;k++;
    split(root, i, left, right);
		split(right, j-i+2, middle, right);
		ans = merge(left, right);
		split(ans, k, left, right);
		root = merge(merge(left, middle), right);
	}
	void processForStressTests( int i, int j, int k ) {
                // Replace this code with a faster implementation
                string t = s.substr(0, i) + s.substr(j + 1);
                s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
	}

void inOrderTraversal(vector<char> &ans, Vertex* v)
{
    stack<Vertex*> s;
    Vertex* current = v;
 
    while (current != NULL || !s.empty()) {
        while (current != NULL) {

            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        ans.push_back(current->key);
        current = current->right;
 
    }
}


	string result() {
		vector<char> ans;
		inOrderTraversal(ans, root);
		for(int i=0; i< ans.size(); i++) s[i] = ans[i];
		return s;
	}
};

void print2DUtil(Vertex* v, int space)
{
  if (v == NULL)
      return;
  space += COUNT;
  print2DUtil(v->right, space);
  cout << endl;
  for (int i = COUNT; i < space; i++)
      cout << " ";
  cout << v->key <<"," <<v->sum << "\n";
  print2DUtil(v->left, space);
}
void print2D(Vertex* v)
{
  print2DUtil(v, 0);
}

string rope(string query, vector<vector<int>> l){
  Rope r(query);
  for (int action_index = 0; action_index < l.size(); ++action_index) {
		r.process(l[action_index][0], l[action_index][1], l[action_index][2]);
  }
  cout<< r.result()<<endl;
  return r.result();
}

void sample() {
        assert(rope("hlelowrold", {{1, 1, 2},
                                  {6, 6, 7}}) == "helloworld");

        assert(rope("abcdef", {{0, 1, 1},
                              {4, 5, 0}}) == "efcabd");

        assert(rope("abcdef", {{0, 0, 5},
                              {4, 4, 5},
                              {5, 5, 0}}) == "fbcdea");

        assert(rope("dtaa", {{1, 1, 2}}) == "data");

        assert(rope("a", {{0, 0, 0}}) == "a");

        assert(rope("vfortetohegreatalbaniaforyou", {{7, 7, 1},
                                                    {2, 4, 4}}) == "voteforthegreatalbaniaforyou");

        assert(rope("vfortetoheugreatalbaniaforyo", {{7,  7,  1},
                                                    {2,  4,  4},
                                                    {11, 27, 10}}) == "voteforthegreatalbaniaforyou");

        assert(rope("greatalbaniaforyouvfortetohe", {{0, 17, 10},
                                                    {7, 7,  1},
                                                    {2, 4,  4}}) == "voteforthegreatalbaniaforyou");

        assert(rope("voteforthegreatalbaniaforyou", {{0, 27, 0}}) == "voteforthegreatalbaniaforyou");

        assert(rope("voteforthegreatalbaniaforyou", {{0, 0, 0}}) == "voteforthegreatalbaniaforyou");

        // assert(rope("voteforthegreatalbaniaforyou", {{0, 27, 27}}) == "voteforthegreatalbaniaforyou");

        assert(rope("uvoteforthegreatalbaniaforyo", {{0, 0, 27}}) == "voteforthegreatalbaniaforyou");

        assert(rope("uvoteforthegreatalbaniaforyo", {{1, 27, 0}}) == "voteforthegreatalbaniaforyou");

        assert(rope("uvoteforthegreatalbaniaforyo", {{1, 27, 1}}) == "uvoteforthegreatalbaniaforyo");

        assert(rope("voteforthegreatalbaniaforyou", {{27, 27, 27}}) == "voteforthegreatalbaniaforyou");

        assert(rope("abcdef", {{5, 5, 4},
                              {4, 5, 3},
                              {3, 5, 2},
                              {2, 5, 1},
                              {1, 5, 0},
                              {0, 0, 1},
                              {0, 1, 1},
                              {0, 2, 1},
                              {0, 3, 1},
                              {0, 4, 1}}) == "abcdef");
    }


int main() {
	ios_base::sync_with_stdio(0);
  // sample();
	string s;
	cin >> s;
	Rope rope(s);
	int actions;
    // print2D(root);
	cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		cin >> i >> j >> k;
		rope.process(i, j, k);
    // print2D(root);
    }
	cout << rope.result() << endl;
}


