#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

using namespace std;
const int MAXN = 300;
vector<int> G;
int N ,K;
struct V {
    vector<int> kids;
    int weight ,best[2] ,height ,parent;
}nodes[MAXN];

void preprocess(int parent ,int on) {
    nodes[on].parent = parent;
    nodes[on].leaf = true;
    for(int next : G[on]) if(!nodes[next].visit && next != parent) {
        kids.push(next);
        preprocess(on ,next);
    }
    if(parent != -1) nodes[on].height = nodes[parent].height + 1;
}

void run(int on) {
    if(nodes[on].visit) return;
    nodes[on].visit = true;
    if(nodes[on].leaf) {
        nodes[on].best[0] = 0;
        nodes[on].best[1] = nodes[on].weight;
    } else {
        for(queue<int> Q = queue<int>(on);!Q.empty();Q.pop()) {

            for(int K : nodes[Q.top()].kids) Q.push(K);
        }
    }
}

int main() {
    int i ,eax ,ebx;
    while(cin >> N >> K) {
        memset(nodes ,0 ,sizeof(nodes));
        visit.clear();
        for(i = 0;i < N;i++) cin >> nodes[i].weight;
        for(i = 1;i <= N;i++) G[i] = vector<int>();
        for(i = 0;i < N - 1;i++)  {
            cin >> eax >> ebx;
            G[eax].push_back(ebx);
            G[ebx].push_back(eax);
        }
        nodes[1].height = 0;
        preprocess(-1 ,1);
    }
}
// I quit.
