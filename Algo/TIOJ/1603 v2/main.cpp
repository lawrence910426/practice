#include <iostream>
#include <memory.h>
#include <assert.h>

#define MAXN 100005
#define MAXIMUM (1LL << 60)
#define MINIMUM (-1)
using namespace std;
long long int seg[MAXN * 10][2] ,eax;
void modify(int l ,int r ,int id ,int pos ,long long int val) {
    if(l == pos && l == r - 1) {
        seg[id][0] = seg[id][1] = val;
        return;
    }
    int center = (l + r) / 2;
    if(l <= pos && pos < center) modify(l ,center ,id * 2 ,pos, val);
    else modify(center ,r ,id * 2 + 1 ,pos, val);
    seg[id][0] = max(seg[id * 2][0] ,seg[id * 2 + 1][0]);
    seg[id][1] = min(seg[id * 2][1] ,seg[id * 2 + 1][1]);
}

int ql ,qr;
long long int query_max(int L ,int R ,int id) {
    if(ql <= L && R <= qr) return seg[id][0];
    if(qr < L || R <= ql) return MINIMUM;
    if(L == R - 1) return MINIMUM;
    int center = (L + R) / 2;
    long long maxi = MINIMUM;
    maxi = max(maxi ,query_max(L ,center ,id * 2));
    maxi = max(maxi ,query_max(center ,R ,id * 2 + 1));
    return maxi;
}

long long int query_min(int L ,int R ,int id) {
    if(ql <= L && R <= qr) return seg[id][1];
    if(qr < L || R <= ql) return MAXIMUM;
    if(L == R - 1) return MAXIMUM;
    int center = (L + R) / 2;
    long long int mini = MAXIMUM;
    mini = min(mini ,query_min(L ,center ,id * 2));
    mini = min(mini ,query_min(center ,R ,id * 2 + 1));
    return mini;
}

int main() {
    int N ,Q;
    int i;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    cin >> N >> Q;
    memset(seg ,0 ,sizeof(seg));
    for(i = 0;i < N;i++) {
        cin >> eax;
        modify(0 ,N ,1 ,i ,eax);
    }
    while(Q--) {
        cin >> ql >> qr;
        //assert(1 <= ql && ql <= qr && qr <= N);
        ql -= 1;
        cout << query_max(0 ,N ,1) - query_min(0 ,N ,1) << endl;
    }
}
/*
8 3
5 7 3 1 9 7 10 11
1 5
1 8
6 8
*/
