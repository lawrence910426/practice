#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory.h>

using namespace std;
const int MAXN = 2005;
int raw[MAXN][MAXN] ,data[MAXN][MAXN];
struct s {
    int counter[MAXN];
} dp[MAXN][MAXN];
vector<int> discrete;
int main() {
    int N ,Q ,l ,r ,u ,d;
    int i ,j;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> raw[i][j];
        /*discrete = vector<int>();
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) discrete.push_back(raw[i][j]);
        sort(discrete.begin() ,discrete.end());
        auto last = unique(discrete.begin() ,discrete.end());
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) data[i][j] = lower_bound(discrete.begin() ,last ,raw[i][j]) - discrete.begin();*/
        for(i = 0;i < MAXN;i++) for(j = 0;j < MAXN;j++) dp[i][j].counter = map<int ,int>();
        map<int ,int> mapa;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
            mapa[raw[i][j]] = mapa[raw[i][j]] + 1;
            dp[i + 1][j + 1].counter = mapa;
        }
        for(cin >> Q;Q--;) {
            cin >> l >> r >> u >> d;
            r += 1, d += 1;
            mapa = map<int ,int>();
            int out = -1;
            for(auto it : mapa)
                if(it.second * 2 > (r - l) * (d - u))
                    out = it.first;
            cout << out << endl;
        }
    }
}
