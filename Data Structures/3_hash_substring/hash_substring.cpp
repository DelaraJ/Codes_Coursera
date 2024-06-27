#include <bits/stdc++.h>

//compare two string
// way1:
// str_inp1 and str_inp2 are equal when strcmp(str_inp1, str_inp2)==0
// way2:
// res = str1.compare(str2); =>
// res == 0 -> are equal
// res < 0 -> str1 < str2
// res > 0 -> str1 > str2
// way3:
// str1 == str2 and str1 != str2



using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

unsigned long long x = 3, prime = 1e9+9;
Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

unsigned long long polyHash(const string& s, size_t x, size_t prime) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = ((hash * x)  % prime + s[i]) % prime;
    return hash;
}

vector<unsigned long long> precomputeHashes(const Data& input, size_t textSize, size_t patternSize) {
    vector<unsigned long long> H(textSize - patternSize +1);
    string s = input.text.substr(textSize-patternSize, patternSize);
    H[textSize-patternSize] = polyHash(s, x, prime);
    unsigned long long y = 1;
    for(int i=0; i<patternSize; i++){
        y= (y*x) % prime;
    }
    for(int i = textSize-patternSize-1; i>=0; i--){
        H[i] = (((x * H[i+1] + input.text[i]) % prime - (y * input.text[i+patternSize]) % prime) + prime) % prime;
    }
    return H;
}
bool AreEqual(string mainString, string pattern){
    if(mainString.size() != pattern.size()) return false;
    return mainString == pattern;
}

void print_occurrences(const vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
    size_t t = input.text.size(), p = input.pattern.size();
    vector<int> positions;
    unsigned long long patternHash  = polyHash(input.pattern, x, prime);
    vector<unsigned long long> H = precomputeHashes(input, t, p);
    for(size_t i =0; i< t-p+1; i++){
        if(patternHash != H[i]) continue;
        string check1= input.text.substr(i, p);
        if(AreEqual(check1, input.pattern))
            positions.push_back(i);
    }
    return positions;
}


int main() {
    ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
