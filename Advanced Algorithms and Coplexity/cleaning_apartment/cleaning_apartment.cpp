#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertHampathToSat {
    int numVertices;
    vector<set<int>> adj;
    vector<Edge> edges;
    vector<vector<bool>> v;
    vector<vector<int>> clauses;

    ConvertHampathToSat(int n, int m) : numVertices(n) { 
        adj.resize(n+1); 
        edges.resize(m);
        v.resize(n+1, vector<bool> (n+1, false));
    }

    void printEquisatisfiableSatFormula() {
        //n*n
        // cout<< numVertices + numVertices + (numVertices*numVertices*(numVertices-1))/2 + edges.size()*(numVertices-1)<<" " << numVertices * numVertices << endl;

        // Each vertex belongs to a path.
        for(int i=1; i<=numVertices * numVertices; i+=numVertices){
            vector<int> tmp;
            for(int j=i; j<numVertices+i; j++){
                tmp.push_back(j);
            }
            // tmp.push_back(0);
            clauses.push_back(tmp);
        }

        // Each position in a path is occupied by some vertex.
        for(int i=1; i<=numVertices; i++){
            vector<int> tmp;
            for(int j=i; j<=numVertices * numVertices; j+=numVertices){
                tmp.push_back(j);
            }
            // tmp.push_back(0);
            clauses.push_back(tmp);
        }

        //No two vertices occupy the same position of a path.
        for(int i=1; i<=numVertices * numVertices; i+=numVertices){
            for(int j=i; j<numVertices+i; j++){
                for(int k=j+numVertices; k<=numVertices * numVertices; k+=numVertices){
                    clauses.push_back({-j, -k});
                }
            }
        }

        // Each vertex appears just once in a path.
        for(int i=1; i<=numVertices * numVertices; i+=numVertices){
            for(int j=i; j<numVertices+i; j++){
                for(int k=j+1; k<numVertices+i; k++){
                    clauses.push_back({-j, -k});
                }
            }
        }

        // Two successive vertices on a path must be connected by an edge.
        // for(int i=1; i<= numVertices; i++){
        //     for(int j=1; j<=numVertices; j++){
        //         if(i==j) continue;
        //         if(adj[i].find(j) == adj[i].end()){
        //             if(!v[i][j] && !v[j][i]){
        //                 v[i][j]= true;
        //                 v[j][i]= true;
        //                 for(int k=1; k<numVertices; k++){
        //                     clauses.push_back({-((i-1)*numVertices+k), -((j-1)*numVertices+k+1)});
        //                 }
        //             }
        //         }
        //     }
        // }
        for (int i = 1; i <= numVertices; i++){
            for (int j=1; j <= numVertices;j++){
                if(!v[i][j]&& i!=j){
                    for (int k = 1; k < numVertices; k++)
                    {
                        clauses.push_back({-((i-1)*numVertices+k), -((j-1)*numVertices+k+1)});
                    }
                    
                }
            }     
        }
        // for(auto& e : edges){
        //     for(int k=1; k<numVertices; k++){
        //         cout<< -((e.from-1)*numVertices+k) <<" "<< -((e.to-1)*numVertices+k+1)  << " " << 0 <<endl;
        //     }
        // }
        cout<< clauses.size() << " " << numVertices* numVertices << endl;
        for(auto& c : clauses){
            for(auto& a : c){
                cout<<a << " ";
            }
            cout<< 0 << endl;
        }
        
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >>converter.edges[i].from>>converter.edges[i].to;
        converter.adj[converter.edges[i].from].insert(converter.edges[i].to);
        converter.v[converter.edges[i].from][converter.edges[i].to]=true;
        converter.v[converter.edges[i].to][converter.edges[i].from]=true;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
