#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


bool compare(int a, int b)
{
  return a<b;
}

string largest_number(vector<int> a) {
  vector<int> one;
  vector<int> two;
  vector<int> three;
  int thousand_count=0, flag=0;
  for (int i=0; i<a.size(); i++)
  {
    if(a[i]<10) one.push_back(a[i]);
    else if(a[i]<100) two.push_back(a[i]);
    else if(a[i]==1000) thousand_count++;
    else  three.push_back(a[i]);
  }

  a.clear();
  sort(one.begin(), one.end(), compare);
  sort(two.begin(), two.end(), compare);
  sort(three.begin(), three.end(), compare);

  if(two.empty() && three.empty() && !one.empty())
  {
    int check=0;
    for(int i =0; i< one.size(); i++)
    {
      check+=a[i];
    }
    if (check==0)
    {
      a.clear();
      a.push_back(0);
      flag=1;
    }
  }

  while((!one.empty() || !two.empty() || !three.empty())&&flag==0)
  {
    int initial_o = !one.empty() ? one.back() : 0;
    int initial_t = !two.empty() ? two.back() : 0;
    int th=!three.empty() ? three.back() : 0;
    // if(initial_o!=0 && initial_t!=0 && (int)((initial_o))==(int)((initial_t)/10) && (initial_t)%10>=(int)(initial_o))
    // {
    //   a.push_back(two.back());
    //   two.pop_back();
    // }
    // else if(initial_o!=0 && th!=0 && (int)((initial_o))==(int)((th)/100) && ((int)(th/10))%10>=(int)(initial_o))
    // {
    //   a.push_back(three.back());
    //   three.pop_back();
    // }

    // else if(o>=t && o>=th)
    // {
    //   a.push_back(one.back());
    //   one.pop_back();
    // }
    // else if(initial_t!=0 && th!=0 && (int)((initial_t))==(int)(th/10) && th%10>=(int)(th/100))
    // {
    //   a.push_back(three.back());
    //   three.pop_back();
    // }
    // else if(t>=o && t>=th)
    // {
    //   a.push_back(two.back());
    //   two.pop_back();
    // }
    // else
    // {

    //   a.push_back(three.back());
    //   three.pop_back();
    // }

    if(initial_o>(int)(initial_t/10) && initial_o>(int)(th/100))
    {
      a.push_back(one.back());
      one.pop_back();
    }

    else if((int)(initial_t/10)>initial_o && (int)(initial_t/10)>(int)(th/100))
    {
      a.push_back(two.back());
      two.pop_back();
    }

    else if((int)(th/100)>(int)(initial_t/10) && (int)(th/100)>initial_o)
    {
      a.push_back(three.back());
      three.pop_back();
    }

    else
    {
      int o= !one.empty() ? (((one.back()*10)+one.back())*10)+one.back(): 0;
      int t= !two.empty() ? two.back()*10+((int)(two.back()/10)) : 0;
      if(o>t && o>th)
      {
        a.push_back(one.back());
        one.pop_back();
      }
      else if(t>o && t>th)
      {
        a.push_back(two.back());
        two.pop_back();
      }
      else if(th>o && th>t)
      {
        a.push_back(three.back());
        three.pop_back();
      }
      else if(th==t)
      {
        a.push_back(two.back());
        two.pop_back();
      }
      else if(o==t)
      {
        a.push_back(one.back());
        one.pop_back();
      }
      else
      {
        a.push_back(three.back());
        three.pop_back();
      }

    }



  }
  for(int i=0; i<thousand_count; i++)
  {
    a.push_back(1000);
  }

  stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  cin >> n;
  // vector<int> a;
  // a.push_back(56);
  // a.push_back(5);
  // a.push_back(50);
  // a.push_back(2);
  // a.push_back(1);

  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  cout << largest_number(a);
}

// A Novel by Jane Austen 
