#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;

const int MAXN = 1e6 + 50 ,INF = (1LL << 31) - 1;
long long dp[MAXN] ,pre[MAXN] ,raw[MAXN] ,A ,B ,C;
long long F(long long i ,long long j) { return (-2) * A * pre[j] * pre[i] + A * pre[j] * pre[j] - B * pre[j] + dp[j]; }
long long G(long long i) { return A * pre[i] * pre[i] + B * pre[i] + C; }
bool Valid(int i ,int j ,int k) {
    long long ai = (-2) * A * pre[i] ,bi = A * pre[i] * pre[i] + B * pre[i] + dp[i];
    long long aj = (-2) * A * pre[j] ,bj = A * pre[j] * pre[j] + B * pre[j] + dp[j];
    long long ak = (-2) * A * pre[k] ,bk = A * pre[k] * pre[k] + B * pre[k] + dp[k];
    //assert((bi - bj) * (ak - aj) != (bj - bk) * (aj - ai));
    return (bi - bj) * (ak - aj) <= (bj - bk) * (aj - ai);
}
int main() {
    int N ,i;
    deque<int> deq;
    while(cin >> N >> A >> B >> C) {
        for(i = 0;i < N;i++) cin >> raw[i];
        for(pre[0] = i = 0;i < N;i++) pre[i + 1] = pre[i] + raw[i];
        deq = deque<int>(); deq.push_back(0); dp[0] = 0;
        for(i = 1;i <= N;i++) {
            while(deq.size() >= 2 && F(i ,deq[0]) < F(i ,deq[1])) deq.pop_front();
            dp[i] = F(i ,deq[0]) + G(i);
            while(deq.size() >= 2 && !Valid(deq[deq.size() - 2] ,deq[deq.size() - 1] ,i)) deq.pop_back();
            deq.push_back(i);
        }
        cout << dp[N] << endl;
    }
}
