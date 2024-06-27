#include <bits/stdc++.h>
using namespace std;

class edge{
public:
    int from, to;
    long flow, capacity;
    edge * residual;
    edge(int _from, int _to, int _capacity) :
    from(_from), to(_to), capacity(_capacity), flow(0){}
    edge(){}
    bool isResidual(){
        return capacity==0;
    }
    long remainingeCpacity(){
        return capacity - flow;
    }
    void augment(long bottleNeck){
        flow += bottleNeck;
        residual->flow -= bottleNeck;
    }
};


class maxFlowSolver{
    public:
    int n, s, t, flight, crew;
    vector<vector<edge *>> graph;
    vector<int> ans;
    vector<int>visited;
    int is_visited = 0;
    long maxFlow=0;
    void initialize(int x, int f, int c){
        n=x;
        s =0;
        t = n-1;
        flight = f;
        crew = c;
        graph.resize(n);
        ans.resize(flight,-1);
        visited.resize(n, -1);
    }
    void add_edge(int f, int t, long c){
        edge * e1 = new edge(f,t,c);
        edge * e2 = new edge(t,f,0);
        e1->residual = e2;
        e2->residual = e1;
        graph[f].push_back(e1);
        graph[t].push_back(e2);
    }

    // long dfs(int node, long flow){
    //     if(node == t) return flow;
    //     visited[node] = is_visited;
    //     for(auto& edge : graph[node]){
    //         if(edge->remainingeCpacity() > 0 && visited[edge->to] != is_visited){
    //             long bottleNeck = dfs(edge->to, min(flow, edge->remainingeCpacity()));

    //             if(bottleNeck > 0){
    //                 if(edge->to == t){

    //                 }
    //                 edge->augment(bottleNeck);
    //                 return bottleNeck;
    //             }
    //         }
    //     }
    //     return 0;
    // }

    long bfs(int node, long flow){
        if(node == t) return flow;
        queue<pair<int, long>> q;
        visited[node] = is_visited;
        q.push({node, flow});
        vector<edge*> prev(n, nullptr);
        long bottleNeck = 0;
        while(!q.empty()){
            auto x = q.front();
            q.pop();
            if(x.first == t){
                bottleNeck = x.second;
                break;
            }
            for(auto& edge : graph[x.first]){
                if(edge->remainingeCpacity() > 0 && visited[edge->to] != is_visited){
                    visited[edge->to] = is_visited;
                    long tmp = min(x.second, edge->remainingeCpacity());
                    prev[edge->to] = edge;
                    q.push({edge->to, tmp});
                }
                
            }
        }
        if(prev[t] == nullptr) return 0;
        // int mustPush = prev[t]->from - flight;
        // bool found = false;
        for(edge * edge = prev[t]; edge!= nullptr; edge = prev[edge->from]){
            // if(!found && prev[edge->from]->from == s){
            //     ans[edge->from -1] = mustPush;
            //     found = true;
            // }
            edge->augment(bottleNeck);
        }
        return bottleNeck;

    }

    vector<int> solver(){
        // long tmp = dfs(s, LONG_MAX);
        // while(tmp!=0){
        //     is_visited++;
        //     maxFlow+= tmp;
        //     tmp = dfs(s, LONG_MAX);
        // }
        // return maxFlow;
        long tmp = bfs(s, LONG_MAX);
        while(tmp!=0){
            is_visited++;
            maxFlow+= tmp;
            tmp = bfs(s, LONG_MAX);;
        }
        for(int i =0; i<flight; i++){
            for(auto& edge : graph[i+1]){
                if(edge->flow == 1){
                    ans[i] = edge->to - flight;
                    break;
                }
            }
        }
        return ans;
    }

};



int main(){
    int f,c;
    cin>>f>>c;
    maxFlowSolver obj;
    obj.initialize(f+c+2, f, c);

    int t = f+c+1, s=0;
    for(int i=1; i<=f; i++){
        obj.add_edge(s, i, 1);
        for(int j=1+f; j<=c+f; j++){
            int a;
            cin>>a;
            if(a==1) obj.add_edge(i, j, 1);
        }
    }
    for(int j=1+f; j<=c+f; j++){
        obj.add_edge(j, t, 1);
    }
    vector<int> ans = obj.solver();
    for(int i : ans){
        cout<< i <<" ";
    }
}