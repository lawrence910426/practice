#include <iostream>
#include <set>
#include <map>

using namespace std;

const int MAXN = 1e5 + 50;
int N, Q, raw[MAXN], cmd, a, b;
map<int, set<int>*> P;
int main() {
    int i, ans; set<int>::iterator it;
    cin >> N >> Q;
    for(i = 1;i <= N;i++) cin >> raw[i];
    for(i = 1;i <= N;i++) {
        if(P.find(raw[i]) == P.end()) P[raw[i]] = new set<int>();
        P[raw[i]]->insert(i);
    }
    while(Q--) {
        cin >> cmd >> a >> b;
        if(cmd == 1) {
            P[raw[a]]->erase(a);
            if(P[raw[a]]->size() == 0) P.erase(raw[a]);
            raw[a] = b;
            if(P.find(raw[a]) == P.end()) P[raw[a]] = new set<int>();
            P[raw[a]]->insert(a);
        } else if(cmd == 2) {
            if(P.find(a) == P.end()) P[a] = new set<int>();
            if(P.find(b) == P.end()) P[b] = new set<int>();
            if(P[a]->size() > P[b]->size()) swap(P[a], P[b]);
            for(int item : *P[a]) P[b]->insert(item);
            P.erase(a);
        } else if(cmd == 3) {
            ans = (1LL << 31) - 1;
            if(P.find(b) != P.end()) {
                it = P[b]->lower_bound(a);
                if(it != P[b]->end()) {
                    ans = min(ans, abs(*it - a));
                }
                if(it != P[b]->begin()) {
                    it = prev(it);
                    ans = min(ans, abs(*it - a));
                }
            }
            cout << (ans == (1LL << 31) - 1 ? -1 : ans) << endl;
        }
    }
}
