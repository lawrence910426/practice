#include <iostream>
#include <set>
using namespace std;
const int MAXN = 1e6 + 50;
struct { int par ,l ,r ,time; } tree[MAXN];
set<int> S;
set<int>::iterator it;
int N ,val ,father;

void Left() { father = *it; tree[father].l = val; }
void Right() { father = *prev(it); tree[father].r = val; }

int main() {
    cin >> N;
    int i;
    for(i = 0;i < N;i++) {
        cin >> val;
        if(S.empty()) father = 0;
        else {
            it = S.lower_bound(val);
            if(it == S.end()) Right();
            else if(it == S.begin()) Left();
            else {
                if(tree[*prev(it)].time < tree[*it].time) Left();
                else Right();
            }
        }
        tree[val] = {father ,-1 ,-1 ,i};
        S.insert(val);
    }
    for(i = 1;i <= N;i++) cout << tree[i].par << '\n';
}
