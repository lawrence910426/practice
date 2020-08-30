#pragma GCC optimize("Ofast")

#include <iostream>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
const int MAXN = 1e5 + 50;
tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> Tree[MAXN];
tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update>* pointer[MAXN];

class DisjointSet {
    int data[MAXN];
public:
    DisjointSet(int N) { for(int i = 1;i <= N;i++) data[i] = i; }
    int query(int i) { return (i == data[i] ? i : data[i] = query(data[i])); }
    void join(int a, int b) { data[query(a)] = query(b); }
};
int raw[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, M;
    char Q;
    int x, y, i, temp;
    bool flag;
    cin >> N >> M;
    DisjointSet DSU = DisjointSet(N);
    for(i = 1;i <= N;i++) pointer[i] = &Tree[i];
    for(i = 1;i <= N;i++) { cin >> raw[i]; pointer[i]->insert(raw[i]); }
    while(M--) {
        cin >> Q >> x >> y;
        if(Q == 'A') {
            x = DSU.query(x); y = DSU.query(y);
            if(x == y) continue;
            if(pointer[x]->size() > pointer[y]->size()) swap(pointer[x], pointer[y]);
            while(!pointer[x]->empty()) {
                temp = *pointer[x]->begin();
                pointer[y]->insert(temp);
                pointer[x]->erase(temp);
            }
            DSU.join(x, y);
        } else if(Q == 'M') {
            temp = DSU.query(x);
            pointer[temp]->erase(raw[x]);
            raw[x] = y;
            pointer[temp]->insert(raw[x]);
        } else if(Q == 'Q') {
            cout << *pointer[DSU.query(x)]->find_by_order(y - 1) << '\n';
        }
    }
}
