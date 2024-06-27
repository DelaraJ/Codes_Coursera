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
  vector<int> a(n+1);
  vector<int> ans;
  ans.push_back(1);
  if(n<4)
  {
    if(n==1) return ans;
    ans.push_back(n);
    return ans;
  }
  a[2]=1;
  a[3]=1;
  
  for(int i=4; i<=n; i++)
  {
    int ta = a[i-1]+1, tb= (i%2==0)? (a[i/2]+1):1000000, tc= (i%3==0)? (a[i/3]+1):1000000;
    a[i]=min3(ta, tb, tc);
    if(a[i]==tc) ans.push_back(i/3);
    else if(a[i]==tb) ans.push_back(i/2);
    else ans.push_back(i-1);
  }
  ans.push_back(n);
  return ans;
}