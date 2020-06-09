#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 2e5 + 10;
int black[MAXN] ,white_count ,black_count ,N ,wound[MAXN];

int main() {
    int i ,color ,val;
    while(cin >> N) {
        black_count = white_count = 0;
        for(i = 0;i < N;i++) {
            cin >> color >> val;
            if(color == 0) white_count += 1;
            else black[black_count++] = val;
        }
        sort(black ,black + black_count);
        /* Obviously it is the solution that minimize the harmness of cows */
        for(i = 0;i < black_count - 1;i++) wound[i] = black[i + 1] - black[i];
        sort(wound ,wound + black_count - 1);
        /* Insert white cows between the black cows */
        if(white_count >= black_count - 1) cout << 0 << endl;
        else cout << wound[black_count - white_count - 2] << endl;
    }
}
