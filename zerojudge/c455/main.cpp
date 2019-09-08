#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

#define N 100005
vector<int> edges[N + N];
int previous[N + N] ,visit[N + N] ,match[N + N];
int p ,q, k;

int hungarian() {
    int i ,ans = 0;
    bool done;
    queue<int> next;
    memset(match ,0 ,sizeof(match));
    for(i = 1;i <= p + q;i++) {
        if(!match[i]) {
            memset(visit ,0 ,sizeof(visit));
            memset(previous ,-1 ,sizeof(previous));
            while(!next.empty()) next.pop();
            next.push(i);
            done = false;
            while(!next.empty() && !done) {
                visit[next.front()] = true;
                for(int to : edges[next.front()]) {
                    if(!visit[to]) {
                        //previous[to] = next.front();
                        if(match[to]) {
                            next.push(to);
                        } else {
                            /*while(to != -1) {
                                match[to] = true;
                                to = previous[to];
                            }*/
                            ans += 1;
                            match[to] = match[i] = true;
                            done = true; break;
                        }
                    }
                }
                next.pop();
            }
        }
    }
    return ans;
}

int main() {
    int T;
    int i ,eax ,ebx;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
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
