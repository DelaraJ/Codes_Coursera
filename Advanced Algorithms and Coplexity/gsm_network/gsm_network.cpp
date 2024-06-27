#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices, numEdges;
    vector<Edge> edges;
    vector<int> nodeColors;
    ConvertGSMNetworkProblemToSat(int n, int m) : numVertices(n), numEdges(m){  
        nodeColors.resize(n, -1);
        edges.resize(m);
    }

    // bool check(){
    //     //tr
    //     for(int i=0; i<numEdges; i++){
    //         if(nodeColors[edges[i].from] == -1){//not visited
    //             if(nodeColors[edges[i].to] != 0) nodeColors[edges[i].from] =0;
    //             else if(nodeColors[edges[i].to] != 1) nodeColors[edges[i].from] =1;
    //             else if(nodeColors[edges[i].to] != 2) nodeColors[edges[i].from] =2;
    //         }
    //         if(nodeColors[edges[i].to] == -1){//not visited
    //             if(nodeColors[edges[i].from] != 0) nodeColors[edges[i].to] =0;
    //             else if(nodeColors[edges[i].from] != 1) nodeColors[edges[i].to] =1;
    //             else if(nodeColors[edges[i].from] != 2) nodeColors[edges[i].to] =2;
    //         }
    //     }
    //     for(int i=0; i<numEdges; i++){
    //         if(nodeColors[edges[i].from] == nodeColors[edges[i].to]) return false;
    //     }
    //     return true;

    // }

    void printEquisatisfiableSatFormula() {
        vector<vector<int>> cluases;
        //one state has just one color
        // for(int i=0; i<numVertices*3; i+=3){
        //     vector<int> tmp(numVertices*3+1, 0);
        //     tmp[i] = -1;
        //     tmp[i+1] = -1;
        //     cluases.push_back(tmp);
        //     tmp[i] = 0;
        //     // tmp[i+1] = 0;

        //     // tmp[i+1] = -1;
        //     tmp[i+2] = -1;
        //     cluases.push_back(tmp);
        //     // tmp[i+2] = 0;
        //     tmp[i+1] = 0;


        //     tmp[i] = -1;
        //     // tmp[i+2] = -1;
        //     cluases.push_back(tmp);
        //     // tmp[i] = 0;
        //     // tmp[i+1] = 0;
        // }
        // //one state has at least one color
        // for(int i=0; i<numVertices*3; i+=3){
        //     vector<int> tmp(numVertices*3+1, 0);
        //     tmp[i] = 1;
        //     tmp[i+1] = 1;
        //     tmp[i+2] = 1;
        //     cluases.push_back(tmp);
        // }


        // //one edge with two colors
        // for(auto& e : edges){
        //     for(int j=0; j<3; j++){
        //         vector<int> tmp(numVertices*3+1, 0);
        //         tmp[(e.from-1) *3 + j] = -1;
        //         tmp[(e.to-1) *3 + j] = -1;
        //         cluases.push_back(tmp);
        //     }
        // }
        cout<< numEdges*3 + numVertices*3 + numVertices<< " " << 3*numVertices << endl;

        //one state has at least one color
        for(int i=1; i<=numVertices*3; i+=3){
            cout<< i<< " "<< i+1<< " "<< i+2<< " "<< 0 << endl;
        }

        //one edge with two colors
        for(auto& e : edges){
            for(int j=1; j<=3; j++){
                cout << -((e.from-1) *3 + j) << " " << -((e.to-1) *3 + j) << " " << 0 << endl;
            }
        }

        for(int i=1; i<=numVertices*3; i+=3){
            cout<< -i << " " << -(i+1) << " " << 0 << endl;
            cout<< -i << " " << -(i+2) << " " << 0 << endl;
            cout<< -(i+1) << " " << -(i+2) << " " << 0 << endl;
            
        }

    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
