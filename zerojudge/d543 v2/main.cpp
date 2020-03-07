#pragma GCC optimize("Ofast")
#include <iostream>
#include <random>

using namespace std;
const int MAXN = 1e6;
struct node { int l ,r ,val ,key ,pri ,maxi; } data[MAXN];
class T {
    int root ,used;
    void Pull_Up(int x) {
        if(x == -1) return;
        data[x].maxi = data[x].val;
        if(data[x].l != -1) data[x].maxi = max(data[x].maxi ,data[data[x].l].maxi);
        if(data[x].r != -1) data[x].maxi = max(data[x].maxi ,data[data[x].r].maxi);
    }
    int Merge(int left ,int right) {
        if(left == -1) return right;
        if(right == -1) return left;
        if(data[left].pri < data[right].pri) {
            data[left].r = Merge(data[left].r ,right);
            Pull_Up(left); return left;
        } else {
            data[right].l = Merge(left ,data[right].l);
            Pull_Up(right); return right;
        }
    }
    void Split(int self ,int& l ,int& r ,int key) {
        if(self == -1) l = r = -1;
        else {
            if(data[self].key < key) {
                l = self; Split(data[self].r ,data[l].r ,r ,key); Pull_Up(l);
            } else {
                r = self; Split(data[self].l ,l ,data[r].l ,key); Pull_Up(r);
            }
        }
    }
    void Dfs(int on) {
        if(on == -1) return;
        Dfs(data[on].l);
        printf("on:%d l:%d r:%d val:%d key:%d maxi:%d\n" ,on ,data[on].l ,data[on].r ,data[on].val ,data[on].key ,data[on].maxi);
        Dfs(data[on].r);
    }
public:
    T() { root = -1; used = 0; }
    void Insert(int pos ,int val) {
        int left = -1 ,right = -1;
        Split(root ,left, right ,pos);
        data[used] = node{-1 ,-1 ,val ,pos ,rand() ,val};
        root = Merge(left ,Merge(used ,right));
        used += 1;
    }
    int Query(int l ,int r) {
        int left = -1 ,mid = -1 ,right = -1 ,temp = -1 ,ans;
        Split(root ,left ,temp ,l);
        Split(temp ,mid ,right ,r);
        ans = data[mid].maxi;
        root = Merge(left ,Merge(mid ,right));
        return ans;
    }
} Treap;

int main() {
    int N ,Q;
    int i ,l ,r ,value;
    ios::sync_with_stdio(0); cin.tie(0);
    while(cin >> N) {
        Treap = T();
        for(i = 0;i < N;i++) { cin >> value; Treap.Insert(i ,value); }
        for(cin >> Q;Q--;) {
            cin >> l >> r;
            if(l > r) swap(l ,r);
            cout << Treap.Query(l - 1 ,r) << '\n';
        }
    }
}
