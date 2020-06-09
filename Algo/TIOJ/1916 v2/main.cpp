#include <iostream>
#include <map>
using namespace std;
const int MAXN = 2005;
map<int ,int> sum[MAXN][MAXN];
int data[MAXN][MAXN];
int N ,Q ,l ,r ,u ,d;
int main() {
    int i ,j;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> data[i][j];
        for(i = 0;i <= N;i++) sum[i][0] = sum[0][i] = map<int ,int>();
        for(i = 1;i <= N;i++) for(j = 1;j <= N;j++) {
            for(auto it : sum[i][j - 1]) sum[i][j][it.first] = it.second;
            sum[i][j][data[i - 1][j - 1]] = sum[i][j][data[i - 1][j - 1]] + 1;
        }
        for(cin >> Q;Q--;) {
            cin >> l >> r >> u >> d;
            r += 1 ,d += 1;
            map<int ,int> mapa;
            for(auto it : sum[r][d]) mapa[it.first] = mapa[it.first] + it.second;
            for(auto it : mapa) cout << it.first << " " << it.second << endl;
            cout << endl;
            for(auto it : sum[l][u]) mapa[it.first] = mapa[it.first] + it.second;
            for(auto it : mapa) cout << it.first << " " << it.second << endl;
            cout << endl;
            for(auto it : sum[r][u]) mapa[it.first] = mapa[it.first] - it.second;
            for(auto it : mapa) cout << it.first << " " << it.second << endl;
            cout << endl;
            for(auto it : sum[l][d]) mapa[it.first] = mapa[it.first] - it.second;
            for(auto it : mapa) cout << it.first << " " << it.second << endl;
            cout << endl;
            int ans = -1;
            for(auto it : mapa) if(it.second * 2 > (r - l) * (d - u)) ans = it.first;
            cout << ans << endl;
        }
    }
}
