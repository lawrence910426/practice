#pragma GCC optimize("Ofast")
#include <iostream>
#include <set>
#define endl '\n'
using namespace std;
const int MAXN = 1e3 + 500;
int ans[MAXN][MAXN];
int main() {
    int N ,i ,j ,target ,pos ,lines ,counter ,prev ,a ,b;
    bool first;
    while(cin >> N) {
        first = true;
        if(N % 2 == 0) {
            for(i = 0;i < N - 1;i++) if(i % 2 == 0) {
                for(j = 1;j < N - i;j++) ans[j + i][j] = N - j - i / 2 + 1;
            } else {
                for(j = 1;j < N - i;j++) ans[j + i][j] = (j % 2 == 1 ? (i / 2) + 2 : N - (i / 2));
            }
            for(i = 1;i <= N - 1;i++) {
                cout << 1;
                for(j = 1;j <= i;j++) cout << " " << ans[i][j];
                cout << endl;
            }
        } else {
            target = (N - 1) / 2;
            pos = lines = counter = 0;
            for(i = 0;i < N;i++) for(j = 1;j <= target;j++) {
                prev = pos;
                pos += j;
                pos %= N;
                if(counter == lines) {
                    counter = -1;
                    lines += 1;
                    cout << (first ? "" : " ") << prev + 1 << " " << pos + 1 << endl;
                    first = true;
                } else cout << (first ? "" : " ") << prev + 1, first = false;
                counter += 1;
            }
        }
    }
}
