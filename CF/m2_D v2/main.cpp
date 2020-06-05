#pragma GCC optimize("Ofast")
#include <iostream>
#include <map>
#include <set>
#include <memory.h>

using namespace std;
const int MAXN = 1e5 + 50;
map<int, set<int>* > Field;
int raw[MAXN];

void op1(int a, int b) {
    Field[raw[a]]->erase(a);
    if(Field[raw[a]]->size() == 0) { delete Field[raw[a]]; Field.erase(raw[a]); }
    raw[a] = b;
    if(Field.find(raw[a]) == Field.end()) Field[raw[a]] = new set<int>();
    Field[raw[a]]->insert(a);
}

void op2(int a, int b) {
    if(Field.find(a) == Field.end()) Field[a] = new set<int>();
    if(Field.find(b) == Field.end()) Field[b] = new set<int>();
    if(Field[a]->size() > Field[b]->size()) swap(Field[a], Field[b]);
    for(int item : *Field[a]) Field[b]->insert(item);
    delete Field[a]; Field.erase(a);
}

int op3(int a, int b) {
    int ans = MAXN;
    if(Field.find(b) == Field.end()) return -1;
    set<int>::iterator it = Field[b]->lower_bound(a);
    if(it != Field[b]->end()) { ans = min(ans, abs(a - *it)); }
    if(it != Field[b]->begin()) { ans = min(ans, abs(a - *prev(it))); }
    return ans == MAXN ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, Q, cmd, a, b; int i, temp;
    cin >> N >> Q;
    memset(raw, 0, sizeof(raw)); Field[0] = new set<int>();
    for(i = 1;i <= N;i++) Field[0]->insert(i);
    for(i = 1;i <= N;i++) { cin >> temp; op1(i, temp); }
    while(Q--) {
        cin >> cmd >> a >> b;
        if(cmd == 1) { op1(a, b); }
        else if(cmd == 2) { op2(a, b); }
        else if(cmd == 3) { cout << op3(a, b) << '\n'; }
    }
}
