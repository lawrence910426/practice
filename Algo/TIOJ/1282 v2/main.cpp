#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
using namespace std;
const int MAXN = 1e5 + 10;
struct seg {
    long long sum ,gcd;
    seg(): sum(0) ,gcd(0) {}
    seg(long long s ,long long g): sum(s) ,gcd(g) {}
}zkw[5 * MAXN];
long long diff[MAXN] ,raw[MAXN];
int leaf;
long long gcd(long long a ,long long b) {
    if(a == 0) return b;
    if(b == 0) return a;
    return gcd(b ,a % b);
}
seg join(seg a ,seg b) { return seg(a.sum + b.sum ,gcd(a.gcd ,b.gcd)); }
seg query(int l ,int r) {
    seg ans = seg();
    if(l == r) return ans;
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
        if(l % 2 == 0) ans = join(ans ,zkw[l ^ 1]);
        if(r % 2 == 1) ans = join(ans ,zkw[r ^ 1]);
    }
    return ans;
}

void update(int pos ,long long value) {
    pos += leaf + 1;
    zkw[pos].sum += value;
    zkw[pos].gcd = abs(zkw[pos].sum);
    for(pos >>= 1;pos >= 1;pos >>= 1)
        zkw[pos] = join(zkw[pos * 2] ,zkw[pos * 2 + 1]);
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,Q ,c ,l ,r;
    int i;
    long long k;
    while(cin >> N >> Q) {
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < N - 1;i++) diff[i] = raw[i + 1] - raw[i];
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = leaf + 1;i < leaf + 1 + N - 1;i++) zkw[i].sum = diff[i - leaf - 1] ,zkw[i].gcd = abs(diff[i - leaf - 1]);
        for(i = leaf - 1;i >= 1;i--) zkw[i] = join(zkw[i * 2] ,zkw[i * 2 + 1]);
        while(Q--) {
            cin >> c;
            if(c == 1) {
                cin >> l >> r >> k;
                if(l == 1) raw[0] += k;
                else update(l - 2 ,k);
                update(r - 1 ,-k);
            } else if(c == 2) {
                cin >> l >> r;
                seg s1 = query(0 ,l - 1);
                seg s2 = query(l - 1 ,r - 1);
                cout << gcd(s1.sum + raw[0] ,s2.gcd) << endl;
            }
        }
    }
}
