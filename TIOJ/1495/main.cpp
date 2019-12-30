#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;
const long long MAXN = 1e3 + 5 ,mod = 1e9 + 7;
long long power(long long value ,long long powers) {
    long long tmp = value ,ret = 1;
    while(powers != 0) {
        if(powers % 2 == 1) ret = (ret * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        powers >>= 1;
    }
    return (ret + mod) % mod;
}
long long inv(long long value) { return power(value ,mod - 2); }

struct zkw {
    long long data[MAXN * 5] ,leaf;
    zkw() {}
    zkw(long long N) {
        memset(data ,0 ,sizeof(data));
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
    }
    void modify(long long l ,long long r ,long long value) {
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) data[l ^ 1] += value;
            if(r % 2 == 1) data[r ^ 1] += value;
        }
    }
    long long query(long long pos) {
        long long ans = 0;
        for(pos += leaf + 1;pos;pos >>= 1) ans += data[pos];
        return ans;
    }
} seg;
struct dsu {
    long long boss[MAXN] ,siz[MAXN];
    dsu() {
        for(long long i = 0;i < MAXN;i++) {
            boss[i] = i;
            siz[i] = 1;
        }
    }
    long long query(long long i) { return (i == boss[i] ? i : boss[i] = query(boss[i])); }
    void join(long long a ,long long b) {
        a = query(a) ,b = query(b);
        siz[a] += siz[b];
        boss[b] = a;
    }
} G;
long long N ,M ,src[MAXN] ,dst[MAXN] ,type[MAXN] ,ans ,s ,d ,temp ,sum;
int main() {
    long long i ,j;
    while(cin >> N >> M) {
        G = dsu();
        ans = 1;
        for(i = 0;i < M;i++) {
            cin >> src[i] >> dst[i] >> type[i];
            if(type[i] == 0) {
                if(G.query(src[i]) == G.query(dst[i])) ans = 0;
                G.join(src[i] ,dst[i]);
            }
        }
        if(ans == 0) cout << 0 << endl;
        else {
            vector<long long> bosses;
            for(i = 0;i < N;i++) if(G.query(i) == i) bosses.push_back(i);
            seg = zkw(bosses.size());
            for(i = 0;i < M;i++) if(type[i] == 1) {
                s = G.query(src[i]) ,d = G.query(dst[i]);
                if(s != d) {
                    s = lower_bound(bosses.begin() ,bosses.end() ,s) - bosses.begin();
                    d = lower_bound(bosses.begin() ,bosses.end() ,d) - bosses.begin();
                    temp = max(s ,d);
                    seg.modify(temp ,temp + 1 ,1);
                }
            }
            sum = G.siz[bosses[0]];
            for(i = 1;i < bosses.size();i++) {
                temp = (sum * G.siz[bosses[i]]) % mod;
                ans = (temp - seg.query(i)) % mod;
                sum = (sum + G.siz[bosses[i]]) % mod;
            }
            cout << ans << endl;
        }
    }
}
