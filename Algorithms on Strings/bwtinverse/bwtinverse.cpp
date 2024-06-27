#include <bits/stdc++.h>
using namespace std;

#include <iostream>

// class Node {
// public:
//     int data;
//     Node* next;

//     Node(int value) : data(value), next(nullptr) {}
// };

// class LinkedList {
// private:
//     Node* head;

// public:
//     LinkedList() : head(nullptr) {}

//     void insert(int value) {
//         Node* newNode = new Node(value);
//         if (head == nullptr) {
//             head = newNode;
//         } else {
//             Node* temp = head;
//             while (temp->next != nullptr) {
//                 temp = temp->next;
//             }
//             temp->next = newNode;
//         }
//     }

//     void display() {
//         Node* temp = head;
//         while (temp != nullptr) {
//             std::cout << temp->data << " ";
//             temp = temp->next;
//         }
//         std::cout << std::endl;
//     }

//     ~LinkedList() {
//         Node* temp = head;
//         while (temp != nullptr) {
//             Node* next = temp->next;
//             delete temp;
//             temp = next;
//         }
//     }
// };

int letterToIndex (char letter)
{
	switch (letter)
	{
		case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		default: assert (false); return -1;
	}
}

struct myChar{
  char c;
  myChar(char c) : c(c){}
  myChar(){}
};

// bool comparer(myChar c1, myChar c2){
//   return c1.c<c2.c;
// }

bool comparer(pair<char, int>* c1, pair<char, int>* c2){
  return *c1<*c2;
}

string InverseBWTPtr(string& bwt) {
  int bound = bwt.size();

  // vector<pair<char,char*>> firstCol(bound), lastCol(bound);
  // for(int i=0; i<bound; i++){
  //   firstCol[i].first = lastCol[i].first = bwt[i];
  //   lastCol[i].second = &firstCol[i].first;
  // }
  // sort(firstCol.begin(), firstCol.end());
  // for(int i=0; i<bound; i++){
  //   firstCol[i].second = &lastCol[i].first;
  // }
  // vector<char> preAns(bound);
  // preAns[bound-1] = '$';
  // pair<char,char*> c = lastCol[0];
  // for(int j=0; j<bound-1; j++){
  //   preAns[bound-2-j] = c.first;
  //   // c = //index needed!
  // }
  // string text(preAns.begin(), preAns.end());
  // // text.reserve();


  string bwtsorted = bwt;
  sort(bwtsorted.begin(), bwtsorted.end());

  vector<pair<char, int>> data(bound);
  vector<pair<char, int>*> firstCol(bound);
  // vector<char*> lastCol(bound);
  // vector<int> sth(bound);
  // vector<char> firstCol(bound);
  for(int i=0; i<bound; i++){
    // firstCol[i].c = bwt[i];
    // lastCol[i] = &firstCol[i];
    data[i].first = bwt[i];
    firstCol[i] = &data[i];
    // firstCol[i] = &bwt[i];
  }
  sort(firstCol.begin(), firstCol.end(), comparer);
  for(int i=0; i<bound; i++){
    firstCol[i]->second = i;
  }
  vector<char> preAns(bound);
  preAns[bound-1] = '$';
  int index = 0;
  for(int j=0; j<bound-1; j++){
    preAns[bound-2-j] = bwt[index];
    index = data[index].second;
  }
  
  string text(preAns.begin(), preAns.end());


  return text;

}

string InverseBWT(const string& bwt) {
  int bound = bwt.size();
  vector<int> alphabetCounter(5, 0);
  vector<int> CounterTillNow(5, 0);
  vector<int> index(bound, 0);
  for(int i=0; i<bound; i++){
    index[i] = alphabetCounter[letterToIndex(bwt[i])];
    alphabetCounter[letterToIndex(bwt[i])]++;
  }
  CounterTillNow[0] = 0;
  CounterTillNow[1] = alphabetCounter[0];
  for(int i=2; i<5; i++){
    CounterTillNow[i] = CounterTillNow[i-1] + alphabetCounter[i-1];
  }
  vector<char> preAns(bound);
  preAns[bound-1] = '$';
  int i = 0;
  for(int j=0; j<bound-1; j++){
    // text = bwt[i] + text;
    preAns[bound-2-j] = bwt[i];
    i = CounterTillNow[letterToIndex(bwt[i])] + index[i];
  }
  string text(preAns.begin(), preAns.end());
  // text.reserve();
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
