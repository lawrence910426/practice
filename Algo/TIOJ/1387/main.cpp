#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
struct stone { int W ,M ,C; } item[1000005];
int N ,T;
long long int dp[2000005];

inline bool gin(int &a){
    char c;
    while(c=getchar(),c<'0'||c>'9')if(c==-1)return 0;
    a=c-'0';
    while(c=getchar(),c>='0'&&c<='9')a=a*10+c-'0';
    return 1;
}

int main() {
    int i ,j;
    long long ans;
    gin(N);
    for(i = 0;i < N;i++) gin(item[i].W) ,gin(item[i].M) ,gin(item[i].C);
    gin(T);
    memset(dp ,0 ,sizeof(dp));
    for(i = 0;i < N;i++) while(item[i].C--) {
        for(j = T - item[i].W;j >= 0;j--) if(dp[j] != 0) dp[j + item[i].W] = max(dp[j + item[i].W] ,dp[j] + item[i].M);
        dp[item[i].W] = max(dp[item[i].W] ,(long long)item[i].M);
    }
    for(ans = i = 0;i <= T;i++) ans = max(ans ,dp[i]);
    cout << ans << endl;
}
