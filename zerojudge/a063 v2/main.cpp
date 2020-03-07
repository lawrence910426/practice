#include <iostream>
#include <random>
#include <memory.h>
using namespace std;

const int MAXN = 2e5;
struct node { int l ,r ,rev ,key ,val ,pri ,siz; } data[MAXN];
class TP {
    int root ,used;
    void Split(int self ,int key ,int& left ,int& right) {
        if(self == -1) {
            left = right = -1;
        } else {
            Push_Down(self);
            int lsiz = (data[self].l == -1 ? 0 : data[data[self].l].siz);
            if(key <= lsiz) {
                left = self;
                Split(data[self].r ,key ,data[left].r ,right);
            } else {
                right = self;
                Split(data[self].l ,key - lsiz - 1 ,left ,data[right].l);
            }
            Pull_Up(left); Pull_Up(right);
        }
    }
    int Merge(int left ,int right) {
        if(left == -1) return right;
        if(right == -1) return left;
        Push_Down(left); Push_Down(right);
        if(data[left].pri < data[right].pri) {
            data[left].r = Merge(data[left].r ,right);
            Pull_Up(left); return left;
        } else {
            data[right].l = Merge(left ,data[right].l);
            Pull_Up(right); return right;
        }
    }
    void Send(int x) { swap(data[x].l ,data[x].r); data[x].rev ^= 1; }
    void Push_Down(int x) {
        if(data[x].rev == 0) return;
        if(data[x].l != -1) Send(data[x].l);
        if(data[x].r != -1) Send(data[x].r);
        data[x].rev = 0;
    }
    void Pull_Up(int x) {
        if(x == -1) return;
        data[x].siz = 1;
        if(data[x].l != -1) data[x].siz += data[data[x].l].siz;
        if(data[x].r != -1) data[x].siz += data[data[x].r].siz;
    }
    void Dfs(int on) {
        if(on == -1) return;
        Push_Down(on);
        Dfs(data[on].l);
        printf("self:%d\tl:%d\tr:%d\tsiz:%d\tval:%d\tpri:%d\n" ,on ,data[on].l ,data[on].r ,data[on].siz ,data[on].val ,data[on].pri);
        Dfs(data[on].r);
    }
    void Show(int on) {
        if(on == -1) return;
        Show(data[on].l);
        cout << data[on].val << " ";
        Show(data[on].r);
    }
public:
    TP() { memset(data ,-1 ,sizeof(data)); root = 0; used = 1; data[0] = node{-1 ,-1 ,0 ,0 ,0}; }
    void Insert(int val ,int pos) {
        int left = -1 ,right = -1;
        Split(root ,pos + 1 ,left ,right);
        data[used] = node{-1 ,-1 ,0 ,pos ,val ,rand() ,1};
        root = Merge(Merge(left ,used) ,right);
        used += 1;
    }
    void Flip(int l ,int r) {
        int left = -1 ,mid = -1 ,right = -1;
        cout << "o-----" << endl; Dfs(root);
        Split(root ,l ,left ,mid);
        Split(mid ,r ,mid ,right);
        cout << "l-----" << endl; Dfs(left);
        cout << "m-----" << endl; Dfs(mid);
        cout << "r-----" << endl; Dfs(right);
        Send(mid);
        Merge(left ,Merge(mid ,right));
    }
    void Show() { Show(root); }
} Treap;

int main() {
    srand(0);
    int N ,Q; cin >> N >> Q;
    int i ,l ,r;
    for(i = 1;i <= N;i++) { Treap.Insert(i ,i); cout << endl; }
    while(Q--) { cin >> l >> r; Treap.Flip(l ,r + 1); }
    Treap.Show();
}
