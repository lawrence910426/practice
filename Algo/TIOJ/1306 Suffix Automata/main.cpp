#pragma GCC optimize("Ofast")

#include <iostream>
#include <memory.h>

#define getchar getchar_unlocked
#define putchar putchar_unlocked


using namespace std;
const int MAXN = 1e4 + 50, ROOT = 0;
int str[MAXN];

class SuffixAutomata {
    struct { int len, par, kids[26], endpos_siz; } node[MAXN * 3];
    int previous, used;

    struct linked_list { int ptr, chain; } llist[MAXN * 3];
    int llist_used;
    int buckets[MAXN];
public:
    SuffixAutomata() {
        memset(node, -1, sizeof(node));
        memset(buckets, -1, sizeof(buckets));
        node[ROOT].len = 0;
        previous = 0; used = 1; llist_used = 0;
    }
    void Insert(int value) {
        int now = used, last = previous;
        previous = now;
        used += 1;

        node[now].endpos_siz = 1;
        node[now].len = node[last].len + 1;
        while(last != -1 && node[last].kids[value] == -1) {
            node[last].kids[value] = now;
            last = node[last].par;
        }

        if(last == -1) node[now].par = ROOT;
        else {
            int collision = node[last].kids[value];
            if(node[collision].len == node[last].len + 1) node[now].par = collision;
            else {
                int clone = used;
                used += 1;

                node[clone] = node[collision];
                node[clone].len = node[last].len + 1;
                node[clone].endpos_siz = 0;
                node[collision].par = node[now].par = clone;
                while(last != -1 && node[last].kids[value] == collision) {
                    node[last].kids[value] = clone;
                    last = node[last].par;
                }
            }
        }
    }
    void Init() {
        int i, temp, ptr, maxi = -1;
        for(i = 1;i < used;i++) {
            if(buckets[node[i].len] == -1) {
                buckets[node[i].len] = llist_used;
                llist[llist_used] = linked_list{i, -1};
            } else {
                temp = buckets[node[i].len];
                buckets[node[i].len] = llist_used;
                llist[llist_used] = linked_list{i, temp};
            }
            maxi = max(maxi, node[i].len);
            llist_used += 1;
        }

        for(i = maxi;i > 0;i--) {
            for(temp = buckets[i];temp != -1;temp = llist[temp].chain) {
                ptr = llist[temp].ptr;
                node[node[ptr].par].endpos_siz += node[ptr].endpos_siz;
            }
        }
    }
    int Query(int *data) {
        int i, pos = ROOT;
        for(i = 0;pos != -1 && data[i] != -1;i++) pos = node[pos].kids[data[i]];
        return (pos == -1 ? 0 : node[pos].endpos_siz);
    }
} SAM;

inline void input(int &_x) {
    _x = 0;
    int _tmp = 1; char _tc = getchar();
    while((_tc < '0' || _tc > '9') && _tc != '-') _tc = getchar();
    if(_tc == '-') _tc = getchar(), _tmp = -1;
    while(_tc >= '0' && _tc <= '9') _x = _x*10+(_tc-48), _tc = getchar();
    _x *= _tmp;
}

inline void output(int _x)
{
    char _buff[20]; int _f = 0;
    if(_x == 0) {
        _f = 1;
        _buff[0] = '0';
    } else {
        while(_x > 0)
        {
            _buff[_f++] = _x%10+'0';
            _x /= 10;
        }
    }
    for(_f-=1; _f >= 0; _f--) putchar(_buff[_f]);
    putchar('\n');
}

int main() {
    char c;
    int T, N, i, ans;
    input(T);
    while(T--) {
        SAM = SuffixAutomata();
        for(c = getchar();'a' <= c && c <= 'z';c = getchar()) SAM.Insert(c - 'a');
        SAM.Init();
        input(N);
        while(N--) {
            i = 0;
            for(c = getchar();'a' <= c && c <= 'z';c = getchar()) str[i++] = c - 'a';
            str[i] = -1;
            ans = SAM.Query(str);
            output(ans);
        }
    }
}
