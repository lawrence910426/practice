#include <iostream>
#include <random>
#include <time.h>
#include <set>
using namespace std;
const int MAXN = 3e5 ,MAXM = 65536;
int times ,i ,j ,x[MAXN] ,y[MAXN] ,mirror[MAXN] ,r ,r2 ,rr ,ans[MAXM];
long long sumx ,sumy;
int query(int i) { return (mirror[i] == i ? i : mirror[i] = query(mirror[i])); }
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    srand(time(0));
    for(i = 0;i < MAXN;i++) {
        cin >> x[i] >> y[i];
        x[i] %= MAXM ,y[i] %= MAXM;
    }
    for(i = 0;i < MAXM;i++) mirror[i] = i;
    sumx = sumy = 0;
    for(i = 0;i < MAXM;i++) {
        r = rand() % MAXN ,r2 = rand() % MAXN;
        r = query(r);
        sumx += x[r] ,sumy += y[r];
        mirror[r] = query(r2);
        ans[i] = r;
    }
    sumx %= MAXM ,sumy %= MAXM;
    for(times = 0;times < 10000;times++) {
        rr = rand() % MAXM;
        sumx -= x[ans[rr]] ,sumy -= y[ans[rr]];

        r = rand() % MAXN ,r2 = rand() % MAXN;
        sumx += x[r] ,sumy += y[r];
        //r = query(r);
        //mirror[r] = query(r2);
        ans[rr] = r;

        sumx = (sumx + MAXM) % MAXM ,sumy = (sumy + MAXM) % MAXM;
        if(sumx % MAXM == 0 && sumy % MAXM == 0) {
            for(j = 0;j < MAXM;j++) cout << ans[j] + 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
