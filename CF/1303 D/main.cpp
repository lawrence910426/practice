#include <iostream>
#include <queue>
using namespace std;

long long T ,N ,M ,temp ,sum;
priority_queue<long long> pq;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int i ,ans;
    for(cin >> T;T--;) {
        cin >> N >> M;
        sum = ans = 0; pq = priority_queue<long long>();
        for(i = 0;i < M;i++) { cin >> temp; pq.push(temp); sum += temp; }
        while(!pq.empty() && N != 0) {
            temp = pq.top(); pq.pop(); sum -= temp;
            if(N >= temp) N -= temp;
            else if(sum < N) { pq.push(temp >> 1); pq.push(temp >> 1); ans += 1; sum += temp; }
        }
        cout << (N == 0 ? ans : -1) << '\n';
    }
}
