#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>

using namespace std;
const int MAXN = 2e6 + 50, INF = 1e9;
class zkw {
    int mini[MAXN * 5], tag[MAXN * 5], leaf;
public:
    zkw() {}
    zkw(int N) {
        for(leaf = 1;leaf < N + 2;leaf <<= 1);
        for(int i = leaf * 2;i >= 1;i--) mini[i] = tag[i] = 0;
    }
    void pull(int x) { mini[x] = min(mini[x * 2], mini[x * 2 + 1]) + tag[x]; }
    void modify(int l, int r, int delta) {
        if(l >= r) return;
        int pos;
        for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
            if(l % 2 == 0) { pos = l ^ 1; tag[pos] += delta; pull(pos); }
            if(r % 2 == 1) { pos = r ^ 1; tag[pos] += delta; pull(pos); }
            pull(l >> 1); pull(r >> 1);
        }
        for(pos = (l >> 1);pos != 0;pos >>= 1) pull(pos);
    }
    int minimum(int l, int r) {
        int ans = INF;
        for(l += leaf, r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
            if(l % 2 == 0) ans = min(ans, mini[l ^ 1]);
            if(r % 2 == 1) ans = min(ans, mini[r ^ 1]);
        }
        for(int pos = (l >> 1);pos != 0;pos >>= 1) ans += tag[pos];
        return ans;
    }
} seg;

int raw[MAXN];
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T, N, K, eax, ebx, l, r; int i;
    for(cin >> T;T--;) {
        cin >> N >> K;
        if(T < 4) seg = zkw(K * 2 + 1);
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < N / 2;i++) {
            eax = min(raw[i], raw[N - i - 1]);
            ebx = max(raw[i], raw[N - i - 1]);
            if(T < 4) {
                l = eax + 1; r = ebx + K + 1;
                seg.modify(l, eax + ebx, 1);
                seg.modify(eax + ebx + 1, r ,1);
                seg.modify(2, l, 2);
                seg.modify(r, K * 2 + 1, 2);
            }
        }
        if(T < 4) cout << seg.minimum(2, K * 2 + 1) << '\n';
    }
}
