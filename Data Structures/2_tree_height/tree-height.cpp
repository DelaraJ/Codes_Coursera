#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif


using namespace std;
class Node;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;
    Node() {this->parent = NULL;}

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int findHeightByBFS(Node* root)
{
  
  int height=0;
  if(root==NULL) return 0;
  queue<pair<Node *, int>> q;
  q.push({root, 0});
  vector<int> check;
  int tr=0;
  while(!q.empty())
  {
    
    pair<Node *, int> tmp = q.front();
    height=q.front().second;
    q.pop();
    for(int i=0; i<tmp.first->children.size(); i++)
    {
      q.push({tmp.first->children[i], tmp.second+1});
    }
  }
  return  height+1;
}

// int exactHeight(vector<Node *> nodes, int n)
// {
//   int maxHeight = 0;
//   for (int leaf_index = 0; leaf_index < n; leaf_index++) {
//     int height = 0;
//     for (Node *v = nodes[leaf_index]; v != NULL; v = v->parent)
//       height++;
//     maxHeight = max(maxHeight, height);
//   }
//   return maxHeight;
// }


// void test()
// {

// for(int k =0; k<=99; k++)
// {
//   Node *root = new Node();
//   root -> key = rand()% 10000;

//   vector<Node *> nodes;
//   nodes.push_back(root);

//   while(nodes.size() < 10000)
//   {
//     // Choose a random node
//     int index = rand() % nodes.size();
//     Node *node = nodes[index];
//     // Create a new node with a random key
//     Node *child = new Node();
//     child->key = rand() % 10000;
//     // Set the new node's parent to the chosen node
//     child->setParent(node);
//     // Add the new node to the list of nodes
//     nodes.push_back(child);
//   }
//   int correctAns = exactHeight(nodes, 10000);
//   int check = findHeightByBFS(root);
//   if(correctAns!=check) cout<<"Wrong Answer :"<<check<<' '<<correctAns<<"\n";
//   // else cout<<"OK\n";

//   for (int i = 0; i < nodes.size(); i++) {
//         delete nodes[i];
//     }
// }
// }


int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  vector<Node> nodes;
  nodes.resize(n);
  int root;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else root = child_index;
    nodes[child_index].key = child_index;
  }
  cout<<findHeightByBFS(&nodes[root])<<endl;
  return 0;
}

// int main (int argc, char **argv)
// {
//   return main_with_large_stack_space();
//   // test();
// #if defined(__unix__) || defined(__APPLE__)
//   // Allow larger stack space
//   const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
//   struct rlimit rl;
//   int result;

//   result = getrlimit(RLIMIT_STACK, &rl);
//   if (result == 0)
//   {
//       if (rl.rlim_cur < kStackSize)
//       {
//           rl.rlim_cur = kStackSize;
//           result = setrlimit(RLIMIT_STACK, &rl);
//           if (result != 0)
//           {
//               cerr << "setrlimit returned result = " << result << endl;
//           }
//       }
//   }

// #endif
// }
