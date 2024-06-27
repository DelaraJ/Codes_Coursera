#include <bits/stdc++.h>

using namespace std;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  // vector<int> assigned_workers_;
  // vector<long long> start_times_;
  vector<pair<int, long long>> worker__start;
  vector<pair<int, long long>> worker__start_print;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << worker__start_print[i].first << " " << worker__start_print[i].second << "\n";
    }
  }

  void SiftDown(int i)
  {
    int indexOfMin = i, size=worker__start.size();
    int l = 2*i +1;
    int r = 2*i +2;
    if(l<size || r<size)
    {
      if(l<size && worker__start[l].second <= worker__start[indexOfMin].second)
      {
        if(worker__start[l].second == worker__start[indexOfMin].second)
        {
          if(worker__start[l].first < worker__start[indexOfMin].first) indexOfMin=l;
        }
        else indexOfMin=l;
        
      } 
      if(r<size && worker__start[r].second <= worker__start[indexOfMin].second)
      {
        if(worker__start[r].second == worker__start[indexOfMin].second)
        {
          if(worker__start[r].first < worker__start[indexOfMin].first)  indexOfMin=r;
        }
        else indexOfMin=r;
      }
    }
    if (i!=indexOfMin)
    {
      swap(worker__start[i], worker__start[indexOfMin]);
      SiftDown(indexOfMin);
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    int bound = num_workers_;
    for(int i=0; i<bound; i++)
    {
      worker__start.push_back(make_pair(i, 0));
      // worker__start_print.push_back(make_pair(i, 0));
    }

    // for(int i=int(worker__start.size()/2); i>=0; i--)
    // {
    //   SiftDown(i);
    // }

    for(int i=0; i<jobs_.size(); i++)
    {
      worker__start_print.push_back(worker__start[0]);
      worker__start[0].second+=jobs_[i];
      SiftDown(0);
    }

  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
