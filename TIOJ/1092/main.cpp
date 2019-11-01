#include <iostream>
#include <vector>
#include <memory.h>
#include <cstring>
#include <bitset>
using namespace std;
const int MAXN = 1e4 + 10;
int N ,E ,a ,b;
vector<int> G_1[MAXN] ,G_2[MAXN];
bitset<MAXN> visit;
int status[MAXN];
void preprocess(int on ,bool style) {
    if(on == a) return;
    if(style) status[on] |= (1 << 0);
    else status[on] |= (1 << 1);
    for(int V : G_1[on]) preprocess(V ,!style);
}

bool dfs(int on ,bool style) {
    if(on == b) return true;
    if(style) {
        for(int V : G_2[on]) if(status[V] == 2) return dfs(V ,!style);
        for(int V : G_2[on]) if(status[V] == 3) return dfs(V ,!style);
        return false;
    } else {
        for(int V : G_2[on]) if(status[V] == 1) return dfs(V ,!style);
        for(int V : G_2[on]) if(status[V] == 3) return dfs(V ,!style);
        return false;
    }
}

int main() {
    int i ,eax ,ebx;
    string first;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> E ,!(N == 0 && E == 0)) {
        memset(status ,0 ,sizeof(status));
        for(i = 0;i < MAXN;i++) G_1[i] = vector<int>() ,G_2[i] = vector<int>();
        a = 1 ,b = N;
        for(i = 0;i < E;i++) {
            cin >> eax >> ebx;
            G_1[ebx].push_back(eax);
            G_2[eax].push_back(ebx);
        }
        cin >> first;
        preprocess(b ,true);
        cout << ((first == "Moumou") ^ dfs(a ,true) ? "Moumou" : "Mimi") << '\n';
    }
}
