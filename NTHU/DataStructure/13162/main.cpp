#include <iostream>
#include <sstream>
#include <memory.h>
#include <assert.h>

using namespace std;

const int MAXL = 15, MAXN = 1005;

int Matrix[MAXL][MAXN], Col[MAXL];

int get() {
    int ans = 0, base = 1;
    while(cin.peek() != ' ') {
        ans += base * (cin.get() - '0');
        base *= 10;
    }
    return ans;
}

int main() {
    int T, L, Q, row, maxcol;
    long long ans, base;

    for(cin >> T;T--;) {
        cin >> L >> Q;
        cin.get();

        memset(Matrix, 0, sizeof(Matrix));
        maxcol = 0;
        for(int i = 0;i < L;i++) Col[i] = 0;
        
        while(Q--) {
            row = get();
            cout << row << " " << cin.peek() << endl;
            while(cin.peek() != '\n') {
                cout << cin.get() << " " << cin.peek() << endl;
                Matrix[row][Col[row]] = cin.get() - '0';
                Col[row] += 1;
                maxcol = max(maxcol, Col[row]);
            }
        }
        
        ans = 0;
        for(int i = 0;i < maxcol;i++) {
            base = 1;
            for(int j = L - 1;j >= 0;j--) {
                ans += base * (long long)Matrix[j][i];
                base *= 10;
            }
        }  
        cout << ans << '\n';
    }    
}
