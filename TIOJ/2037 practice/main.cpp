#include <iostream>
#include <bitset>
#include <vector>

using namespace std;
const int MAXN = 1e5 + 50 ,MAXV = 3e5;
int match[MAXV];
bitset<MAXV> visit;
vector<int> G[MAXV];
int hungarian(int on) {
    if(visit[on]) return 0;
    visit[on] = true;
    for(int V : G[on]) {
        if(match[V] == -1 || hungarian(match[V]) == 1) {
            match[V] = on;
            match[on] = V;
            return 1;
        }
    }
    return 0;
}

int main() {
    int T ,N ,M ,E ,ans;
    int i ,src ,dst;
    for(cin >> T;T--;) {
        for(i = 0;i < MAXV;i++) G[i] = vector<int>();
        for(i = 0;i < MAXV;i++) match[i] = -1;
        cin >> N >> M >> E;
        while(E--) {
            cin >> src >> dst;
            dst += MAXN;
            G[src].push_back(dst);
            G[dst].push_back(src);
        }
        ans = 0;
        for(i = 1;i <= N;i++) {
            visit.reset();
            if(match[i] == -1 && hungarian(i) == 1) ans += 1;
        }
        cout << ans << endl;
    }
}
