#include <iostream>
#include <queue>
#include <assert.h>
using namespace std;

const int MAXN = 1e6 + 50;
struct line {
    long long alpha ,beta;
    long long value(long long x) { return alpha * x + beta; }
};
long long dp[MAXN] ,pre[MAXN] ,raw[MAXN] ,A ,B ,C;
long long F(long long i ,long long j) { return A * pre[j] * pre[j] + B * pre[j] - 2 * A * pre[i] * pre[j] + dp[j]; }
long long G(long long i) { return A * pre[i] * pre[i] - B * pre[i] + C; }
bool Valid(int i ,int j ,int k) {
    long long ai = (-2) * A * pre[i] ,bi = A * pre[i] * pre[i] + B * pre[i] + dp[i];
    long long aj = (-2) * A * pre[j] ,bj = A * pre[j] * pre[j] + B * pre[j] + dp[j];
    long long ak = (-2) * A * pre[k] ,bk = A * pre[k] * pre[k] + B * pre[k] + dp[k];
    assert((bi - bj) * (ak - aj) != (bj - bk) * (aj - ai));
    return (bi - bj) * (ak - aj) < (bj - bk) * (aj - ai);
}
int main() {
    int N ,i;
    while(cin >> N >> A >> B >> C) {
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = 0;i < N;i++) pre[i] = (i == 0 ? 0 : pre[i - 1]) + raw[i];
        deque<int> deq; deq.push_back(0); dp[0] = F(0 ,0) + G(0);
        for(i = 1;i < N;i++) {
            while(deq.size() > 2 && F(i ,deq[0]) < F(i ,deq[1])) deq.pop_front();
            dp[i] = F(i ,deq.front()) + G(i);
            while(deq.size() > 2 && !Valid(deq[deq.size() - 2] ,deq[deq.size() - 1] ,i)) deq.pop_back();
            deq.push_back(i);
        }
        cout << dp[N - 1] << endl;
    }
}
