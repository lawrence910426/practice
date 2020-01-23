#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
const int MAXN = 3e2 + 5 ,MAXM = 1e5 + 50 ,INF = (1LL << 31) - 1;
struct edge { int src ,dst ,val ,id; } data[MAXM * 2];
bool cmp(edge a ,edge b) { return a.val < b.val; }
set<int> T[MAXN];
int N ,M ,heads ,ans;
int cut_min(int parent ,int pos ,int target ,int mini) {
    if(pos == target) return mini;
    for(int item : T[pos]) {
        edge e = data[item];
        if(e.dst == parent) continue;
        int ans = cut_min(e.src ,e.dst ,target ,min(mini ,e.id));
        if(ans == INF) continue;
        if(ans == e.id) {
            T[e.src].erase(item);
            T[e.dst].erase((item >= M ? item - M : item + M));
        }
        return ans;
    }
    return INF;
}
int main() {
    int i ,lptr ,rptr;
    while(cin >> N >> M) {
        for(i = 0;i < MAXN;i++) T[i].clear();
        for(i = 0;i < M;i++) cin >> data[i].src >> data[i].dst >> data[i].val;
        sort(data ,data + M ,cmp);
        for(i = 0;i < M;i++) {
            data[i + M].src = data[i].dst;
            data[i + M].dst = data[i].src;
            data[i + M].val = data[i].val;
            data[i + M].id = data[i].id = i;
        }
        set<int> edge_codes;
        for(rptr = 0 ,heads = N;rptr < M && heads != 1;rptr++) {
            int cut = cut_min(-1 ,data[rptr].src ,data[rptr].dst ,INF);
            if(cut == INF) heads -= 1;
            else edge_codes.erase(cut);
            T[data[rptr].src].insert(rptr);
            T[data[rptr].dst].insert(rptr + M);
            edge_codes.insert(rptr);
        }
        ans = INF;
        for(lptr = 0;lptr < M;lptr++) {
            int mini = *edge_codes.begin();
            while(*edge_codes.begin() < lptr && rptr < M) {
                int cut = cut_min(-1 ,data[rptr].src ,data[rptr].dst ,INF);
                if(cut == INF) return -1;
                edge_codes.erase(cut);
                T[data[rptr].src].insert(rptr);
                T[data[rptr].dst].insert(rptr + M);
                edge_codes.insert(rptr);
                rptr += 1;
            }
            if(*edge_codes.begin() < lptr) break;
            ans = min(ans ,data[rptr - 1].val - data[lptr].val);
        }
        cout << ans << endl;
    }
}
