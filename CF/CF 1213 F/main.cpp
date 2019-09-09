#include <iostream>
#include <set>
#include <algorithm>
#include <assert.h>

using namespace std;
#define MAXN 200005
set<int> edge[MAXN];
int dsu[MAXN];
char codec[MAXN];
int boss(int i) {
    if(dsu[i] == i) return i;
    return dsu[i] = boss(dsu[i]);
}
void combine(int a ,int b) {
    //a become slave and b become master
    int ba = boss(a) ,bb = boss(b);
    edge[bb].insert(edge[ba].begin() ,edge[ba].end());
    dsu[b] = dsu[a] = dsu[ba] = bb;
}

int N;
void inputs() {
    int last ,on;
    cin >> last;
    for(int i = 1;i < N;i++) {
        cin >> on;
        edge[last].insert(on);
        last = on;
    }
}

set<int> bosses;
void run_codec() {

}

int main() {
    int K ,boss_i ,boss_j;
    int i ,j;
    bool flag;
    while(cin >> N >> K) {
        for(i = 0;i < MAXN;i++) {
            edge[i].clear();
            dsu[i] = i;
        }
        inputs() ,inputs();

        flag = true;
        while(flag) {
            flag = false;
            for(i = 1;i <= N && !flag;i++) for(j = i + 1;j <= N && !flag;j++) {
                boss_i = boss(i) ,boss_j = boss(j);
                if(boss_i == boss_j) continue;
                if(edge[boss_i].find(boss_j) != edge[boss_i].end() &&
                   edge[boss_j].find(boss_i) != edge[boss_j].end()) {
                    combine(boss_i ,boss_j);
                    flag = true;
                }
            }
        }

        bosses.clear();
        for(i = 1;i <= N;i++) if(boss(i) == i) bosses.insert(i) ,cout << i << endl;

        if(bosses.size() > K) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            run_codec();
            for(i = 1;i <= N;i++) cout << codec[boss(i)];
            cout << endl;
        }
    }
}
