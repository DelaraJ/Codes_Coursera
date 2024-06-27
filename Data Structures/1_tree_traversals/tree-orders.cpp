#include <bits/stdc++.h>

using namespace std;

// struct Node{
//   int value;
//   Node *lchild;
//   Node *rchild;
//   Node(int val) {
//     value = val;
//     lchild=NULL;
//     rchild=NULL;
//   };
// };

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector <bool> stackAddedchecker;
  // vector<Node *> nodes;
public:
  void read();
  vector <int> in_order();
  void in_order_helper(int i);
  vector <int> pre_order();
  void pre_order_helper(int i);
  vector <int> post_order();
  void post_order_helper(int i);
};

void TreeOrders::read() {
  cin >> n;
  key.resize(n);
  left.resize(n);
  right.resize(n);
  // nodes.resize(n);
  // stackAddedchecker.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> key[i] >> left[i] >> right[i];
  }
  // for (int i = 0; i < n; i++) {
  //   nodes[i] = new Node(key[i], (left[i])? );
  // }
}
#pragma region 
vector <int> TreeOrders::in_order() {
  vector<int> result;
  stack<tuple<int, int , int>> stackTravers;
  in_order_helper(0);
  // int counter=0;
  // int x=0, y=0;
  // stackTravers.push(make_tuple(key[0], left[0], right[0]));
  // stackAddedchecker[0] =true;

  // while(counter<n)
  // {
  //   // int check = get<0>(stackTravers.top());
  //   // bool l = false, r=false;
  //   // if(get<1>(stackTravers.top())!=-1 && stackAddedchecker[get<1>(stackTravers.top())]!=true)l = true;
  //   // if(get<1>(stackTravers.top())==-1 || stackAddedchecker[get<1>(stackTravers.top())]==true){
  //   //   if(get<2>(stackTravers.top())!=-1 && stackAddedchecker[get<2>(stackTravers.top())]!=true) r= true;
  //   // }if(l){
  //   //   // stackAddedchecker[get<1>(stackTravers.top())] = true;//check left
  //   //   stackTravers.push(make_tuple(key[get<1>(stackTravers.top())], left[get<1>(stackTravers.top())], right[get<1>(stackTravers.top())])); 
  //   // }if(get<1>(stackTravers.top())==-1){
  //   //   stackAddedchecker[get<1>(stackTravers.top())] = true;//check left
  //   //   result.push_back(get<0>(stackTravers.top()));
  //   //   stackTravers.pop();
  //   //   counter ++;
  //   // }if(r){
  //   //   // stackAddedchecker[get<2>(stackTravers.top())] = true;//check right
  //   //   stackTravers.push(make_tuple(key[get<2>(stackTravers.top())], left[get<2>(stackTravers.top())], right[get<2>(stackTravers.top())])); 
  //   // }

  //   if(get<1>(stackTravers.top()) != -1 && stackAddedchecker[get<1>(stackTravers.top())] != true){
  //     x = get<1>(stackTravers.top());
  //     stackTravers.push(make_tuple(key[x], left[x], right[x]));
  //     stackAddedchecker[x] =true;
  //   }
  //   else{
  //     if(get<1>(stackTravers.top()) == -1) result.push_back(get<0>(stackTravers.top())), counter++;
  //     if(get<2>(stackTravers.top()) != -1 && stackAddedchecker[get<2>(stackTravers.top())] != true){
  //       x = get<2>(stackTravers.top());
  //       stackTravers.pop();
  //       stackTravers.push(make_tuple(key[x], left[x], right[x]));
  //       stackAddedchecker[x] =true;
  //     }
  //     else{
  //       if(get<2>(stackTravers.top()) == -1 && stackAddedchecker[x] != true){
  //         result.push_back(get<0>(stackTravers.top()));
  //         stackTravers.pop();
  //       }
  //     }
  //     // else if(get<1>(stackTravers.top()) == -1)  stackTravers.pop();
  //   }
  // }
  
  return result;
}
void TreeOrders::in_order_helper(int i) {
  if(left[i] != -1)   in_order_helper(left[i]);
  cout<< key[i] << ' ';
  if(right[i] != -1)  in_order_helper(right[i]);
}
#pragma endregion

#pragma region
vector <int> TreeOrders::pre_order() {
  vector<int> result;    
  pre_order_helper(0);
  return result;
}
void TreeOrders::pre_order_helper(int i){
  // res.push_back(key[i]);
  cout<< key[i] << ' ';
  if(left[i] != -1)  pre_order_helper(left[i]);
  if(right[i] != -1) pre_order_helper(right[i]);
}
#pragma endregion

#pragma region 
vector <int> TreeOrders::post_order() {
  vector<int> result;
  post_order_helper(0);
  return result;
}
void TreeOrders::post_order_helper(int i){
  if(left[i] != -1)  post_order_helper(left[i]);
  if(right[i] != -1) post_order_helper(right[i]);
  cout<< key[i] << ' ';
  // res.push_back(key[i]);
}
#pragma endregion

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main(){
  ios_base::sync_with_stdio(0);
  TreeOrders t;

  t.read();
  t.in_order_helper(0);
  cout << '\n';
  t.pre_order_helper(0);
  cout << '\n';
  t.post_order_helper(0);
  cout << '\n';
  return 0;
}

// int main (int argc, char **argv)
// {
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
//               std::cerr << "setrlimit returned result = " << result << std::endl;
//           }
//       }
//   }
// #endif

//   return main_with_large_stack_space();
// }

