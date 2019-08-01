#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <bitset>

using namespace std;

#define N 100005

vector<int> edges[N * 2];
bitset<N * 2> visit;
int match[N * 2];
int p ,q ,ans;

void preprocess() {
    visit.reset();
    for(int i = 1;i <= p;i++) {
        for(int q : edges[p]) {
            if(visit[q]) continue;
            visit[q] = true;
            match[i] = q;
            match[q] = i;
            ans += 1;
            break;
        }
    }
}

bool dfs(int from) {
    for(int next : edges[from]) {
        if(visit[next]) continue;
        visit[next] = true;
        if(match[next] == -1 || dfs(match[next])) {
            match[next] = from;
            match[from] = next;
            return true;
        }
    }
    return false;
}

int hungarian() {
    ans = 0;
    memset(match ,-1 ,sizeof(match));
    preprocess();
    for(int i = 1;i <= p;i++) {
        if(match[i] == -1) {
            visit.reset();
            if(dfs(i)) ans += 1;
        }
    }
    return ans;
}

int main() {
    int T ,k;
    int i ,eax ,ebx;
    ios::sync_with_stdio(false) ,cin.tie(0) ,cout.tie(0);
    for(cin >> T;T--;) {
        cin >> p >> q >> k;
        memset(edges ,0 ,sizeof(edges));
        for(i = 0;i < k;i++) {
            cin >> eax >> ebx;
            ebx += p;
            edges[eax].push_back(ebx);
            edges[ebx].push_back(eax);
        }
        cout << hungarian() << endl;
    }
}
