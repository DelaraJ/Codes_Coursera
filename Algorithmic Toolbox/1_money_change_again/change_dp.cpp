#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// int get_change(int m) {
//   //write your code here
//   return m / 4;
// }

int Change_Money_Recursive (int money, vector<int> coins)
{
  if(money == 0) return 0;
  int MinNumCoins = 2147483647;
  for (int i=0; i<coins.size(); i++)
  {
    if(money>=coins[i])
    {
      int MinSoFar = Change_Money_Recursive(money-coins[i], coins);
      if(MinSoFar+1 < MinNumCoins) MinNumCoins = MinSoFar+1;
    }
  }
  return MinNumCoins;

}

int Change_Money_DP(int money, vector<int> coins)
{
  vector<int> MinNumCoins(money+1);
  for(int i=1; i<=money; i++) MinNumCoins[i]=pow(10, 6);
  for(int i =1; i<=money; i++)
    for(int j=0; j<coins.size(); j++)
      if(i>=coins[j])
        MinNumCoins[i]=min(MinNumCoins[i-coins[j]]+1,MinNumCoins[i]);
  return MinNumCoins[money];
  
}

int main() {
  int m;
  cin >> m;
  vector<int> coins={1, 3, 4};
  cout << Change_Money_DP(m, coins) << '\n';
}
