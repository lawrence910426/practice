#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const long long MAXN = 2e5 + 50 ,MOD = 998244353;
long long pos[MAXN] ,raw[MAXN];
int main() {
    long long N ,K ,ans = 1 ,sum = 0; cin >> N >> K;
    long long i ,temp;
    for(i = 0;i < N;i++) { cin >> raw[i]; pos[raw[i]] = i; }
    vector<long long> maxi;
    for(i = 0;i < K;i++) maxi.push_back(pos[N - i]);
    sort(maxi.begin() ,maxi.end());
    for(i = 0;i < maxi.size() - 1;i++) ans = ans * (maxi[i + 1] - maxi[i]) % MOD;
    for(i = 0;i < maxi.size();i++) sum += raw[maxi[i]];
    cout << sum << " " << ans << endl;
}
