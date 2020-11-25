#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

const int MAXN = 2e5 + 5;
typedef std::pair<long long, long long> pll;
typedef __gnu_pbds::priority_queue<pll, std::greater<pll>, __gnu_pbds::rc_binomial_heap_tag> pq;

vector<int> G[MAXN];
vector<long long> raw(MAXN, 0);

pq dfs(int on) {
    pq ans; 
    pll temp;
    long long remainder;
    if(G[on].size() == 0) {
        ans.push({raw[on], 1});
    } else {
        for(int V : G[on]) {
            pq kid = dfs(V);
            ans.join(kid);
        }
        temp = ans.top();
        for(ans.pop(); !ans.empty() && ans.top().first == temp.first; ans.pop()) temp.second += ans.top().second; 
        while(!ans.empty() && (ans.top().first - temp.first) * temp.second <= raw[on]) {
            raw[on] -= (ans.top().first - temp.first) * temp.second;
            temp.first = ans.top().first; temp.second += ans.top().second;
            ans.pop(); 
        }
        remainder = raw[on] % temp.second;
        temp.first += raw[on] / temp.second;
        ans.push({temp.first, temp.second - remainder});
        if(remainder > 0) ans.push({temp.first + 1, remainder});
    }
    raw[on] = 0;
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N;
    int i, p;
    pll temp;

    cin >> N;
    for(i = 2;i <= N;i++) {
        cin >> p;
        G[p].push_back(i);
    }
    for(i = 1;i <= N;i++) cin >> raw[i];
    
    for(pq ans = dfs(1);!ans.empty();ans.pop()) temp = ans.top();
    cout << temp.first << endl;
}
