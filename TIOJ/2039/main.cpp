#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <queue>
using namespace std;
const int MAXN = 2e6+50;
int N ,K ,raw[MAXN] ,leaf ,ans;
struct seg {
    int L ,R ,value ,LL ,RR;
    bool style;
    inline seg(): L(0) ,R(0) ,value(0) ,style(false) {}
    inline seg(int l ,int r, int v): L(l) ,R(r) ,value(v) {}
    inline seg(seg s ,int ll ,int rr ,bool st): LL(ll) ,RR(rr) ,style(st) ,L(s.L) ,R(s.R) ,value(s.value) {}
    inline bool operator< (const seg& s) const { return value < s.value; }
    inline bool operator> (const seg& s) const { return value > s.value; }
};
inline seg max(seg a ,seg b ,seg c) { return max(a ,max(b, c)); }
struct zkw {
    int mini ,maxi;
    seg LR ,RL;
    inline zkw() {}
    inline zkw(zkw a ,zkw b) {
        mini = (raw[a.mini] < raw[b.mini] ? a.mini : b.mini);
        maxi = (raw[a.maxi] > raw[b.maxi] ? a.maxi : b.maxi);
        LR = max(seg(a.maxi ,b.mini ,raw[a.maxi] - raw[b.mini]) ,a.LR ,b.LR);
        RL = max(seg(a.mini ,b.maxi ,raw[b.maxi] - raw[a.mini]) ,a.RL ,b.RL);
    }
} tree[MAXN * 4];
inline zkw query(int L ,int R) {
    zkw ans = tree[L + leaf + 1];
    for(L += leaf ,R += leaf + 1;L ^ R ^ 1;L >>= 1 ,R >>= 1) {
        if(L % 2 == 0) ans = zkw(ans ,tree[L + 1]);
        if(R % 2 == 1) ans = zkw(ans ,tree[R - 1]);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,left ,right;
    seg s;
    priority_queue<seg> pq;
    while(cin >> N >> K) {
        for(i = 0;i < N;i++) cin >> raw[i];
        memset(tree ,0 ,sizeof(tree));
        for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
        for(i = leaf + 1;i < leaf + 1 + N;i++) {
            tree[i].mini = tree[i].maxi = i - leaf - 1;
            tree[i].LR = seg(i - leaf - 1 ,i - leaf - 1 ,0);
            tree[i].RL = seg(i - leaf - 1 ,i - leaf - 1 ,0);
        }
        for(i = leaf - 1;i >= 1;i--) tree[i] = zkw(tree[i * 2] ,tree[i * 2 + 1]);
        pq = priority_queue<seg>();
        pq.push(seg(query(0 ,N).RL ,0 ,N ,false));
        for(ans = 0;!pq.empty() && K--;) {
            s = pq.top();
            pq.pop();
            ans += s.value;
            if(s.style) {
                if(s.LL + 1 != s.L) pq.push(seg(query(s.LL ,s.L).LR ,s.LL ,s.L ,true));
                if(s.L + 1 != s.R) pq.push(seg(query(s.L ,s.R).RL ,s.L ,s.R ,false));
                if(s.R + 1 != s.RR) pq.push(seg(query(s.R ,s.RR).LR ,s.R ,s.RR ,true));
            } else {
                if(s.LL + 1 != s.L) pq.push(seg(query(s.LL ,s.L).RL ,s.LL ,s.L ,false));
                if(s.L + 1 != s.R) pq.push(seg(query(s.L ,s.R).LR ,s.L ,s.R ,true));
                if(s.R + 1 != s.RR) pq.push(seg(query(s.R ,s.RR).RL ,s.R ,s.RR ,false));
            }
        }
        cout << ans << endl;
    }
}
