#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct Bracket {
    char type;
    int position;
    
    Bracket(char type, int position): type(type), position(position) {}
    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

};

int main() {
    string text;
    getline(cin, text);

    stack <Bracket> opening_brackets_stack;
    int tr=-1;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position));
        }

        else if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty())
            {
                cout<<position+1;
                return 0;
            }
            Bracket tmp = opening_brackets_stack.top();
            // tr = tmp.position;
            opening_brackets_stack.pop();
            if (!tmp.Matchc(next)) {
                cout<<position+1;
                return 0;
            }
        }
    }

    if(opening_brackets_stack.empty()) 
    {
        cout<< "Success";
        return 0;
    }
    while(!opening_brackets_stack.empty())
    {
        tr=opening_brackets_stack.top().position;
        opening_brackets_stack.pop();
    }
    cout<<tr+1;
    return 0;
}
