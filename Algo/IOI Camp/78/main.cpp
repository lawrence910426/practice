#include <iostream>
#include <vector>
#include <set>
#include <memory.h>

using namespace std;
const int MAXN = 2e5 + 50 ,SIZE = 1 << 19;

struct segment { int l ,r ,previous ,code; } pool[MAXN * 5];
int used;


class zkw {
public:
    int leaf;
    int data[SIZE];
    zkw() {
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        for(int i = 0;i < SIZE;i++) data[i] = -1;
    }
    void modify(int pos ,segment s) { data[leaf + pos + 1].edges.push_back(s); }
    void modify(segment s ,int pos) {
        int l = s.l ,r = s.r;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) data[l ^ 1].edges.push_back(segment{pos ,pos + 1});
            if(r % 2 == 1) data[r ^ 1].edges.push_back(segment{pos ,pos + 1});
        }
    }
    void modify(int a ,int b) { data[leaf + a + 1].edges.push_back(segment{b ,b + 1}); }
} tree;

class feeder {
    set<int> fed;
    int id ,pos ,index ,ptr;
public:
    feeder() {}
    feeder(int id ,zkw* src) {
        pos = id + src->leaf + 1;
        while(pos != 0 && tree.data[pos].edges.size() == 0) pos >>= 1;
        if(pos != 0) {
            index = 0;
            ptr = tree.data[pos].edges[index].l;
            fed = set<int>();
        } else ptr = -1;
    }
    int peek() { return ptr; }
    bool next() {
        if(pos == 0) return false;
        do {
            if(ptr + 1 == tree.data[pos].edges[index].r) {
                if(tree.data[pos].edges.size() == index + 1) {
                    pos >>= 1;
                    while(pos != 0 && tree.data[pos].edges.size() == 0) pos >>= 1;
                    if(pos == 0) { ptr = -1; return false; }
                    index = 0;
                } else index += 1;
                ptr = tree.data[pos].edges[index].l;
            } else ptr += 1;
        } while(fed.find(ptr) != fed.end());
        fed.insert(ptr);
        return true;
    }
} iter[MAXN];

int main() {
    int N ,M;
    int i ,c ,a ,b ,l ,r;
    while(cin >> N >> M) {
        tree = zkw();
        /*while(M--) {
            cin >> c;
            if(c == 1) {
                cin >> a >> b;
                tree.modify(a ,b);
            } else if(c == 2) {
                cin >> a >> l >> r;
                tree.modify(a ,segment{l ,r + 1});
            } else if(c == 3) {
                cin >> b >> l >> r;
                tree.modify(segment{l ,r + 1} ,b);
            } else return -1;
        }
        for(i = 0;i <= N;i++) for(iter[i] = feeder(i ,&tree);iter[i].peek() != -1;iter[i].next())
            cout << i << " " << iter[i].peek() << endl;*/
    }
}
