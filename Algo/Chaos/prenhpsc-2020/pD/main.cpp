#include <iostream>
#include <queue>

const int MAXN = 1e6 + 50;
int raw[MAXN];
deque<pair<int, int> > maxi, mini;

int main() {
    long long ans = 0;
    int N, K;
    cin >> N >> K;
    int i, j;
    for(i = 0;i < N;i++) cin >> raw[i];
    for(i = j = 0;i < N;i++) {
        if(i == 0) {
            maxi.push_back({raw[0], 0});
            mini.push_back({raw[0], 0});
            j += 1;
        }
        while(j < N && maxi.front().first - mini.front().first <= K) {
            while(!maxi.empty() && maxi.back().first <= raw[j]) maxi.pop_back();
            maxi.push_back({raw[j], j});
            while(!mini.empty() && mini.back().first >= raw[j]) mini.pop_back();
            mini.push_back({raw[j], j});
            j += 1;
        }
        if(maxi.front().first - mini.front().first > K) ans += (long long)j - 1LL - (long long)i;

    }
}
