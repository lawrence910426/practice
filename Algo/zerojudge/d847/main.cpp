#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

using namespace std;
struct pt { int x ,y ,code ,ans; } data[10005];
vector<int> sorted[1005];
bool cmp_code(pt& a, pt& b) { return a.code < b.code; }

int zkw[4096 * 10] ,leaf;
inline int query(int L ,int R) {
    int ret = 0;
    for(L += leaf ,R += leaf + 1;L ^ R ^ 1;L >>= 1, R >>= 1) {
        if(L % 2 == 0) ret += zkw[L ^ 1];
        if(R % 2 == 1) ret += zkw[R ^ 1];
    }
    return ret;
}
inline void modify(int pos ,int x) { for(pos += leaf + 1;pos;pos >>= 1) zkw[pos] += x; }
inline void build() { leaf = 4096; memset(zkw ,0 ,sizeof(zkw)); }

int main() {
    int i ,j ,N;
    while(cin >> N) {
        for(i = 0;i < 1005;i++) sorted[i] = vector<int>();
        build();
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y ,data[i].code = i ,sorted[data[i].x].push_back(i);
        for(i = 0;i < 1005;i++) { for(j = 0;j < sorted[i].size();j++) data[sorted[i][j]].ans = query(0 ,data[sorted[i][j]].y); for(j = 0;j < sorted[i].size();j++) modify(data[sorted[i][j]].y ,1); }
        sort(data ,data + N ,cmp_code);
        for(i = 0;i < N;i++) cout << data[i].ans << endl;
    }
}
