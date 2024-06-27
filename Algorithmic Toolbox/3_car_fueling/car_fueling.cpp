#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(int a, int b) 
{
    return a>b;
}    

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int last_possible_stop=0, answer=0, check=0;
    // while (dist>0)
    // {
    //     if (stops_counter<1)
    //         return -1;

    //     if (stops.back() < tank)
    //     {
    //         last_possible_stop=stops.back();
    //         stops_counter--;
    //         continue;
    //     }        
    // }
    while(dist>tank)
    {
        if(tank-stops.back()<0 || stops.empty())
        {
            if (check==1)
            {
                dist-=last_possible_stop;
                for(size_t i=0; i<stops.size(); i++)
                {
                    stops[i]-=last_possible_stop;
                }                
                answer+=1;
                check=0;
            }
            else return -1;
        }
        else
        {
            last_possible_stop=stops.back();
            stops.pop_back();
            check=1;
        }
    }
    return answer;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 4;
    cin >> n;

    vector<int> stops(n);// = {200, 375, 550, 750};
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    sort(stops.begin(), stops.end(),compare);
    cout << compute_min_refills(d, m, stops) << "\n";
    return 0;
}
