#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 4e2 + 50 ,INF = (1LL << 31) - 1;
int dp[MAXN][MAXN] ,get[MAXN][26];
int main() {
    int T; int a ,b ,s ,i ,j; char temp;
    string src ,dst; bool flag;
    for(cin >> T;T--;) {
        cin >> src >> dst;
        for(i = 0;i < MAXN;i++) for(temp = 'a';temp <= 'z';temp++) get[i][temp - 'a'] = INF;
        for(i = 0;i < src.size();i++) for(temp = 'a';temp <= 'z';temp++) for(j = i;j < src.size();j++)
            if(temp == src[j]) { get[i][temp - 'a'] = j + 1; break; }
        flag = false;
        for(s = 1;s <= dst.size();s++) {
            dp[0][s] = 0;
            for(a = 0;a <= s;a++) for(b = s;b <= dst.size();b++) {
                if(a == 0 && b == s) continue;
                dp[a][b] = INF;
                if(a != 0 && dp[a - 1][b] < INF) dp[a][b] = min(dp[a][b] ,get[dp[a - 1][b]][dst[a - 1] - 'a']);
                if(b != s && dp[a][b - 1] < INF) dp[a][b] = min(dp[a][b] ,get[dp[a][b - 1]][dst[b - 1] - 'a']);
            }
            flag |= (dp[s][dst.size()] < INF);
        }
        cout << (flag ? "Yes" : "No") << endl;
    }
}
/*
4
zyx
x
*/
