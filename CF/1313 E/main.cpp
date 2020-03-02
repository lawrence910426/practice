#pragma GCC optimize("Ofast,unroll-loops")
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <list>

using namespace std;
const int MAXC = 26 ,MAXN = 1e6 + 50;
list<int> ans[2][MAXN];

class Automata {
    struct { int kids[MAXC] ,fail ,emit; } node[MAXN];
    int used ,root;
public:
    Automata() {
        used = root = 0;
        for(int i = 0;i < MAXN;i++) {
            for(int j = 0;j < MAXC;j++) node[i].kids[j] = -1;
            node[i].emit = node[i].fail = -1;
        }
    }
    void Insert(string& s) {
        int on = root;
        for(int i = 0;i < s.size();i++) {
            if(node[on].kids[s[i] - 'a'] == -1) node[on].kids[s[i] - 'a'] = ++used;
            on = node[on].kids[s[i] - 'a'];
            node[on].emit = i;
        }
    }
    void Build() {
        queue<int> Q;
        int i ,on ,ptr;
        for(i = 0;i < MAXC;i++) if(node[root].kids[i] != -1) {
            on = node[root].kids[i];
            node[on].fail = root;
            Q.push(on);
        }
        for(node[root].fail = root;!Q.empty();Q.pop()) {
            for(i = 0;i < MAXC;i++) if(node[Q.front()].kids[i] != -1) {
                on = node[Q.front()].kids[i]; ptr = node[Q.front()].fail;
                while(ptr != root && node[ptr].kids[i] == -1) ptr = node[ptr].fail;
                node[on].fail = ptr = (node[ptr].kids[i] == -1 ? root : node[ptr].kids[i]);
                Q.push(on);
            }
        }
    }
    void Run(string& s ,list<int>* ans) {
        int on = root ,color ,ptr;
        for(int i = 0;i < s.size();i++) {
            color = s[i] - 'a';
            while(on != root && node[on].kids[color] == -1) on = node[on].fail;
            on = (node[on].kids[color] == -1 ? root : node[on].kids[color]);
            for(ptr = on;ptr != root;ptr = node[ptr].fail) ans[node[ptr].emit].push_back(i);
        }
    }
} *Pattern;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int slen ,plen ,output = 0 ,low ,up; string str[2] ,patt;
    cin >> slen >> plen >> str[0] >> str[1] >> patt;

    Pattern = new Automata(); Pattern->Insert(patt); Pattern->Build(); Pattern->Run(str[0] ,ans[0]);
    reverse(str[1].begin() ,str[1].end()); reverse(patt.begin() ,patt.end());
    Pattern = new Automata(); Pattern->Insert(patt); Pattern->Build(); Pattern->Run(str[1] ,ans[1]);

    for(int i = 0;i < plen - 1;i++) {
        vector<int> S;
        for(int item : ans[0][i]) S.push_back(item - i);
        for(int item : ans[1][plen - i - 2]) {
            low = slen - item - 1; up = low + plen - i - 2;
            output += upper_bound(S.begin() ,S.end() ,up) - lower_bound(S.begin() ,S.end() ,low - i);
        }
    }
    cout << output << endl;
}
