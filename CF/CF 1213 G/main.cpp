#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 200005
long long int dsu[MAXN] ,amount[MAXN];
struct edge {
    int src ,dst ,weight;
}data[MAXN];

struct answer {
    int weight ,code;
}queries[MAXN];
long long int raw_ans[MAXN];

int boss(int i) {
    if(dsu[i] == i) return i;
    return dsu[i] = boss(dsu[i]);
}

inline void combine(int a ,int b ,long long int& ans) {
    int ba = boss(a) ,bb = boss(b);
    ans -= amount[ba] * (amount[ba] - 1) / 2;
    ans -= amount[bb] * (amount[bb] - 1) / 2;
    amount[bb] += amount[ba];
    ans += amount[bb] * (amount[bb] - 1) / 2;
    dsu[a] = dsu[b] = dsu[ba] = dsu[bb];
}

bool sort_ans(answer a ,answer b) {
    return a.weight < b.weight;
}

bool sort_edge(edge a ,edge b) {
    return a.weight < b.weight;
}

int main() {
    int N ,Q;
    long long int ans;
    edge tmp;
    int i ,ptr ,j;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    cin >> N >> Q;
    for(i = 0;i < MAXN;i++) {
        dsu[i] = i;
        amount[i] = 1;
    }
    for(i = 0;i < N - 1;i++) cin >> data[i].src >> data[i].dst >> data[i].weight;
    for(i = 0;i < Q;i++) {
        cin >> queries[i].weight;
        queries[i].code = i;
    }
    sort(data ,data + N - 1 ,sort_edge);
    sort(queries ,queries + Q ,sort_ans);
    for(ans = ptr = i = 0;i < Q;i++) {
        while(ptr < N - 1 && data[ptr].weight <= queries[i].weight) {
            combine(data[ptr].src ,data[ptr].dst ,ans);
            ptr++;
        }
        raw_ans[queries[i].code] = ans;
    }
    for(i = 0;i < Q;i++) cout << raw_ans[i] << " ";
    cout << endl;
}
