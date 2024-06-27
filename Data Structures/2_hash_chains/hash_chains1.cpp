#include <bits/stdc++.h>

using namespace std;
struct Query {
    string type, s;
    long long ind;
};


class QueryProcessor {
    int bucket_count;
    static const int hashGroups=1000;
    vector<string> table[hashGroups];
    size_t hashFunction(const string& s) const {
        static const long long multiplier = 263;
        static const long long prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }
    void processQuery(const Query& query) {
        size_t hashedValue = hashFunction(query.s);
        if (query.type == "check") {
            auto cell = table[query.ind];
            while(cell.size()>0){
                cout<<cell.back() << " ";
                cell.pop_back();
            }
            cout<< endl;
        } else {
            if (query.type == "find"){
                bool found = false;
                for(size_t i = 0; i < table[hashedValue].size(); i++){
                    if(table[hashedValue].at(i) == query.s){
                        found = true;
                        break;
                    }
                }
                if(!found)cout << "no" << endl;
                else cout << "yes" << endl;
            }
                
            else if (query.type == "add") {
                bool found = false;
                for(size_t i = 0; i < table[hashedValue].size(); i++){
                    if(table[hashedValue].at(i) == query.s){
                        found = true;
                        break;
                    }
                }
                if(!found){
                    table[hashedValue].push_back(query.s);
                }
            } else if (query.type == "del") {
                for(size_t i = 0; i < table[hashedValue].size(); i++){
                if(table[hashedValue].at(i) == query.s){
                    table[hashedValue].erase(table[hashedValue].begin()+i);
                    break;
                }
                }
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }

};




int main() {
    ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
