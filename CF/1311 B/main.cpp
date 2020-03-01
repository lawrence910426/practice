#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e2 + 50;
int T ,M ,N;
int raw[MAXN] ,conn[MAXN];
int main() {
    int i ,src ,dst;
    for(cin >> T;T--;) {
        cin >> N >> M;
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < M;i++) { cin >> conn[i]; conn[i] -= 1; }
        sort(conn ,conn + M);
        src = conn[0];
        for(i = 1;i < M;i++) {
            if(conn[i] != conn[i - 1] + 1) {
                dst = conn[i - 1] + 1;
                sort(raw + src ,raw + dst + 1);
                src = conn[i];
            }
        }
        dst = conn[i - 1] + 1;
        sort(raw + src ,raw + dst + 1);
        for(i = 0;i < N;i++) if(raw[i - 1] > raw[i]) break;
        cout << (i == N ? "YES" : "NO") << endl;
    }
}
