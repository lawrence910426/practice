#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;

#define N 100005
int p ,q;
vector<int> edges[N * 2];
int previous[N * 2] ,match[N * 2];
bool visit[N * 2];

inline int hungarian() {
    int ans = 0;
    int i;
    queue<int> next;
    bool done;
    memset(match ,-1 , sizeof(match));
    for(i = 1;i <= p + q;i++) {
        memset(visit ,0 ,sizeof(visit));
        memset(previous ,-1 ,sizeof(previous));
        if(match[i] == -1) {
            while(!next.empty()) next.pop();
            done = false;
            for(next.push(i);!next.empty() && !done;next.pop()) {
                for(int dest : edges[next.front()]) {
                    if(visit[dest]) continue;
                    if(match[dest] == -1) {
                        int iter = next.front();
                        while(iter != -1) {
                            int temp = match[iter];
                            match[iter] = dest;
                            match[dest] = iter;
                            dest = temp;
                            iter = previous[iter];
                        }
                        ans += 1;
                        done = true; break;
                    } else {
                        visit[dest] = true;
                        previous[match[dest]] = next.front();
                        next.push(match[dest]);
                    }
                }
            }
        }
    }
    return ans;
}

bool used[N];
inline void preprocess() {
    memset(used ,0 ,sizeof(used));
    for(int i = 1;i <= p;i++) {
        for(int q : edges[i]) {
            if(used[q]) continue;
            used[q] = true;
            match[q] = i;
            match[i] = q;
        }
    }
}

int main() {
    int T ,k;
    int eax ,ebx;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    for(cin >> T;T--;) {
        memset(edges ,0 ,sizeof(edges));
        cin >> p >> q >> k;
        while(k--) {
            cin >> eax >> ebx;
            ebx += p;
            edges[eax].push_back(ebx);
            edges[ebx].push_back(eax);
        }
        preprocess();
        cout << hungarian() << endl;
    }
}
