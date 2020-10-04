#include <iostream>
#include <memory.h>
#include <cstring>
#include <algorithm>

using namespace std;
string s;
int N;
long long dp[3][3], old[3][3], strings = 1;
const long long mod = 1e9 + 7;

int main() {
    cin >> N >> s;
    int i, j, k, temp;
    char start, end;
    
    memset(old, 0, sizeof(old));
    for(i = 0;i < N;i++) {
        if(s[i] == '?') { start = 'a'; end = 'c'; }
        else { start = end = s[i]; }
        memset(dp, 0, sizeof(dp));

        for(j = start - 'a';j <= end - 'a';j++) {
            dp[j][0] = old[0][0] + old[1][0] + old[2][0] + (j == 0 ? strings : 0);
            dp[j][1] = old[0][1] + old[1][1] + old[2][1] + (j == 1 ? old[0][0] + old[1][0] + old[2][0] : 0);
            dp[j][2] = old[0][2] + old[1][2] + old[2][2] + (j == 2 ? old[0][1] + old[1][1] + old[2][1] : 0);
        }
        
        for(int x = 0;x < 3;x++) for(int y = 0;y < 3;y++) dp[x][y] %= mod;

        swap(dp, old);
        if(s[i] == '?') strings = (strings * 3) % mod;
   }

    int ans = 0;
    for(i = 0;i < 3;i++)  ans += old[i][2];
    cout << ans % mod << endl;
}
