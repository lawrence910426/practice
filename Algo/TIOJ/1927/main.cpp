#pragma GCC optimize("Ofast,no-stack-protector")

#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAXN = 1e5 + 50;
const long long mod = 1e9 + 7;

int N, Q;
bitset<MAXN> data;

long long power(long long base, long long power) {
    long long ans = 1, temp;
    for(temp = base;power > 0;power >>= 1) {
        if(power & 1) ans = (ans * temp) % mod;
        temp = (temp * temp) % mod;
    }
    return ans;
}

class SuffixArray {
    struct { int keys[2], index; } bucket[2][MAXN];
    int sum[MAXN];
    void radix_sort(int C) {
        int i, j;
        for(j = 1;j >= 0;j--) {
            for(i = 1;i < C;i++) sum[i] = 0;
            for(i = 0;i < N;i++) sum[bucket[0][i].keys[j]] += 1;
            for(i = 1;i < C;i++) sum[i] += sum[i - 1];
            for(i = N - 1;i >= 0;i--) {
                int &index = sum[bucket[0][i].keys[j]];
                bucket[1][--index] = bucket[0][i];
            }
            swap(bucket[0], bucket[1]);
        }
        for(j = i = 0;i < N;i++) {
            RA[bucket[0][i].index] = j;
            if(i + 1 < N) j += (bucket[0][i].keys[0] == bucket[0][i + 1].keys[0] && bucket[0][i].keys[1] == bucket[0][i + 1].keys[1] ? 0 : 1);
        }
    }
public:
    int RA[MAXN], SA[MAXN], LCP[MAXN];
    void Init() {
        int i, L, ans = 0;
        for(i = 0;i < N;i++) {
            bucket[0][i].keys[0] = 0;
            bucket[0][i].keys[1] = (data[i] ? 1 : 0);
            bucket[0][i].index = i;
        }
        radix_sort(2);
        for(L = 1;L < N;L <<= 1) {
            for(i = 0;i < N;i++) {
                bucket[0][i].keys[0] = RA[i];
                bucket[0][i].keys[1] = (i + L < N ? RA[i + L] + 1 : 0);
                bucket[0][i].index = i;
            }
            radix_sort(N + 1);
        }
        for(i = 0;i < N;i++) SA[i] = -1;
        for(i = 0;i < N;i++) SA[RA[i]] = i;
        for(i = 0;i < N;i++) {
            if(ans > 0) ans -= 1;
            if(RA[i] == 0) LCP[RA[i]] = 0;
            else {
                while(ans + SA[RA[i]] < N && ans + SA[RA[i] - 1] < N && data[ans + SA[RA[i]]] == data[ans + SA[RA[i] - 1]]) ans += 1;
                LCP[RA[i]] = ans;
            }
        }
    }
} SA;

class RangeMinQuery {
    int mini[MAXN][30];
public:
    void Init(int *data) {
        int i, j;
        for(i = 0;i < N;i++) mini[i][0] = data[i];
        for(j = 1;j < 30;j++) for(i = 0;i < N;i++) {
            mini[i][j] = mini[i][j - 1];
            if(i + (1 << (j - 1)) < N) mini[i][j] = min(mini[i][j], mini[i + (1 << (j - 1))][j - 1]);
        }
    }
    int Min(int l, int r) {
        int len = __lg(r - l);
        return min(mini[l][len], mini[r - (1 << len)][len]);
    }
} RMQ;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int i, temp, a, b;
    cin >> N >> Q;
    for(i = 0;i < N;i++) {
        cin >> temp;
        data[i] = (power(temp, (mod - 1) / 2) == 1);
    }
    SA.Init(); RMQ.Init(SA.LCP);
    while(Q--) {
        cin >> a >> b;
        if(a == b) cout << N - a << '\n';
        else {
            a = SA.RA[a]; b = SA.RA[b];
            if(a > b) swap(a, b);
            cout << RMQ.Min(a + 1, b + 1) << '\n';
        }
    }
}
