#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int MAXN = 1e6 + 50;
vector<int> G[MAXN];
int N ,kids[MAXN] ,parent[MAXN];
void dfs(int on ,int p) {
    parent[on] = p;
    kids[on] = 1;
    for(int V : G[on]) {
        if(V != p) dfs(V ,on);
        kids[on] += kids[V];
    }
}
int main() {
    int i ,eax ,ebx;
    int maxi ,ans;
    while(cin >> N) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 0;i < N - 1;i++) {
            cin >> eax >> ebx;
            G[eax].push_back(ebx);
            G[ebx].push_back(eax);
        }
        dfs(0 ,-1);
        ans = (1LL << 31) - 1;
        for(i = 0;i < N;i++) {
            maxi = -1;
            for(int V : G[i]) {
                if(V == parent[i]) maxi = max(maxi ,kids[0] - kids[i]);
                else maxi = max(maxi ,kids[V]);
            }
            ans = min(ans ,maxi);
        }
        cout << ans << endl;
    }
}
