#include <bits/stdc++.h>

#define int long long

inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
using namespace std;
const int MAXN = 2e5 + 50;
struct zkw {
    int leaf ,data[MAXN * 5];
    int sum(int l ,int r) {
        int ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) ans += data[l ^ 1];
            if(r % 2 == 1) ans += data[r ^ 1];
        }
        return ans;
    }
    void modify(int x ,int diff) { for(x += leaf + 1;x >= 1;x >>= 1) data[x] += diff; }
    zkw() {
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        memset(data ,0 ,sizeof(data));
    }
} seg[2];

struct S { int pos ,vel; } raw[MAXN];
bool cmp(S a ,S b) { return a.pos < b.pos; }
vector<int> discrete;

main() {
    int N ,ans = 0; N=read();
    int i ,temp;
    for(i = 0;i < N;i++) raw[i].pos=read();
    for(i = 0;i < N;i++) raw[i].vel=read();
    sort(raw ,raw + N ,cmp);
    for(i = 0;i < N;i++) discrete.emplace_back(raw[i].vel);
    sort(discrete.begin() ,discrete.end());
    auto last = unique(discrete.begin() ,discrete.end());
    for(i = 0;i < N;i++) {
        auto it = lower_bound(discrete.begin() ,last ,raw[i].vel);
        temp = it - discrete.begin();
        ans += raw[i].pos * seg[1].sum(0 ,temp + 1) - seg[0].sum(0 ,temp + 1);
        seg[0].modify(temp ,raw[i].pos);
        seg[1].modify(temp ,1);
    }
    printf("%lld\n",ans);//cout << ans << endl;
}
