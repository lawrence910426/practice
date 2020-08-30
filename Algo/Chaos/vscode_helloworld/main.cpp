#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAXN = 1e6 + 50;

int N, K;
long long duration[MAXN], temp, ans;

int main() {
    priority_queue<long long, vector<long long>, greater<long long> > heap;
    cin >> N >> K;
    int ptr;
    for(ptr = 0;ptr < N;ptr++) cin >> duration[ptr];

    /* All toilets are empty. Therefore we let the disciples use the bathroom until the bathroom is full. */
    for(ptr = 0;ptr < N && heap.size() < K;ptr++) heap.push(duration[ptr]);
    /* All toilets are occupied. Once someone finished its job the next one take over the bathroom. */
    for(;ptr < N;ptr++) {
        temp = heap.top();
        heap.pop();
        heap.push(temp + duration[ptr]);
    }    
    /* The last one who leaves the toilet would be the answer. */
    for(ans = -1;!heap.empty();heap.pop()) ans = heap.top();
    cout << ans << endl;
}