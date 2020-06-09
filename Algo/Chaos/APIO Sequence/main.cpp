#include <iostream>
#include <deque>
using namespace std;
const int MAXN = 1e5 + 50;
int N ,K;
long long raw[MAXN] ,pre[MAXN] ,dp[MAXN] ,last[MAXN];
long long F(long long i ,long long j) { return pre[j] * pre[i] + last[j] - pre[j] * pre[j]; }
bool Valid(int i ,int j ,int k) {
    long long ai = pre[i] ,bi = last[i] - pre[i] * pre[i];
    long long aj = pre[j] ,bj = last[j] - pre[j] * pre[j];
    long long ak = pre[k] ,bk = last[k] - pre[k] * pre[k];
    return (bj - bi) * (aj - ak) < (bk - bj) * (ai - aj);
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int i;
    while(cin >> N >> K) {
        for(i = 0;i < N;i++) cin >> raw[i];
        for(pre[0] = i = 0;i < N;i++) pre[i + 1] = pre[i] + raw[i];
        for(i = 1;i <= N;i++) last[i] = 0;
        while(K--) {
            deque<int> deq; deq.push_back(0);
            for(i = 1;i <= N;i++) {
                while(deq.size() >= 2 && F(i ,deq[0]) < F(i ,deq[1])) deq.pop_front();
                dp[i] = F(i ,deq[0]);
                while(deq.size() >= 2 && !Valid(deq[deq.size() - 2] ,deq[deq.size() - 1] ,i)) deq.pop_back();
                deq.push_back(i);
            }
            for(i = 1;i <= N;i++) last[i] = dp[i];
        }
        cout << dp[N] << '\n';
    }
}
