#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <assert.h>

using namespace std;
const int MAXN = 5e5 + 50 ,MAXD = 31;
struct seg { int l ,r; };
struct digit {
    bool able[MAXN] ,ans[MAXN];
    int prefix[MAXN] ,nq0 ,nq1;
    seg q0[MAXN] ,q1[MAXN];
} answer[MAXD];
bool cmp(seg s1 ,seg s2) { return s1.l < s2.l; }
int i ,j ,D ,l ,r ,v;
int N ,Q ,lptr ,rptr;
long long ans;

void update() { for(j = lptr;j < rptr;j++) if(answer[D].able[j]) { answer[D].ans[j] = true; break; } }
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> Q) {
        for(D = 0;D < MAXD;D++) {
            answer[D].nq0 = answer[D].nq1 = 0;
            for(j = 0;j < MAXN;j++) {
                answer[D].able[j] = true;
                answer[D].ans[j] = false;
                answer[D].prefix[j] = 0;
            }
        }
        for(i = 0;i < Q;i++) {
            cin >> l >> r >> v;
            for(D = 0;D < MAXD;D++ ,v >>= 1) {
                if(v % 2 == 0) {
                    answer[D].q0[answer[D].nq0].l = l - 1;
                    answer[D].q0[answer[D].nq0].r = r;
                    answer[D].nq0 += 1;
                } else {
                    answer[D].q1[answer[D].nq1].l = l - 1;
                    answer[D].q1[answer[D].nq1].r = r;
                    answer[D].nq1 += 1;
                }
            }
        }
        for(D = 0;D < MAXD;D++) {
            sort(answer[D].q0 ,answer[D].q0 + answer[D].nq0 ,cmp);
            sort(answer[D].q1 ,answer[D].q1 + answer[D].nq1 ,cmp);
        }

        /* [lptr ,rptr) means finished process */
        lptr = 0 ,rptr = 0;
        for(D = 0;D < MAXD;D++) for(i = 0;i < answer[D].nq0;i++) {
            for(j = max(rptr ,answer[D].q0[i].l);j < answer[D].q0[i].r;j++)
                answer[D].able[j] = false;
            rptr = max(rptr ,answer[D].q0[i].r);
        }
        for(D = 0;D < MAXD;D++) for(i = 1;i < N + 1;i++)
            answer[D].prefix[i] = answer[D].prefix[i - 1] + (answer[D].able[i - 1] ? 1 : 0);

        /* [lptr ,rptr] means the segment want to be popped. */
        for(D = 0;D < MAXD;D++) for(i = 0;i < answer[D].nq1;i++) {
            if(i == 0) {
                lptr = answer[D].q1[i].l;
                rptr = answer[D].q1[i].r;
            } else if(rptr <= answer[D].q1[i].l) {
                update();
                lptr = answer[D].q1[i].l;
                rptr = answer[D].q1[i].r;
            } else if(answer[D].q1[i].r <= rptr) {
                lptr = answer[D].q1[i].l;
                rptr = answer[D].q1[i].r;
            } else if(rptr < answer[D].q1[i].r) {
                if(answer[D].prefix[rptr] - answer[D].prefix[answer[D].q1[i].l] > 0) {
                    lptr = answer[D].q1[i].l;
                } else {
                    update();
                    lptr = answer[D].q1[i].l;
                    rptr = answer[D].q1[i].r;
                }
            }
            assert(answer[D].prefix[rptr] -answer[D]. prefix[lptr] > 0);
        }
        update();

        for(i = 0;i < N;i++) {
            ans = 0;
            for(D = 0;D < MAXN;D++) if(answer[D].ans[i]) ans += (1LL << D);
            cout << ans << endl;
        }
        cout << '\n';
    }
}
/*
6 5
1 2 1
2 3 1
3 5 0
1 4 1
5 6 1

6 5
1 2 1
2 3 1
3 5 1
1 4 1
5 6 1
*/
