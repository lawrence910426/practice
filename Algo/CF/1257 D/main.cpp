#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <assert.h>

using namespace std;
const int MAXN = 2e5 + 10;
int T ,N ,M;
int monsters[MAXN];
pair<int ,int> heros[MAXN]; /* First: Ability ,Second: Endurance */
int zkw[MAXN * 5] ,leaf;

int join(int i ,int j) {
    if(heros[i].second > heros[j].second) return i;
    else return j;
}

int query(int l ,int r) {
    int ans = zkw[leaf + l + 1];
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
        if(l % 2 == 0) ans = join(ans ,zkw[l ^ 1]);
        if(r % 2 == 1) ans = join(ans ,zkw[r ^ 1]);
    }
    return ans;
}

int main() {
    int killed ,days ,kill;
    int i ,j;
    bool unable;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    for(cin >> T;T--;) {
        cin >> N;
        for(i = 0;i < N;i++) cin >> monsters[i];
        cin >> M;
        for(i = 0;i < M;i++) cin >> heros[i].first >> heros[i].second;
        sort(heros ,heros + M);
        memset(zkw ,0 ,sizeof(zkw));
        for(leaf = 1;leaf < M + 2;leaf <<= 1) ;
        for(i = leaf + 1;i < leaf + 1 + M;i++) zkw[i] = i - leaf - 1;
        for(i = leaf - 1;i >= 1;i--) zkw[i] = join(zkw[i * 2] ,zkw[i * 2 + 1]);
        unable = false;
        for(i = days = killed = 0;killed != N;days++) {
            for(j = kill = 0;true;) {
                auto ptr = lower_bound(heros ,heros + M ,pair<int ,int>(monsters[killed + kill] ,0));
                if(ptr == heros + M) { unable = true; break; }
                int best = query(ptr - heros ,M);
                if(kill >= heros[best].second) break;
                for(;killed + kill < N && kill < heros[best].second;kill++) if(monsters[killed + kill] > heros[best].first) break;
                if(killed + kill == N || kill == heros[best].second) break;

                j += 1;
                assert(j < 1000);
            }
            if(unable) break;
            else killed += kill;

            i += 1;
            assert(i < 1000);
        }
        if(unable) cout << -1 << '\n';
        else cout << days << '\n';
    }
}
