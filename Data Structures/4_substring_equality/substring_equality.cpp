#include <bits/stdc++.h>

using namespace std;

class Solver {
	string s;
	long long x = 17, m1 = 1e9+7, m2= 1e9+9;
	vector<long long> H1;
	vector<long long> H2;
	vector<long long> powers1;
	vector<long long> powers2;
public:	
	Solver(string s) : s(s) {	
		H1 = precomputeHashes(s, m1);
		H2 = precomputeHashes(s, m2);
		powers1 = calculatePowers(s.size(), m1);
		powers2 = calculatePowers(s.size(), m2);
	}
	bool ask(int a, int b, int l) {
		return 	(((H1[a+l] - (H1[a]*powers1[l]) % m1)+ m1) % m1) == (((H1[b+l] - (H1[b]*powers1[l]) % m1)+ m1) % m1)
			 && (((H2[a+l] - (H2[a]*powers2[l]) % m2)+ m2) % m2) == (((H2[b+l] - (H2[b]*powers2[l]) % m2)+ m2) % m2);
	}
	vector<long long> precomputeHashes(string input, long long prime) {
		vector<long long> H(s.size()+1);
		H[0] = 0;
		for(int i = 1; i<=s.size(); i++){
			H[i] = ((x*H[i-1])%prime + input[i-1]) % prime;
		}
		return H;
	}

	vector<long long> calculatePowers(size_t n, long long mod){
		vector<long long> p(n+1);
		p[0]=1;
		for(size_t i=1; i<=n; i++){
			p[i]=(p[i-1]*x) % mod;
		}
		return p;
	}
	
};


int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
