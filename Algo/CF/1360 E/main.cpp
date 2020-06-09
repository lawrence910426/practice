#include <iostream>
#include <bitset>

using namespace std;
const int MAXN = 3000;
bitset<MAXN> raw, visit; int N;

void dfs(int x, int y) {
    if(x < 0 || y < 0 || x >= N || y >= N) return;
    if(visit[x * 50 + y] || raw[x * 50 + y] == false) return;
    visit[x * 50 + y] = true;
    dfs(x + 1, y); dfs(x - 1, y); dfs(x, y + 1); dfs(x, y - 1);
}

int main() {
    int T; int i, j; char eax; bool used, err;
    for(cin >> T;T--;) {
        raw.reset(); visit.reset();
        cin >> N; used = err = false;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) { cin >> eax; raw[i * 50 + j] = (eax == '1'); }
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
            if(!visit[i * 50 + j] && raw[i * 50 + j]) {
                if(used) { err = true; break; }
                else { dfs(i, j); used = true; }
            }
        }
        cout << (err ? "NO" : "YES") << endl;
    }
}
