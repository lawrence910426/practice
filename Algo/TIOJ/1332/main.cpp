#pragma GCC optimize("Ofast")
#include <iostream>
#include <set>

const int MAXN = 1e6 + 50;
using namespace std;
int ans[MAXN];
set<int> S;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N ,val ,father; cin >> N;
    int i ,j ,on;
    bool left ,right ,flag;
    for(i = 0;i < N;i++) {
        cin >> val;
        if(S.empty()) {
            tree[val] = node{-1 ,-1 ,0};
            tree[val].par[0] = val;
        } else {
            auto it = S.lower_bound(val);
            if(it == S.end()) {
                father = *S.rbegin();
                tree[father].r = val;
            } else {
                left = (tree[*it].l == -1);
                right = (it != S.begin() && tree[*prev(it)].r == -1);
                if(left && right) {
                    flag = true; //LCA(*prev(it) ,*it) < val;
                } else flag = left;

                if(flag) {
                    father = *it;
                    tree[father].l = val;
                } else {
                    it = prev(it);
                    father = *it;
                    tree[father].r = val;
                }
            }
            tree[val] = node{-1 ,-1 ,tree[father].dep + 1};
            tree[val].par[0] = father;
            if(tree[father].l != -1 && tree[father].r != -1) S.erase(father);
        }
        on = tree[val].par[0];
        for(j = 0;j < MAXL;j++) {
            tree[val].par[j] = on;
            on = tree[on].par[j];
        }
        S.insert(val);
    }
    for(i = 1;i <= N;i++) cout << (tree[i].par[0] == i ? 0 : tree[i].par[0]) << '\n';
}
