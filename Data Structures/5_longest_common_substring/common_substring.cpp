#include <bits/stdc++.h>

using namespace std;

struct Answer {
	long long i, j, len;
};

// vector<long long> precomputehashes(string input)
// {
// 	long long prime = 1e12 + 39, x = 35;
// 	vector <long long> H(input.size() + 1);
// 	H[0] = 0;
// 	for(int i=1; i<=input.size(); i++){
// 		H[i] = ((x* H[i-1]) %prime + input[i-1]) %prime;	
// 	}
// 	return H;
// }

vector<long long> calculatePowers(long long n){
	long long x = 35, mod = 1e12+39;
	vector<long long> p(n+1);
	p[0]=1;
	for(long long i=1; i<=n; i++){
		p[i]=(p[i-1]*x) % mod;
	}
	return p;
}

unsigned long long polyHash(const string& s, long long x, long long prime) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = ((hash * x)  % prime + s[i]) % prime;
    return hash;
}

vector<long long> precomputeHashes(const string& input, long long patternSize) {
	long long textSize = input.size();
    vector<long long> H(textSize - patternSize +1);
    string s = input.substr(textSize-patternSize, patternSize);
	long long prime = 1e12 + 39;
	long long x = 35;

    H[textSize-patternSize] = polyHash(s, x, prime);
    long long y = 1;
    for(int i=0; i<patternSize; i++){
        y= (y*x) % prime;
    }
    for(int i = textSize-patternSize-1; i>=0; i--){
		long long a = (x * H[i+1])%prime;
		long long b = (y * input[i+patternSize]) % prime;
        H[i] = ((a + input[i] - b) + prime) % prime;
    }
    return H;
}

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	int left=0, right = (min(s.size(), t.size()));
	int mid= (left + right) /2;
	unsigned long long prime = 1e12 + 39;
	while(left <= right){
		bool wasfound=false;
		mid = (left + right) /2;
		vector<long long> Hs = precomputeHashes(s, mid), Ht = precomputeHashes(t, mid);
		unordered_map<long long, int> umap;
		for(int i =0; i<Hs.size(); i++){
			umap[Hs[i]]=i;
		}
		for(int i =0; i<Ht.size(); i++){
			auto  it = umap.find(Ht[i]);
			if(it != umap.end()){
				ans = {it->second, i, mid};
				left = mid + 1;
				wasfound = true;
				break;
			}
		}
		if(!wasfound) right = mid -1;
	}
	
	return ans;
}



int main() {
	// ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = (Answer)solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
