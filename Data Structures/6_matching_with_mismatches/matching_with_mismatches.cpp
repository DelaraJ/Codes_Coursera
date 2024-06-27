#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll x = 263, prime=100000007;

vector<ll> precomputehashes(string s){
	vector<ll> H(s.size()+1);
	H[0]=0;
	for(int i=1; i< s.size()+1; i++){
		H[i]= (H[i-1]*x %prime + s[i-1]) %prime;
	}
	return H;
}

vector<ll> calculatePowers(size_t n, ll mod= prime){
	vector<ll> p(n+1);
	p[0]=1;
	for(size_t i=1; i<=n; i++){
		p[i]=(p[i-1]*x) % mod;
	}
	return p;
}

class Solver{
	int k;
	string text, pattern;
	vector<ll> tH;
	vector<ll> pH;
	vector<ll> powers;
	vector<int> pos;
	public:
		Solver(int k, string text, string pattern) : k(k), text(text), pattern(pattern){
			powers = calculatePowers(text.size());
			tH =  precomputehashes(text);
			pH = precomputehashes(pattern);
		}
		vector<int> solve();
		bool recursivecheckMismatches(int i, int left, int right);
		bool checkhash(int i, int left, int right);
};

vector<int> Solver::solve() {
	bool passed = false;
	int t = text.size(), p = pattern.size();
	int sth = k;
	for(int i=0; i<t-p+1; i++){
		passed = recursivecheckMismatches(i, 0, pattern.size());
		if(passed){
			pos.push_back(i);
		}
		k=sth;
	}
	return pos;
}
bool Solver::checkhash(int i, int left, int right){
	auto ht = ((tH[i+right] - (tH[i+left]*powers[right - left]) %prime) +prime) %prime;
	auto hp = ((pH[right] - (pH[left]*powers[right - left]) %prime) +prime) %prime;
	return ht == hp;
}

bool Solver::recursivecheckMismatches(int i, int left, int right){
	if(left>=right) return true;
	int mid= (right + left) /2 ;
	if(checkhash(i, left, right)) return true;
	if(text[i+mid] != pattern[mid]){
		if(k==0) return false;
		k--;
	}
	bool rchecker = recursivecheckMismatches(i, mid+1, right);
	if(!rchecker) return false;
	bool lchecker = recursivecheckMismatches(i, left, mid);
	if(!lchecker) return false;
	return true;

}


int main() {
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		Solver solver(k, t, p);
		vector<int> a = solver.solve();
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
