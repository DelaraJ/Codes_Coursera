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
    int n, s, t;
    vector<vector<edge *>> graph;
    vector<int>visited;
    int is_visited = 0;
    long maxFlow=0;
    void initialize(int x){
        n=x;
        s =0;
        t = n-1;
        graph.resize(n);
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

    long dfs(int node, long flow){
        if(node == t) return flow;
        visited[node] = is_visited;
        for(auto& edge : graph[node]){
            if(edge->remainingeCpacity() > 0 && visited[edge->to] != is_visited){
                long bottleNeck = dfs(edge->to, min(flow, edge->remainingeCpacity()));

                if(bottleNeck > 0){
                    edge->augment(bottleNeck);
                    return bottleNeck;
                }
            }
        }
        return 0;
    }

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
            //     if(edge.second->to == t){
            //         pair<int, int> e = {x.first, t};
            //         long bottleNeck = x.second;
            //         while(e.first != -1){
                        
            //         }
            //     }
                if(edge->remainingeCpacity() > 0 && visited[edge->to] != is_visited){
                    visited[edge->to] = is_visited;
                    long tmp = min(x.second, edge->remainingeCpacity());
                    prev[edge->to] = edge;
                    q.push({edge->to, tmp});
                }
                
            }
        }
        if(prev[t] == nullptr) return 0;
        for(edge * edge = prev[t]; edge!= nullptr; edge = prev[edge->from]){
            edge->augment(bottleNeck);
        }
        return bottleNeck;

    }

    long solver(){
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
        return maxFlow;
    }

};



int main(){
    int n,m;
    cin>>n>>m;
    maxFlowSolver obj;
    obj.initialize(n);
    int s =0, t = n-1;
    for(int i=0; i<m; i++){
        int a,b;
        long c;
        cin>>a>>b>>c;
        obj.add_edge(a-1, b-1, c);
    }
    cout<<obj.solver()<<endl;
}