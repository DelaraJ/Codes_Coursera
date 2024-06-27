#include <bits/stdc++.h>
// #include <sys/time.h>
// #include <sys/resource.h>
using namespace std;

struct Vertex {
    int weight;
    vector <int> children;
};
// typedef vector<Vertex> Graph;
typedef map<int, set<int>> Graph;
typedef vector<int> Weights;
typedef vector<int> Sum;

vector<int> D;
vector<bool> visited;
Graph tree;
Weights tree_weights;
void ReadTree() {
    int vertices_count;
    cin >> vertices_count;
    D.resize(vertices_count, INT32_MAX);
    visited.resize(vertices_count, false);
    // Graph tree(vertices_count);
    tree_weights.resize(vertices_count);
    for (int i = 0; i < vertices_count; ++i)
        cin >> tree_weights[i];

    for (int i = 1; i < vertices_count; ++i) {
        int from, to;
        cin >> from >> to;
        tree[from - 1].insert(to - 1);
        tree[to - 1].insert(from - 1);
    }
    // return tree;
}

// void dfs(const Graph &tree, int vertex, int parent) {
//     for (int child : tree[vertex].children)
//         if (child != parent)
//             dfs(tree, child, vertex);

//     // This is a template function for processing a tree using depth-first search.
//     // Write your code here.
//     // You may need to add more parameters to this function for child processing.
// }



// int MaxWeightIndependentTreeSubset(const Graph &tree) {
//     size_t size = tree.size();
//     if (size == 0)
//         return 0;
//     dfs(tree, 0, -1);
//     // You must decide what to return.
//     return 0;
// }

void delete_useless_edges(int parent = -1, int v = 0){
    if(tree[v].find(parent) != tree[v].end()){
        tree[v].erase(parent);
    }
    if(tree[v].size() == 0) return;
    for(auto &a : tree[v]){
        delete_useless_edges(v, a);
    }
}

int FunParty(int v, Graph &tree, int parent = -1){
    if(D[v] == INT32_MAX){
        // visited[v] = true;
        if(tree[v].size()==0){
            D[v] = tree_weights[v];
        }
        else{
            int m1 = tree_weights[v];
            for(auto &a: tree[v]){
                // if(!visited[a]){
                    for(auto& b: tree[a]){
                        if(/*!visited[b] &&*/ b != v) 
                            m1+= FunParty(b, tree, v);
                    }

                // }
            }
            // for(int i=0; i<one; i++){
            //     int two = tree[tree[v].children[i]].children.size();
            //     for(int j=0; j<two; j++){
            //         if(tree[v].children[j] != tree[v].children[i])
            //         m1+= FunParty(tree[v].children[j], tree);
            //     }
            // }
            int m0 = 0;
            for(auto &a: tree[v]){
                if(a != parent) m0+=FunParty(a, tree, v);
            }
            D[v] = max(m0, m1);
        }
        // visited[v] = false;
    }
    return D[v];
}

int main() {
    // // This code is here to increase the stack size to avoid stack overflow
    // // in depth-first search.
    // const rlimit_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    // struct rlimit rl;
    // int result;
    // result = getrlimit(RLIMIT_STACK, &rl);
    // if (result == 0)
    // {
    //     if (rl.rlim_cur < kStackSize)
    //     {
    //         rl.rlim_cur = kStackSize;
    //         result = setrlimit(RLIMIT_STACK, &rl);
    //         if (result != 0)
    //         {
    //             fprintf(stderr, "setrlimit returned result = %d\n", result);
    //         }
    //     }
    // }

    // Here begins the solution
    ReadTree();
    delete_useless_edges();
    int weight = FunParty(0, tree);
    cout << weight << endl;
    return 0;
}
