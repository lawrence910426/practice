#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>
using namespace std;

const int MAXN = 100005;
const long long INF = (1LL << 60) - 1;
vector<pair<int ,int> > seg[MAXN];
long long zkw[MAXN * 5];
int N ,M ,leaf;

inline long long query(int l ,int r) {
    long long ans = INF;
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1, r >>= 1) {
        if(l % 2 == 0) ans = min(ans ,zkw[l ^ 1]);
        if(r % 2 == 1) ans = min(ans ,zkw[r ^ 1]);
    }
    return ans;
}

void update(int pos ,long long value) {
    pos += leaf + 1;
    zkw[pos] = value;
    for(pos >>= 1;pos != 1;pos >>= 1) zkw[pos] = min(zkw[pos * 2] ,zkw[pos * 2 + 1]);
}

int main() {
    int i ,l ,r ,c;
    long long tmp;
    while(cin >> N >> M) {
        for(i = 0;i < MAXN;i++) seg[i] = vector<pair<int ,int> >();
        for(i = 0;i < MAXN * 5;i++) zkw[i] = INF;
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        update(0 ,0);
        while(M--) {
            cin >> l >> r >> c;
            seg[r].push_back(pair<int ,int>(l ,c));
        }
        for(i = 1;i <= N;i++) for(auto item : seg[i]) {
            l = item.first - 1 ,r = i ,c = item.second;
            tmp = query(l ,r);
            if(tmp + c < query(r - 1 ,r)) update(r - 1 ,tmp + c);
        }
        tmp = query(N - 1 ,N);
        cout << (tmp == INF ? -1 : tmp) << endl;
    }
}
