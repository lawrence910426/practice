#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int MAXN = 1e2 + 50;
int main() {
    int T ,N ,ans[MAXN * 2];
    int i;
    for(cin >> T;T--;) {
        cin >> N; set<int> unused;
        for(i = 1;i <= N * 2;i++) unused.insert(i);
        for(i = 0;i < N;i++) {
            cin >> ans[i * 2 + 1];
            unused.erase(ans[i * 2 + 1]);
        }
        for(i = 0;i < N;i++) {
            auto it = unused.lower_bound(ans[i * 2 + 1]);
            if(it == unused.end()) break;
            ans[i * 2] = *it; unused.erase(it);
            if(ans[i * 2] > ans[i * 2 + 1]) swap(ans[i * 2] ,ans[i * 2 + 1]);
        }
        if(i == N) {
            for(i = 0;i < N * 2;i++) cout << ans[i] << " ";
            cout << endl;
        } else cout << -1 << endl;
    }
}
