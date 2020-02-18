#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 3e2 + 5 ,INF = (1LL << 31) - 1 ,MAXM = 5e4 + 50;
struct e {
    int src ,dst;
    long long weight;
} edge[MAXM];
int N ,M;
int dsu[MAXN];
int boss(int i) { return (dsu[i] == i ? i : dsu[i] = boss(dsu[i])); }
void join(int a ,int b) {
    a = boss(a) ,b = boss(b);
    if(a == b) return;
    else dsu[a] = dsu[b];
}
bool cmp(e a ,e b) { return a.weight < b.weight; }
bool check(int thre) {
    int i ,j ,sum ,a ,b;
    bool able;
    for(i = 0;i < M;i++) {
        sum = N;
        for(j = 1;j <= N;j++) dsu[j] = j;
        for(j = i;j < M;j++) {
            able = false;
            if(edge[j].weight - edge[i].weight >= thre) {
                able = false;
                break;
            } else {
                a = boss(edge[j].src) ,b = boss(edge[j].dst);
                if(a != b) {
                    join(a ,b);
                    sum -= 1;
                    if(sum == 1) {
                        able = true;
                        break;
                    }
                }
            }
        }
        if(able) return true;
    }
    return false;
}
int main() {
    int L ,R ,mid;
    int i;
    while(cin >> N >> M) {
        for(i = 0;i < M;i++) cin >> edge[i].src >> edge[i].dst >> edge[i].weight;
        sort(edge ,edge + M ,cmp);
        L = 0 ,R = INF;
        while(L != R - 1) {
            mid = (L + R) / 2;
            if(check(mid)) R = mid;
            else L = mid;
        }
        cout << L << endl;
    }
}
