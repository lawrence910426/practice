#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <memory.h>

#define MAXN 2000005
using namespace std;
int boss[MAXN] ,mini[MAXN];
long long int sum[MAXN];
bool cycle[MAXN];
vector<pair<int ,int> > raw;
vector<int> numbers;

int getboss(int i) {
    if(i == boss[i]) return i;
    else return boss[i] = getboss(boss[i]);
}

inline void join(int a ,int b) {
    a = getboss(a) ,b = getboss(b);
    if(a == b) {
        cycle[a] = true;
        return;
    }
    cycle[a] |= cycle[b];
    mini[a] = min(mini[a] ,mini[b]);
    sum[a] += sum[b];
    boss[b] = boss[a];
}

inline int codec(int value) {
    int code = lower_bound(numbers.begin() ,numbers.end() ,value) - numbers.begin();
    if(boss[code] == -1) {
        boss[code] = code;
        sum[code] = mini[code] = value;
        cycle[code] = false;
    }
    return code;
}


int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    memset(boss ,-1 ,sizeof(boss));
    long long int i ,a ,b;
    long long int ans = 0 ,N;
    cin >> N;
    for(i = 0;i < N;i++) {
        cin >> a >> b;
        numbers.push_back(a);
        numbers.push_back(b);
        raw.push_back(make_pair(a ,b));
    }
    sort(numbers.begin() ,numbers.end());
    numbers.erase(unique(numbers.begin() ,numbers.end()) ,numbers.end());
    for(auto p : raw) join(codec(p.first) ,codec(p.second));
    for(i = 0;i < numbers.size();i++) if(boss[i] == i) ans += sum[i] - (cycle[i] ? 0 : mini[i]);
    cout << ans << endl;
}
