#include <bits/stdc++.h>

using namespace std;



bool partition3(vector<int> &nums, int sum) {
 
  int s=nums.size();
  if(sum%3!=0) return false;
  sum/=3;
  vector<vector<vector<bool>>> dp(s+1,(vector<vector<bool>>(sum+1,(vector<bool>(sum+1,false)))));
  for(int i=0; i<=s; i++) dp[i][0][0]=true;

  for(int i=1; i<=sum; i++)
  {
    for(int j=1; j<=sum; j++)
    {
      dp[0][i][j]=false;
    }
  }

  for(int i=1; i<=s; i++)
  {
    for(int j=0; j<=sum; j++)
    {
      for(int k=0; k<=sum; k++)
      {
        dp[i][j][k]=dp[i-1][j][k];
        if(j-nums[i-1]>=0)   dp[i][j][k] = dp[i][j][k] || dp[i-1][j-nums[i-1]][k];
        if(k-nums[i-1]>=0)   dp[i][j][k] = dp[i][j][k] || dp[i-1][j][k-nums[i-1]];
      }
    }
  }

  return dp[s][sum][sum];

}
int partition3_dp(vector<int> &A,int sum)
{
  int n = A.size();
  vector<vector<vector<int>>> dp(sum+1,vector<vector<int>>(sum+1,vector<int>(n+1,0)));
  dp[0][0][0] = 1;

  for (int x = 0; x <=sum; x++)
  {
    for (int y = 0; y <= sum; y++)
    {
      for (int i = 1; i <= n; i++)
      {
        int a=0,b=0,c=0;
        if(A[i-1]<=x)
          a = dp[x-A[i-1]][y][i-1];
        if(A[i-1]<=y)
          b = dp[x][y-A[i-1]][i-1];
        c = dp[x][y][i-1];
        dp[x][y][i] = a || b|| c;
      }
      
    }
    
  }
  return dp[sum][sum][n];
}

void test()
{
  srand(time(0));
  for (int i = 0; i < 1000; i++)
  {
    int n = rand()%100;
    vector<int> a(n);
    int sum = 0;
    for (int j = 0; j < n; j++)
    {
      a[i] = rand()%1000+1;
      sum += a[i];
    }
    if(sum%3==0)
    {
    int b =  partition3_dp(a,sum/3);
    int c = partition3(a,sum);
    if(b!=c)
    {
      cout<<"test case "<<i<<endl;
      for (int k = 0; k < n; k++)
      {
        cout<<a[k]<<" ";
      }
      cout<<endl<<"shabnam :"<<b<<endl;
      cout<<endl<<"delara :"<<c<<endl<<endl<<endl;
      
    }

    }
  }
  
}

int main() {
  int n;
  cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    cin >> A[i];
  }
  if(A.size()==0) cout << 0 << '\n';
  else
  {
    int sum =0, a =A.size();
    for(int i=0; i<a; i++) sum+=A[i];
    cout <<( partition3(A,sum) ? 1 : 0) << '\n';
  }
  // test();
}
