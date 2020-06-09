#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <memory.h>

using namespace std;
const int MAXN = 1e3 ,MAXM = 50;
vector<int> G[MAXN];
int match[MAXN] ,ans;

int codec(string b) {
    if(b == "XS") return 0;
    if(b == "S") return 1;
    if(b == "M") return 2;
    if(b == "L") return 3;
    if(b == "XL") return 4;
    if(b == "XXL") return 5;
}

bitset<MAXN> visit;
bool hungarian(int on) {
    if(visit[on]) return false;
    visit[on] = true;
    for(int V : G[on]) {
        if(match[V] == -1 || hungarian(match[V])) {
            match[V] = on;
            match[on] = V;
            return true;
        }
    }
    return false;
}

int main() {
    int N ,M;
    int i ,j ,ca ,cb;
    string a ,b;
    while(cin >> N >> M) {
        for(i = 0;i < MAXN;i++) G[i] = vector<int>();
        for(i = 0;i < M;i++) {
            cin >> a >> b;
            ca = codec(a) ,cb = codec(b);
            for(j = 0;j < N / 6;j++) {
                G[i].push_back(MAXM + ca + 6 * j);
                G[MAXM + ca + 6 * j].push_back(i);
                G[i].push_back(MAXM + cb + 6 * j);
                G[MAXM + cb + 6 * j].push_back(i);
            }
        }
        memset(match ,-1 ,sizeof(match));
        ans = 0;
        for(i = 0;i < M;i++) {
            visit.reset();
            if(match[i] == -1 && hungarian(i))
                ans += 1;
        }
        cout << (ans == M ? "YES" : "NO") << endl;
    }
}
/*
6 4
S XL
L S
L XL
L XL
*/
