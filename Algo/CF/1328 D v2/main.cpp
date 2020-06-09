#include <iostream>
#include <deque>
#include <memory.h>

using namespace std;
const int MAXN = 2e5 + 50;
int ans[MAXN] ,raw[MAXN];
int main() {
    int Q ,N ,colors;
    int i ,j;
    for(cin >> Q;Q--;) {
        cin >> N;
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = j = 0;i < N;i++) {
            if(i == j) {
                for(j = i;j < N;j++) if(raw[i] != raw[j]) break;
                if(i == 0) ans[i] = 1;
                else {
                    if(ans[i - 1] == 1 && j == N) ans[i] = 2;
                    if(ans[i - 1] == 1 && j != N) ans[i] = 2;
                    if(ans[i - 1] == 2 && j == N) ans[i] = (raw[0] == raw[N - 1] ? 1 : 3);
                    if(ans[i - 1] == 2 && j != N) ans[i] = 1;
                }
            } else ans[i] = ans[i - 1];
        }
        cout << ans[N - 1] << endl;
        for(i = 0;i < N;i++) cout << ans[i] << " ";
        cout << endl;
    }
}
/*
3
3
2 1 2
*/
