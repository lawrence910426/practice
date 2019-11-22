#include <iostream>
#include <cstring>
#include <bitset>
using namespace std;
const int MAXN = 1e3 + 5;
struct item {
    int cost ,len;
    vector<pair<bitset<MAXN> ,int> > status;
    item(): cost(0) {}
    item operator+ (item& i) {

    }
}dp[MAXN][2];
bitset<MAXN> N ,M;
int nlen ,mlen;

int main() {
    string a ,b;
    int i ,j;
    for(i = 0;i < MAXN;i++) dp[i][0] = dp[i][1] = item();
    getline(cin ,a) ,getline(cin ,b);
    nlen = a.size() ,mlen = b.size();
    for(i = 0;i < nlen;i++) N[i] = a[i] == 'B';
    for(i = 0;i < mlen;i++) M[i] = b[i] == 'B';
    for(i = 0;i < mlen;i++) {
        for(j = 0;j < dp[i][0].status.size();j++) dp[i][0].status[j].reset();
        for(j = 0;j < dp[i][1].status.size();j++) dp[i][1].status[j].reset();
        if(i == 0) {
            dp[0][0].cost = 1 ,dp[0][0].len = 0;
            dp[0][1].cost = 0 ,dp[0][1].len = 1 ,dp[0][1].status[0] = M[0];
        } else {
            if(dp[i - 1][0].cost > dp[i - 1][1].cost) dp[i][0] = dp[i - 1][1];
            else if(dp[i - 1][0].cost < dp[i - 1][1].cost) dp[i][0] = dp[i - 1][0];
            else
        }
    }
}
// quit.
