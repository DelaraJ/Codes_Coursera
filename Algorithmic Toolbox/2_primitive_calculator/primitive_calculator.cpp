#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

// using std::vector;
using namespace std;

vector<int> optimal_sequence(int n) {
  vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if ((n-1) % 3 == 0) {
      n-=1;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int PrimitiveCalculatorGreedy(int n)
{
  int numOperation =0;
  int currentNumber =1;
  while (currentNumber<n)
  {
    if(currentNumber<=n/3) currentNumber*=3;
    else if(currentNumber<=n/2) currentNumber*=2;
    else currentNumber+=1;
    numOperation+=1;
  }
  return numOperation;
}

int min3(int a, int b, int c)
{
  if (a<=b && a<=c) return a;
  if (b<=a && b<=c) return b;
  return c;
}

vector<int> PrimitiveCalculatorDP(int n)
{
  vector<int> a(n+1), aregion(n+1);
  vector<int> ans;
  if(n<4)
  {
    ans.push_back(1);
    if(n==1) return ans;
    ans.push_back(n);
    return ans;
  }
  a[2]=1;
  a[3]=1;
  aregion[2]=1;
  aregion[3]=1;
  
  for(int i=4; i<=n; i++)
  {
    int ta = a[i-1]+1, tb= (i%2==0)? (a[i/2]+1):1000000, tc= (i%3==0)? (a[i/3]+1):1000000;
    a[i]=min3(ta, tb, tc);
    if(a[i]==tc) aregion[i]=i/3;
    else if(a[i]==tb) aregion[i]=i/2;
    else aregion[i]=i-1;
  }
  int i=n;
  while(i!=1)
  {
    ans.push_back(i);
    i=aregion[i];
  }
  ans.push_back(1);
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<int> sequence = PrimitiveCalculatorDP(n);
  cout << sequence.size() - 1 << endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << " ";
  }
}
