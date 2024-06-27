#include <bits/stdc++.h>
#define int long long
using namespace std;

class HashTable
{
    private:
        int p=1e7+19;
        int a = rand()%p, b = rand()%p;
        static const int hashGroups=1000;
        list<pair<int, string>> table[hashGroups];

    public:
        bool isEmpty();
        int hashFunction(int key);
        void Add(int key, string value);
        void Del(int key);
        string Find(int key);
};
bool HashTable::isEmpty() {
    int sum=0;
    for(int i=0; i<hashGroups; i++)
    sum += table[i].size();
    return (sum==0);
}

int HashTable::hashFunction(int key) {
    return (a*key + b)%p %hashGroups;
}

void HashTable::Add(int key, string value){
    int hashedValue = hashFunction(key);
    bool found = false;
    list<pair<int, string>>& cell = table[hashedValue];
    for(auto It = cell.begin(); It!=cell.end(); It++){
        if(It->first == key){
            found = true;
            It->second = value;
            break;
        }
    }
    if(!found){
        cell.emplace_back(key, value); 
    }
    return;
}

void HashTable::Del(int key){
    int hashedValue = hashFunction(key);
    list<pair<int, string>>& cell = table[hashedValue];
    for(auto It = cell.begin(); It!=cell.end(); It++){
        if(It->first == key){
            It = cell.erase(It);
            break;
        }
    }
    return;
}

string HashTable::Find(int key){
    int hashedValue = hashFunction(key);
    auto& cell = table[hashedValue];
    for(auto It = cell.begin(); It!=cell.end(); It++){
        if(It->first == key) return It->second;
    }
    return "not found";
}

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    HashTable contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            contacts.Add(queries[i].number, queries[i].name);
        } else if (queries[i].type == "del") {
            contacts.Del(queries[i].number);
        } else {
            result.push_back(contacts.Find(queries[i].number));
        }
    return result;
}

int32_t main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
