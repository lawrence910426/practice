#include <tuple>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 3e5 + 50;
long long A[MAXN], dp[MAXN];

class MonotoneQueue {
    typedef tuple<long long, long long, long long> T;
public:
    long long best;
    stack<T> storage;
    MonotoneQueue() { best = -1; storage = stack<T>(); }
    
    void Update(long long mini) {
        long long maximum = -1;
        while(!storage.empty() && get<0>(storage.top()) >= mini) {
            maximum = max(maximum, get<1>(storage.top()));
            storage.pop();
        }
        best = max(best, maximum - mini);
        storage.push({mini, maximum, maximum - mini});
    }

    void Push(T item) {
        best = max(best, get<2>(item));
        storage.push(item);
    }
} MQ;


int main() {
    int T, N, Q;
    long long ans;
    int i;
    for(cin >> T;T--;) {
        cin >> N >> Q;
        for(i = 0;i < N;i++) cin >> A[i];
        MQ = MonotoneQueue();

        dp[0] = A[0]; dp[1] = A[1];    
        MQ.Push({A[1], dp[0], dp[0] - A[1]});
        for(i = 2;i < N;i++) {
            dp[i] = A[i] + max(0LL, MQ.best);
            MQ.Update(A[i]);
            MQ.Push({A[i], dp[i - 1], dp[i - 1] - A[i]});
        }
        for(ans = i = 0;i < N;i++) ans = max(ans, dp[i]);
        cout << ans << endl;
    }
}
