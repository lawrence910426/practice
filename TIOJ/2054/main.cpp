#pragma GCC optimize("Ofast")
#include <iostream>
#include <deque>
#include <algorithm>
#include <memory.h>

using namespace std;
const int MAXN = 3e3 + 50 ,MAXL = 1e6 + 50;
struct pt { int x ,y; } data[MAXN];
bool cmp(pt a ,pt b) { return a.x < b.x; }
struct seg { int lazy ,maxi; } segment[MAXL * 5];
void push_down(int id ,int l ,int r) {
    segment[id].maxi += segment[id].lazy;
    if(l != r - 1) {
        segment[id * 2].lazy += segment[id].lazy;
        segment[id * 2 + 1].lazy += segment[id].lazy;
    }
    segment[id].lazy = 0;
}
void modify(int id ,int l ,int r ,int ql ,int qr ,int weight) {
    push_down(id ,l ,r);
    if(qr <= l || r <= ql) return;
    if(ql <= l && r <= qr) {
        segment[id].lazy += weight;
        push_down(id ,l ,r);
    } else {
        modify(id * 2 ,l ,(l + r) / 2 ,ql ,qr ,weight);
        modify(id * 2 + 1 ,(l + r) / 2 ,r ,ql ,qr ,weight);
        segment[id].maxi = max(segment[id * 2].maxi ,segment[id * 2 + 1].maxi);
    }
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,H ,W ,ans;
    int i ,pos ,lptr ,rptr;
    while(cin >> N >> H >> W) {
        memset(segment ,0 ,sizeof(segment));
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y;
        sort(data ,data + N ,cmp);
        deque<int> sweep;
        for(ans = pos = lptr = rptr = 0;pos < MAXL;pos++) {
            while(rptr < N && data[rptr].x <= pos + W) {
                sweep.push_back(rptr);
                modify(1 ,0 ,MAXL ,data[rptr].y ,data[rptr].y + H + 1 ,1);
                rptr += 1;
            }
            while(lptr <= rptr && data[lptr].x < pos) {
                sweep.pop_front();
                modify(1 ,0 ,MAXL ,data[lptr].y ,data[lptr].y + H + 1 ,-1);
                lptr += 1;
            }
            ans = max(ans ,segment[1].maxi);
        }
        cout << ans << '\n';
    }
}
