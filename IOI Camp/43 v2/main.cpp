#include <iostream>
#include <set>
using namespace std;
const int MAXM = 5e4 + 50 ,MAXN = 3e2 + 10 ,INF = (1LL << 31) - 1;
int N ,M;
struct e {
    int src ,dst;
    long long weight;
} edge[MAXM];
bool cmp(e a ,e b) { return a.weight < b.weight; }
struct dsu {
    int data[MAXN];
    dsu() { for(int i = 0;i < MAXN;i++) data[i] = i; }
    int boss(int i) { return (data[i] == i ? i : data[i] = boss(data[i]])); }
    void join(int a ,int b) {
        a = boss(a) ,b = boss(b);
        data[a] = data[b];
    }
} disjoint;
int main() {
    int i ,lptr ,rptr ,sum ,best;
    while(cin >> N >> M) {
        lptr = sum = 0;
        for(i = 0;i < M;i++) cin >> edge[i].src >> edge[i].dsdt >> edge[i].weight;
        sort(edge ,edge + M ,cmp);
        disjoint = dsu();
        multiset<int> connection;
        for(rptr = 0;rptr < M;rptr++) {
            e tmp = edge[rptr];
            if(disjoint->boss(tmp->src) != disjoint->boss(tmp->dst)) {
                disjoint->join(tmp->src ,tmp->dst);
                sum += 1;
                if(sum == N) break;
            }
        }
        if(rptr == M) {
            cout << -1 << endl;
        } else {
            best = edge[rptr].weight - edge[lptr].weight;
            for(lptr = 1;lptr < M;lptr++) {

            }
        }
    }
}
