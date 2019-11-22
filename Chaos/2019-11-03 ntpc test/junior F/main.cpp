#include <iostream>

using namespace std;
const int MAXN = 1e6 + 5 ,GREEN = 0 ,RED = 1 ,BLUE = 2; /* 0-green ,1-red ,2-blue */
int dp[MAXN][3]; /* dp[i][COLOR] = The maximum value of a subsequence from [0,i] with COLOR as ending*/
inline int max(int a ,int b ,int c) { return max(a ,max(b ,c)); } /* Max with three parameters(?) */

int main() {
    int N;
    int i ,value;
    while(cin >> N) {
        /* The complexity would be O(N) */
        for(i = 0;i < N;i++) {
            cin >> value;
            if(i == 0) {
                dp[0][GREEN] = value;
                dp[0][RED] = -value;
                dp[0][BLUE] = 0;
            } else {
                dp[i][GREEN] = max(dp[i - 1][RED] ,dp[i - 1][BLUE]) + value;
                dp[i][RED] = max(dp[i - 1][GREEN] ,dp[i - 1][BLUE]) - value;
                dp[i][BLUE] = max(dp[i - 1][RED] ,dp[i - 1][GREEN]);
            }
        }
        cout << max(dp[N - 1][GREEN] ,dp[N - 1][RED] ,dp[N - 1][BLUE]) << endl;
    }
}
