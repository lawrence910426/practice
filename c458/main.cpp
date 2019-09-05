#include <iostream>
#include <string>
#include <memory.h>

using namespace std;
int L ,K ,dp[10005][10005];
string a ,b;

int main() {
    int i ,j;
    while(cin >> a >> b) {
        cin >> L >> K;
        memset(dp ,0 ,sizeof(dp));
        for(i = 1;i <= a.size();i++) for(j = 1;j <= b.size();j++) {
            dp[i][j] = max(dp[i - 1][j] ,dp[i][j - 1]);
            if(a[i] == b[j]) dp[i][j] = max(dp[i][j] ,dp[i - 1][j - 1] + 1);
        }
    }
}
