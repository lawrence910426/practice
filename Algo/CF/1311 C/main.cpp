#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 2e5 + 50;
int T ,N ,M ,segs[MAXN] ,ans[30] ,stat[30];
int i ,lptr ,rptr;
string s;
int main() {
    for(cin >> T;T--;) {
        cin >> N >> M >> s;
        for(i = 0;i < 30;i++) ans[i] = stat[i] = 0;
        for(i = 0;i < M;i++) cin >> segs[i];
        segs[M] = N;
        sort(segs ,segs + M);
        for(lptr = rptr = 0;lptr <= M;lptr++) {
            while(segs[lptr] > rptr) stat[s[rptr++] - 'a'] += 1;
            for(i = 0;i < 30;i++) ans[i] += stat[i];
        }
        for(i = 0;i < 26;i++) cout << ans[i] << " ";
        cout << endl;
    }
}
