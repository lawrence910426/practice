#include <iostream>
#include <cstring>
#include <memory.h>
using namespace std;
const int MAXN = 4e2 + 5 ,INF = (1LL << 31) - 1;
int T;
string src ,dst;
int dp[MAXN][MAXN] ,get[MAXN][26];
int main() {
    int s ,a ,b; int i ,j; bool flag ,eax ,ebx; char c;
    for(cin >> T;T--;) {
        cin >> src >> dst;
        for(i = 0;i < MAXN;i++) for(j = 0;j < 26;j++) get[i][j] = INF;
        for(i = 0;i < src.size();i++) for(c = 'a';c <= 'z';c++) for(j = i + 1;j < src.size();j++)
            if(c == src[j]) { get[i][c - 'a'] = j; break; }
        flag = false;
        for(s = 1;s < )
        cout << (flag ? "YES" : "NO") << endl;
    }
}
/*
4
xyz
x
*/
