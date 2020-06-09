#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 1e3;
const long long mod = 1e9 + 7;
struct offline { int src ,dst ,type; } data[MAXN];
struct dsu {
    int parent[MAXN] ,siz[MAXN];
    dsu() { for(int i = 0;i < MAXN;i++) parent[i] = i ,siz[i] = 1; }
    int query(int pos) { return (pos == parent[pos] ? pos : parent[pos] = query(parent[pos])); }
    void join(int a ,int b) {
        a = query(a) ,b = query(b);
        siz[b] += siz[a];
        parent[a] = parent[b];
    }
} G;
long long ans ,fixes[MAXN] ,sum;
int main() {
    int N ,M ,src ,dst ,temp;
    int i ,j;
    while(cin >> N >> M) {
        G = dsu();
        memset(fixes ,0 ,sizeof(fixes));
        ans = 1;
        for(i = 0;i < M;i++) {
            cin >> data[i].src >> data[i].dst >> data[i].type;
            if(data[i].type == 0) {
                if(G.query(data[i].src) == G.query(data[i].dst)) ans = 0;
                else G.join(data[i].src ,data[i].dst);
            }
        }
        if(ans == 0) cout << ans << endl;
        else {
            vector<int> boss;
            for(i = 0;i < N;i++) if(G.query(i) == i) boss.push_back(i);
            for(i = 0;i < M;i++) if(data[i].type == 1) {
                src = G.query(data[i].src) ,dst = G.query(data[i].dst);
                if(src != dst) {
                    src = lower_bound(boss.begin() ,boss.end() ,src) - boss.begin();
                    dst = lower_bound(boss.begin() ,boss.end() ,dst) - boss.begin();
                    fixes[max(src ,dst)] += 1;
                }
            }
            sum = G.siz[boss[0]];
            for(i = 1;i < boss.size();i++) {
                temp = (G.siz[boss[i]] * sum) % mod;
                temp = (temp - fixes[i]) % mod;
                ans = (ans * temp) % mod;
                sum = (sum + G.siz[boss[i]]) % mod;
            }
            cout << ans << endl;
        }
    }
}
