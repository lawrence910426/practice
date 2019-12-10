#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <memory.h>
#include <assert.h>
#include <algorithm>

using namespace std;
const int MAXD = 30 ,MAXN = 2e5 + 50;
int N ,Q;
struct seg {
    int l ,r;
    seg() {}
    seg(int L ,int R) :l(L) ,r(R) {}
    bool operator< (seg s) { return l < s.l; }
};
class digit {
public:
    bool able[MAXN] ,ans[MAXN];
    int prefix[MAXN];
    vector<seg> q0 ,q1;
    int i ,j ,lptr ,rptr;
    void init() {
        q0 = vector<seg>();
        q1 = vector<seg>();
        prefix[0] = 0;
        memset(able ,-1 ,sizeof(able));
        memset(ans ,0 ,sizeof(ans));
    }
    /* [l ,r) mode */
    void insert_seg(int l ,int r ,bool style) {
        if(style == false) q0.push_back(seg(l ,r));
        else q1.push_back(seg(l ,r));
    }
    void update() { for(int ptr = lptr;ptr < rptr;ptr++) if(able[ptr]) { ans[ptr] = true; break; } }
    void run() {
        sort(q0.begin() ,q0.end()), sort(q1.begin() ,q1.end());
        lptr = 0 ,rptr = 0;
        for(seg segment : q0) {
            for(j = max(segment.l ,rptr);j < segment.r;j++) able[j] = false;
            rptr = max(rptr ,segment.r);
        }
        for(i = 1;i < N + 1;i++) prefix[i] = prefix[i - 1] + (able[i - 1] ? 1 : 0);
        lptr = rptr = -1;
        for(seg segment : q1) {
            assert(prefix[segment.r] > prefix[segment.l]);
            if(lptr == -1 && rptr == -1) {
                lptr = segment.l, rptr = segment.r;
            } else if(rptr <= segment.l) {
                update(), lptr = segment.l, rptr = segment.r;
            } else if(rptr <= segment.r) {
                if(prefix[rptr] > prefix[segment.l]) {
                    lptr = segment.l;
                } else {
                    update(), lptr = segment.l, rptr = segment.r;
                }
            } else if(segment.r < rptr) {
                lptr = segment.l, rptr = segment.r;
            }
        }
        update();
    }
} data[MAXD];

long long ans;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,j ,l ,r ,v;
    while(cin >> N >> Q) {
        for(i = 0;i < MAXD;i++) data[i].init();
        while(Q--) {
            cin >> l >> r >> v;
            for(i = 0;i < MAXD;i++) data[i].insert_seg(l - 1 ,r ,(v >> i) & 1);
        }
        for(i = 0;i < MAXD;i++) data[i].run();
        for(i = 0;i < N;i++) {
            ans = 0;
            for(j = 0;j < MAXD;j++) if(data[j].ans[i]) ans += (1LL << j);
            cout << ans << " ";
        }
        cout << '\n';
    }
}
