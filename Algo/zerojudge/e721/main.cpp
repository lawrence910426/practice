#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e4 + 5;
int data[MAXN] ,N ,gsize ,dp[MAXN][2];
pair<int ,int> group[MAXN];

int main() {
    int i ,ans;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i];
        sort(data ,data + N);
        group[0] = pair<int ,int>(data[0] ,1);
        for(gsize = i = 1;i < N;i++)
            if(group[gsize - 1].first == data[i]) group[gsize - 1].second += 1;
            else group[gsize++] = pair<int ,int>(data[i] ,1);
        for(ans = i = 0;i < gsize;i++) {
            if(i == 0) {
                dp[i][0] = 0;
                dp[i][1] = group[i].first * group[i].second;
            } else if(group[i].first == group[i - 1].first + 1) {
                dp[i][0] = max(dp[i - 1][0] ,dp[i - 1][1]);
                dp[i][1] = dp[i - 1][0] + group[i].first * group[i].second;
            } else {
                dp[i][0] = max(dp[i - 1][0] ,dp[i - 1][1]);
                dp[i][1] = max(dp[i - 1][0] ,dp[i - 1][1]) + group[i].first * group[i].second;
            }
        }
        cout << max(dp[gsize - 1][0] ,dp[gsize - 1][1]) << endl;
    }
}
/*
3
2 3 4
6
2 2 3 3 3 4
*/
/* Wrong testing data? WTF? */
