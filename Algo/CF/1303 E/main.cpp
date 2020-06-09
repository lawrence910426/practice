#include <iostream>
#include <set>
#include <cstring>

using namespace std;
const int MAXC = 26;
set<int> S[MAXC];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int T ,i ,pos;
    string src ,dst;
    bool rerun;
    for(cin >> T;T--;) {
        cin >> src >> dst; rerun = false; pos = -1;
        for(i = 0;i < MAXC;i++) S[i] = set<int>();
        for(i = 0;i < src.size();i++) S[src[i] - 'a'].insert(i);
        for(i = 0;i < dst.size();i++) {
            auto it = S[dst[i] - 'a'].lower_bound(pos);
            if(it == S[dst[i] - 'a'].end()) {
                if(rerun == false) { pos = -1; i -= 1; rerun = true; }
                else { break; }
            } else { pos = *it; S[dst[i] - 'a'].erase(it); }
        }
        if(i == dst.size()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
/*
2
aacab
cacab
*/
