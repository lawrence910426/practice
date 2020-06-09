#include <iostream>
#include <set>
using namespace std;

const int MAXN = 800000;
struct seg {
    int l ,r ,value;
    bool operator< (seg& s) { return l < s.l; }
};
struct ST { int value ,L ,R ,lazy; } st[MAXN * 5];
void build(int id ,int l ,int r) {
    st[id].L = l ,st[id].R = r;
    if(l == r - 1) return;
    build(id * 2 ,L ,(L + R) / 2);
    build(id * 2 + 1 ,(L + R) / 2 ,R);
}
void push_down(int id) {
    if(st[id].L == st[id].R - 1) st[id].value = st[id].
}
int query(int id ,int l ,int r) {

}
void modify(int id ,int l ,int r ,int value) {

}

int main() {
    set<seg> segments;

}
// too hard i quit
