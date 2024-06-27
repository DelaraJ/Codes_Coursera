#include <bits/stdc++.h>
using namespace std;

bool comparer(tuple<int, int, int> a, tuple<int, int, int> b){
    return (get<2>(a)>get<2>(b));
}

int Clock=1;
void dfs_with_pre_post_order(vector<tuple<int, int, int>> &prepost,
                            vector<set<int>> &adj, 
                            vector<bool> &visited, int x){
    visited[x] = true;
    get<0>(prepost[x]) = x;
    get<1>(prepost[x]) = Clock;
    Clock++;
    for(int i : adj[x]){
        if(!visited[i]) dfs_with_pre_post_order(prepost, adj, visited, i);
    }
    get<2>(prepost[x]) = Clock;
    Clock++;
}

void Explore(vector<set<int>> &adj, vector<int> &visit, int x, int j){
    visit[x] = j;
    for(int i : adj[x]){
        if(visit[i] == -1) Explore(adj, visit, i, j);
    }
}

pair<int, vector<int>> strongly_connected_components(vector<set<int> > adj, vector<set<int> > rGraph) {
    int n= adj.size();
    vector<tuple<int, int, int>> prepost(n, tuple<int,int,int>(INT32_MAX, INT32_MAX, INT32_MAX));
    vector<bool> visited(n, false);
    // visited[0] = true;
    // visited[1] = true;
    for(int i=0; i< n; i++){
        if(!visited[i]) dfs_with_pre_post_order(prepost, rGraph, visited, i);
    }
    vector<int> visit(n, -1);
    int x=0;
    sort(prepost.begin(), prepost.end(), comparer);
    for(int i=0; i<n; i++){
        if(visit[get<0>(prepost[i])] == -1){
            Explore(adj, visit, get<0>(prepost[i]), x);
            x++;
        }
    }
    return {x, visit};
}

struct Clause {
    int firstVar;
    int secondVar;
};

class TwoSatisfiability {
    public:
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m) :
        numVars(n)
    { 
        clauses.resize(m);
    }

    

    void make_graph(int n, vector<set<int>>& graph, vector<set<int>>& rgraph){
        for(auto& cl : clauses){
            int firstvar, notfirstvar;
            if(cl.firstVar > 0){
                firstvar =  cl.firstVar*2;
                notfirstvar =  cl.firstVar*2 +1;
            }
            else{
                notfirstvar = abs(cl.firstVar) * 2;
                firstvar = abs(cl.firstVar) * 2 + 1;
            }
            int secondvar, notsecondvar;
            if(cl.secondVar > 0){
                secondvar =  cl.secondVar*2;
                notsecondvar =  cl.secondVar*2 +1;
            }
            else{
                notsecondvar = abs(cl.secondVar) * 2;
                secondvar = abs(cl.secondVar) * 2 + 1;
            }
            graph[notfirstvar].insert(secondvar);
            graph[notsecondvar].insert(firstvar);

            rgraph[secondvar].insert(notfirstvar);
            rgraph[firstvar].insert(notsecondvar);
        }
    }

    bool isSatisfiable(vector<int>& result) {
        int bound = 2*numVars+2;
        vector<set<int>> graph(bound);
        vector<set<int>> rgraph(bound);
        make_graph(numVars, graph, rgraph);
        pair<int, vector<int>> sccs = strongly_connected_components(graph, rgraph);
        vector<int> twoSAT(bound, -1);
        vector<vector<int>> SCC(sccs.first, vector<int>());
        for(int i=2; i<sccs.second.size(); i+=2){
            if(sccs.second[i] == sccs.second[i+1]) return false;
            SCC[sccs.second[i]].push_back(i);
            SCC[sccs.second[i+1]].push_back(i+1);
        }
        for(int i=0; i<sccs.first; i++){
            for(int a : SCC[sccs.first-1-i]){
                if(a == -1) continue;
                if(twoSAT[a] == -1){
                    twoSAT[a] = 1;
                    if(a%2 == 0) twoSAT[a+1] = 0;
                    else twoSAT[a-1] = 0;
                }
            }
        }
        for(int i =0; i<numVars; i++){
            result[i] = twoSAT[(i+1)*2];
        }
        return true;
    }

};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
        // if(twoSat.clauses[i].firstVar>0) twoSat.clauses[i].firstVar--;
        // else twoSat.clauses[i].firstVar++;
        // if(twoSat.clauses[i].secondVar>0) twoSat.clauses[i].secondVar--;
        // else twoSat.clauses[i].secondVar++;
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
