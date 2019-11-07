#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 5e5 + 10;
struct art {
    long long int volume ,beauty;
    bool operator< (art& i) { return volume < i.volume; }
}item[MAXN];
int N ,prefix_beauty[MAXN];
int zkw[MAXN * 5] ,leaf;

inline int merge(int l ,int r) {
    if(l == -1 && r == -1) return -1;
    else if(l == -1 && r != -1) return r;
    else if(l != -1 && r == -1) return l;
    else return (item[l].volume - prefix_beauty[l] > item[r].volume - prefix_beauty[r] ? l : r);
}

inline void build() {
    int i;
    memset(zkw ,-1 ,sizeof(zkw));
    for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
    for(i = leaf + 1;i < leaf + 1 + N;i++) zkw[i] = i - leaf - 1;
    for(i = leaf - 1;i >= 1;i--) zkw[i] = merge(zkw[i * 2] ,zkw[i * 2 + 1]);
}

inline int query(int l ,int r) {
    if(l == r - 1) return l;
    int ans = -1;
    for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
        if(l % 2 == 0) ans = merge(ans ,zkw[l + 1]);
        if(r % 2 == 1) ans = merge(ans ,zkw[r - 1]);
    }
    return ans;
}

int main() {
    int i ,tmp;
    long long int ans;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> item[i].volume >> item[i].beauty;
        sort(item ,item + N);
        prefix_beauty[0] = 0;
        for(i = 1;i <= N;i++) prefix_beauty[i] = prefix_beauty[i - 1] + item[i - 1].beauty;
        build();
        ans = 0;
        for(i = 0;i < N;i++) {
            tmp = query(0 ,i + 1);
            ans = max(ans ,prefix_beauty[i + 1] - prefix_beauty[tmp] + item[tmp].volume - item[i].volume);
        }
        cout << ans << endl;
    }
}
