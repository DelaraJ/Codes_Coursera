#include <iostream>
#include <vector>
#define ll long long
using namespace std;
ll x = 35, prime=1e12 + 37;
ll polyhash(string t){
	ll h=0;
	for (size_t i = t.size()-1; i >= 0; i--){
		h = ((h * x)% prime  + t[i]) %prime; 
	}
	return h;
}

// vector<ll> rabinkarp(string t, string p) {
// 	vector<ll> H(p.size() - t.size() +1);
// 	H[p.size() - t.size()] = polyhash(t.substr(t.size()-p.size()));
// 	ll y = 1;
//     for(int i=0; i<p.size(); i++){
//         y= (y*x) % prime;
//     }
// 	for(size_t i=p.size() - t.size()-1; i>=0; i--){
//         H[i] = (((x * H[i+1] + t[i]) % prime - (y * t[i+p.size()]) % prime) + prime) % prime;
// 	}
// return H;
// }

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
	int trashpos;
	public:
		Solver(int k, string text, string pattern, vector<long long> powers) : k(k), text(text), pattern(pattern), powers(powers){

			tH.resize(text.size()+1);
			pH.resize(pattern.size()+1);
			int maxs=max(text.size(), pattern.size());
			int mins=min(text.size(), pattern.size());
			tH[0]=pH[0]=0;
			for(int i=1; i< maxs+1; i++){
				if(i<=mins) 
					pH[i]= (pH[i-1]*x %prime + pattern[i-1]) %prime;
				tH[i]= (tH[i-1]*x %prime + text[i-1]) %prime;
			}
		}
		vector<int> solve();
		bool findfirstmismatch(int i, int left, int right);
		bool checkhash(int i, int left, int right);
		bool fakecheckhash(int i, int left, int right);
};

vector<int> Solver::solve() {
	bool passed = false;
	int t = text.size(), p = pattern.size();
	int sth = k;
	for(int i=0; i<t-p+1; i++){
		for(int j=0; i<k; j++)
		{

		}

		passed = findfirstmismatch(i, 0, pattern.size()-1);
		if(passed){
			pos.push_back(i);
		}
		k=sth;
	}
	return pos;
}
bool Solver::checkhash(int i, int left, int right){
	auto ht = ((tH[i+right+1] - (tH[i+left]*powers[right - left+1]) %prime) +prime) %prime;
	auto hp = ((pH[right+1] - (pH[left]*powers[right - left+1]) %prime) +prime) %prime;
	if(ht == hp){
		if(text.substr(i+left, right-left+1) == pattern.substr(left, right-left+1)) return true;
	}
	return false;
}
bool Solver::fakecheckhash(int i, int left, int right){
	string ht, hp;
	for(int j= i+left; j<=i+right; j++){
		ht+=text[j];
	}
	for(int j= left; j<=right; j++){
		hp+=pattern[j];
	}
	string t = text.substr(i+left, right-left+1), p = pattern.substr(left, right-left+1);
	if(t == p) return true;
	return false;
}

bool Solver::findfirstmismatch(int i, int left, int right){
	trashpos=i;
	if(left>right) return false;
	if(left == right){
		if (text[i+left] != pattern[left]){
			if(k==0) return false;
			k--;
		}
		return true;
	}
	int mid= (right - left) /2 ;
	if(checkhash(i, left, right)) return true;
	if(text[i+mid+left] != pattern[mid+left]){
		if(k==0) return false;
		k--;
	}
	bool rchecker = findfirstmismatch(i, left+mid+1, right);
	if(!rchecker) return false;
	bool lchecker =(mid==0)? true : findfirstmismatch(i, left, left+mid-1);
	if(!lchecker) return false;
	return true;

}


int main() {
	// ios_base::sync_with_stdio(false), cin.tie(0);
	vector<long long> powers(200000+1);
	powers[0]=1;
	for(size_t i=1; i<=200000; i++){
		powers[i]=(powers[i-1]*x) % prime;
	}
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		Solver solver(k, t, p, powers);
		vector<int> a = solver.solve();
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
