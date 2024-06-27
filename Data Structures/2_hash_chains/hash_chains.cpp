#include <bits/stdc++.h>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    map<int, list<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1e9+7;
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

    bool find(const Query& query, size_t hashedVal){
        bool was_found = false;
        for (auto It = elems[hashedVal].begin(); It != elems[hashedVal].end(); It++){
            if(*It == query.s){
                was_found = true;
                break;
            }
        }
        return was_found;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        size_t hashedVal = hash_func(query.s);
        if (query.type == "check") {
            for (auto It = elems[query.ind].begin(); It != elems[query.ind].end(); It++)
                cout << *It << " ";
            cout << "\n";
        } else {
            if (query.type == "find"){
                if(find(query, hashedVal)) cout<< "yes" << endl;
                else cout<< "no" <<endl;
            }else if (query.type == "add") {
                if(!find(query, hashedVal)) elems[hashedVal].emplace_front(query.s);
            } else if (query.type == "del") {
                for (auto It = elems[hashedVal].begin(); It != elems[hashedVal].end(); It++)
                    if(*It == query.s) It = elems[hashedVal].erase(It);
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
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
