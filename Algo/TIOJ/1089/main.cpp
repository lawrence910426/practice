#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

#define MAXN 500
vector<int> edges[1005];
int N ,K ,match[1005];
bool visit[1005];
bool hungarian(int on) {
    if(visit[on]) return false;
    visit[on] = true;
    for(int val : edges[on]) {
        if(match[val] == -1 || hungarian(match[val])) {
            match[val] = on;
            match[on] = val;
            return true;
        }
    }
    return false;
}


int main() {
    int x ,y ,ans;
    int i;
    while(cin >> N >> K) {
        for(i = 0;i < 1005;i++) edges[i] = vector<int>();
        memset(match ,-1 ,sizeof(match));
        while(K--) {
            cin >> x >> y;
            edges[x].push_back(MAXN + y);
        }
        ans = 0;
        for(i = 1;i <= N;i++) {
            memset(visit ,0 ,sizeof(visit));
            if(hungarian(i)) ans += 1;
        }
        cout << ans << endl;
    }
}
