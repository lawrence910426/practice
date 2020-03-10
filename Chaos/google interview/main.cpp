#include <iostream>
#include <vector>

using namespace std;

struct tree { vector<tree*> kids; tree* parent; };
void dfs(tree *on) {
    if(on->parent != nullptr) cout << '(';
    for(auto t : on->kids) dfs(t);
    if(on->parent != nullptr) cout << ')';
}
int main() {
    string s;
    while(cin >> s) {
        tree* pos = new tree{ vector<tree*>() ,nullptr };
        for(int i = 0;i < s.size();i++) {
            if(s[i] == '(') {
                tree* node = new tree{ vector<tree*>() ,pos };
                pos->kids.push_back(node);
                pos = node;
            } else pos = pos->parent;
        }
        if(pos->parent != nullptr) {
            cout << "Invalid string" << endl;
            continue;
        }
        int ans = 0;
        while(pos->kids.size() == 1) { pos = pos->kids[0]; ans += 1; }
        cout << ans << endl;
        cout << "The reduced string: ";
        if(pos->kids.size() != 0) { pos->parent = nullptr; dfs(pos); }
        cout << endl;
    }
}
/*
((()))
()()
((()()))
(((()
*/
