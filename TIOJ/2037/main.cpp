#include <iostream>
#include <vector>
#include <memory.h>

#define MAXN 100005
using namespace std;
int p ,q, k ,match[MAXN + MAXN] ,ans;
vector<int> edges[MAXN + MAXN];
bool visit[MAXN + MAXN];

bool hungarian(int on) {
    if(visit[on]) return false;
    visit[on] = true;
    for(int val : edges[on]) {
        visit[on] = true;
        if(match[val] == -1 || hungarian(match[val])) {
            match[val] = on;
            match[on] = val;
            return true;
        }
    }
    return false;
}

void greedy() {
    for(int i = 1;i <= p;i++) for(int val : edges[i]) {
        if(match[val] == -1 && match[i]) {
            match[val] = i;
            match[i] = val;
            ans += 1;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int T;
    int i ,x ,y;
    for(cin >> T;T--;) {
        cin >> p >> q >> k;
        for(i = 0;i < MAXN + MAXN;i++) edges[i] = vector<int>();
        memset(match ,-1 ,sizeof(match));
        for(i = 0;i < k;i++) {
            cin >> x >> y;
            edges[x].push_back(y + MAXN);
            edges[y + MAXN].push_back(x);
        }
        ans = 0;
        greedy();
        for(i = 1;i <= p;i++) {
            memset(visit ,0 ,sizeof(visit));
            if(hungarian(i)) ans += 1;
        }
        cout << ans << endl;
    }
}
