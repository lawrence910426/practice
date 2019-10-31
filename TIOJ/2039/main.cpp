#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <queue>
#include <stack>
using namespace std;
const int MAXN = 2e6+50;
int N ,K ,raw[MAXN] ,leaf;
long long int ans;
struct seg {
    int L ,R ,value ,LL ,RR;
    bool style;
    inline seg(): L(0) ,R(0) ,value(0) ,style(false) {}
    inline seg(int l ,int r, int v): L(l) ,R(r) ,value(v) {}
    inline seg(seg s ,int ll ,int rr ,bool st): LL(ll) ,RR(rr) ,style(st) ,L(s.L) ,R(s.R) ,value(s.value) {}
    inline bool operator< (const seg& s) const { return value < s.value; }
};
inline seg max(seg a ,seg b ,seg c) { return max(a ,max(b, c)); }
struct zkw {
    int mini ,maxi;
    seg LR ,RL;
    inline zkw(): mini(-1) ,maxi(-1) ,LR(seg(-1 ,-1 ,0)) ,RL(seg(-1 ,-1 ,0)) {}
    inline zkw(int i): mini(i) ,maxi(i) ,LR(seg(i ,i ,0)) ,RL(seg(i ,i ,0)) {}
    inline zkw(zkw a ,zkw b) {
        if(a.mini == -1) mini = b.mini ,maxi = b.maxi ,LR = b.LR ,RL = b.RL;
        if(b.mini == -1) mini = a.mini ,maxi = a.maxi ,LR = a.LR ,RL = a.RL;
        if(a.mini == -1 || b.mini == -1) return;
        mini = (raw[a.mini] < raw[b.mini] ? a.mini : b.mini);
        maxi = (raw[a.maxi] > raw[b.maxi] ? a.maxi : b.maxi);
        LR = max(seg(a.maxi ,b.mini ,raw[a.maxi] - raw[b.mini]) ,a.LR ,b.LR);
        RL = max(seg(a.mini ,b.maxi ,raw[b.maxi] - raw[a.mini]) ,a.RL ,b.RL);
    }
}tree[MAXN * 3];
inline zkw query(int L ,int R) {
    auto left = queue<int>();
    auto right = stack<int>();
    for(L += leaf ,R += leaf + 1;L ^ R ^ 1;L >>= 1 ,R >>= 1) {
        if(L % 2 == 0) left.push(L ^ 1);
        if(R % 2 == 1) right.push(R ^ 1);
    }
    zkw ans = zkw();
    for(;!left.empty();left.pop()) ans = zkw(ans ,tree[left.front()]);
    for(;!right.empty();right.pop()) ans = zkw(ans ,tree[right.top()]);
    return ans;
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i;
    priority_queue<seg> pq = priority_queue<seg>();
    cin >> N >> K;
    for(i = 0;i < N;i++) cin >> raw[i];
    for(leaf = 1;leaf < N + 2;leaf <<= 1) ;
    for(i = 0;i < MAXN * 3;i++) tree[i] = zkw();
    for(i = leaf + 1;i < leaf + 1 + N;i++) tree[i] = zkw(i - leaf - 1);
    for(i = leaf - 1;i >= 1;i--) tree[i] = zkw(tree[i * 2] ,tree[i * 2 + 1]);
    pq.push(seg(query(0 ,N).RL ,0 ,N ,false));
    for(ans = 0;!pq.empty() && K--;) {
        seg s = pq.top();
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
    cout << ans << '\n';
}
