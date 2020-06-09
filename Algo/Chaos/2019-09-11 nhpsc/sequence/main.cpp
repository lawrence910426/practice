#include <iostream>
#include <algorithm>
#include <memory.h>
#include <assert.h>

using namespace std;
const int MAXN = 5e5 + 50;
struct query {
    int l ,r ,val;
    bool operator< (query Q) { return l < Q.l; }
} data[MAXN];
bool ans[MAXN] ,able[MAXN];

int N ,Q ,lptr ,rptr;
int i;
void update() {

}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> Q) {
        for(i = 0;i < Q;i++) cin >> data[i].l >> data[i].r >> data[i].val;
        for(i = 0;i < Q;i++) data[i].l -= 1;
        sort(data ,data + Q);
        memset(ans ,0 ,sizeof(ans));
        memset(able ,-1 ,sizeof(able));
        lptr = rptr = -1;
        for(i = 0;i < Q;i++) {
            if(data[i].val == 1) {
                if(lptr == -1) {
                    lptr = data[i].l;
                    rptr = data[i].r;
                } else if(rptr <= data[i].l) {
                    update();
                    lptr = data[i].l;
                    rptr = data[i].r;
                } else if(data[i].r <= rptr) {
                    lptr = data[i].l;
                    rptr = data[i].r;
                } else if(rptr <= data[i].r) {
                    lptr = data[i].l;
                }
            } else {
                if(lptr == -1) ;
                else if(data[i].r < rptr) {
                    lptr = data[i].r;
                } else if(rptr <= data[i].r) {
                    update();
                    lptr = rptr = -1;
                    badrptr = max(badrptr ,data[i].r);
                }
            }
        }
        update();
        for(i = 0;i < N;i++) cout << ans[i] << " ";
        cout << endl;
    }
}
/*
6 5
1 2 1
2 3 1
3 5 1
1 4 1
5 6 1
*/
