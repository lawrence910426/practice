#include <iostream>
#include <memory.h>
using namespace std;
const int MAXN = 1e6 + 50;
int zkw[MAXN * 3] ,leaf;
void update(int pos) { for(pos += leaf + 1;pos;pos >>= 1) zkw[pos] += 1; }
int query(int nrank) {
    for(int ans = 1;true;) {
        if(ans > leaf) return ans - leaf - 1;
        if(zkw[ans * 2] >= nrank) ans = ans * 2;
        else {
            nrank -= zkw[ans * 2];
            ans = ans * 2 + 1;
        }
    }
}

inline char readchar() {
    static const size_t bufsize = 65536;
    static char buf[bufsize];
    static char *p = buf, *end = buf;
    if (p == end) end = buf + fread(buf, 1, bufsize, stdin), p = buf;
    return *p++;
}

template <class T> void input(T& a) {
    static char p;
    while ((p = readchar()) < '0') ;
    a = p ^ '0';
    while ((p = readchar()) >= '0') a *= 10, a += p ^ '0';
}

int main() {
    int Q ,cmd ,x;
    memset(zkw ,0 ,sizeof(zkw));
    for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
    for(input(Q);Q--;) {
        input(cmd);
        if(cmd == 1) {
            input(x);
            update(x);
        } else cout << query((zkw[1] + 1) / 2) << '\n';
    }
}
