#include <iostream>
#include <memory.h>
#include <stack>
#include <vector>
#include <set>

using namespace std;

vector<int> edges[5005];
bool visit[5005] ,removed[5005];
int degree[5005];

int mindeg(int on) {
    int ans = (1LL << 31) - 1;
    visit[on] = true;
    for(int next : edges[on]) {
        if(removed[next]) continue;
        degree[on] += 1;
        if(visit[next]) continue;
        ans = min(ans ,mindeg(next));
    }
    return min(ans ,degree[on]);
}

int boss[5005];
int amount[5005];
int find(int on) {
    if(boss[on] == on) return on;
    return boss[on] = find(boss[on]);
}
void merge(int a ,int b) {
    a = find(a) ,b = find(b);
    if(a == b) return;
    amount[a] += amount[b];
    boss[b] = boss[a];
}

int main() {
    int N ,M ,deg ,left ,ans;
    int i ,j ,eax ,ebx;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> M) {
        for(i = 0;i < 5005;i++) {
            edges[i] = vector<int>();
            amount[i] = 1;
            boss[i] = i;
        }

        for(i = 0;i < M;i++) {
            cin >> eax >> ebx;
            edges[eax].push_back(ebx);
            edges[ebx].push_back(eax);
            degree[eax] += 1;
            degree[ebx] += 1;
        }

        stack<pair<int ,int> > seq;
        memset(removed ,0 ,sizeof(removed));
        for(left = N;left != 0; ) {
            memset(visit ,0 ,sizeof(visit));
            for(i = 1;i <= N;i++) {
                if(visit[i] || removed[i]) continue;
                deg = (1LL << 31) - 1;
                for(j = 1;j <= N;j++) if(!removed[j]) deg = min(deg ,degree[j]);
                for(j = 1;j <= N;j++) if(!removed[j] && degree[j] == deg) {
                    removed[j] = true;
                    left -= 1;
                    seq.push(pair<int ,int>(j ,deg));
                    for(int V : edges[j]) degree[V] -= 1;
                    degree[j] = 0;
                    break;
                }
            }
        }

        for(ans = 0;!seq.empty();seq.pop()) {
            int U = seq.top().first;
            removed[U] = false;
            for(int V : edges[U]) {
                if(removed[V]) continue;
                merge(U ,V);
                int size = amount[find(U)];
                int minedge = seq.top().second;
                ans = max(ans ,size * minedge);
            }
        }
        cout << ans << endl;
    }
}
