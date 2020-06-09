#include <iostream>
#include <memory.h>
#include <stack>

using namespace std;
const int MAXN = 5e3 + 50;
int T ,N ,D ,sum ,first ,last ,cnt;
int depth[MAXN];
stack<int> code[MAXN];
int i ,j;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    for(cin >> T;T--;) {
        cin >> N >> D; memset(depth ,0 ,sizeof(depth)); cnt = 0;
        for(i = 0;i < N;i++) { depth[i] = 1; code[i] = stack<int>(); }
        first = 0; last = N - 1; sum = N * (N - 1) / 2;
        while(sum > D) {
            while(last > 0 && depth[last] == 0) last -= 1;
            while(first < N - 1 && depth[first] == (1 << first)) first += 1;
            if(last <= first) break;
            if(sum - last + first >= D) {
                depth[first] += 1; depth[last] -= 1;
            } else {
                first = D - sum + last;
                if(depth[first] == (1 << first)) break;
                depth[first] += 1; depth[last] -= 1;
            }
            sum = sum - last + first;
        }
        if(sum == D) {
            cout << "YES" << '\n';
            for(i = 0;i < N;i++) for(j = 0;j < depth[i];j++) { cnt += 1; code[i].push(cnt); code[i].push(cnt); }
            for(i = 1;i < N;i++) for(j = 0;j < depth[i];j++) { cout << code[i - 1].top() << " "; code[i - 1].pop(); }
            cout << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
}
