#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 50;

class Seg {
    long long data[MAXN * 3];
    int leaf;
public:
    Seg() {
        for(leaf = 1;leaf < MAXN + 2;leaf <<= 1) ;
        memset(data ,0 ,sizeof(data));
    }
    inline void Modify(int l ,int r ,long long diff) {
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) data[l ^ 1] += diff;
            if(r % 2 == 1) data[r ^ 1] += diff;
        }
    }
    inline void Modify(int pos ,long long diff) { for(pos += leaf + 1;pos >= 1;pos >>= 1) data[pos] += diff; }
    inline long long Query(int pos) {
        long long ans = 0;
        for(pos += leaf + 1;pos >= 1;pos >>= 1) ans += data[pos];
        return ans;
    }
    inline long long Query(int l ,int r) {
        long long ans = 0;
        for(l += leaf ,r += leaf + 1;l ^ r ^ 1;l >>= 1 ,r >>= 1) {
            if(l % 2 == 0) ans += data[l ^ 1];
            if(r % 2 == 1) ans += data[r ^ 1];
        }
        return ans;
    }
} seg ,fix;

struct { int nxt ,val; } raw[MAXN];
struct { int id ,ans ,first; long long goal ,sum; } Ans[MAXN];
struct { int id ,L ,R; long long V; } Modify[MAXN];
int last[MAXN] ,Farmer ,Land ,Q;

inline void Move(int src ,int dst ,vector<int>& test) {
    int diff = (src < dst ? 1 : -1) ,i ,nptr ,sptr ,sidx ,nidx;
    vector<int> nodes ,segments;
    for(int T : test) for(i = Ans[T].first;i != -1;i = raw[i].nxt) nodes.push_back(i);
    for(i = src;i != dst;i += diff) segments.push_back(i);
    sort(nodes.begin() ,nodes.end());
    sort(segments.begin() ,segments.end() ,[](int a ,int b) -> bool { return Modify[a].L < Modify[b].L; });

    for(int T : test) Ans[T].sum = 0;
    if(diff == 1) {
        for(nptr = sptr = 0;nptr < nodes.size();nptr++) {
            nidx = nodes[nptr]; sidx = segments[sptr];
            while(sptr < segments.size() && Modify[sidx].L <= nidx) {
                fix.Modify(Modify[sidx].R - 1 ,Modify[sidx].V);
                sptr += 1;
                if(sptr < segments.size()) sidx = segments[sptr];
                else break;
            }
            if(raw[nidx].nxt != -1) Ans[raw[nidx].val].sum -= fix.Query(raw[nidx].nxt ,MAXN);
        }
        while(sptr < segments.size()) {
            sidx = segments[sptr];
            fix.Modify(Modify[sidx].R - 1 ,Modify[sidx].V);
            sptr += 1;
        }
        for(i = src;i != dst;i += diff) seg.Modify(Modify[i].L ,Modify[i].R ,Modify[i].V);
    } else {
        nptr = nodes.size() - 1; sptr = segments.size() - 1;
        while(nptr >= 0) {
            nidx = nodes[nptr]; sidx = segments[sptr];
            while(sptr >= 0 && nidx < Modify[sidx].L) {
                fix.Modify(Modify[sidx].R - 1 ,-Modify[sidx].V);
                sptr -= 1;
                if(sptr >= 0) sidx = segments[sptr];
                else break;
            }
            if(raw[nidx].nxt != -1) Ans[raw[nidx].val].sum += fix.Query(raw[nidx].nxt ,MAXN);
            nptr -= 1;
        }
        while(sptr >= 0) {
            sidx = segments[sptr];
            fix.Modify(Modify[sidx].R - 1 ,-Modify[sidx].V);
            sptr -= 1;
        }
        for(i = src;i != dst;i += diff) seg.Modify(Modify[i].L ,Modify[i].R ,-Modify[i].V);
    }
    for(int T : test) for(i = Ans[T].first;i != -1;i = raw[i].nxt) Ans[T].sum += seg.Query(i);
}

void Integral_Binary_Search(int l ,int r ,vector<int>& test) {
    if(test.size() == 0) return;
    if(l == r - 1) {
        for(int i : test) Ans[i].ans = l;
    } else {
        vector<int> left ,right;
        int mid = (l + r) / 2;
        Move(l ,mid ,test);
        for(int i : test) {
            if(Ans[i].sum < Ans[i].goal) right.push_back(i);
            else left.push_back(i);
        }
        Move(mid - 1 ,l - 1 ,test);
        Integral_Binary_Search(l ,mid ,left);
        Move(l ,mid ,test);
        Integral_Binary_Search(mid ,r ,right);
        Move(mid - 1 ,l - 1 ,test);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    memset(last ,-1 ,sizeof(last)); memset(raw ,-1 ,sizeof(raw));
    memset(Ans ,-1 ,sizeof(Ans)); memset(Modify ,-1 ,sizeof(Modify));
    int i;
    cin >> Farmer >> Land >> Q;
    for(i = 0;i < Land;i++) {
        cin >> raw[i].val;
        if(last[raw[i].val] != -1) raw[last[raw[i].val]].nxt = i;
        last[raw[i].val] = i;
        if(Ans[raw[i].val].first == -1) Ans[raw[i].val].first = i;
    }
    for(i = 1;i <= Farmer;i++) {
        cin >> Ans[i].goal;
        Ans[i].id = i; Ans[i].sum = 0; Ans[i].ans = Q;
    }
    for(i = 0;i < Q;i++) {
        cin >> Modify[i].L >> Modify[i].R >> Modify[i].V;
        Modify[i].id = i; Modify[i].L -= 1;
    }
    Modify[Q].id = Q; Modify[Q].L = 0; Modify[Q].R = Land; Modify[Q].V = 0;

    vector<int> vec; for(i = 1;i <= Farmer;i++) vec.push_back(i);
    Integral_Binary_Search(0 ,Q + 1 ,vec);
    for(i = 1;i <= Farmer;i++) cout << (Ans[i].ans == Q ? -1 : Ans[i].ans + 1) << '\n';
}
/*
4 5 3
1 2 3 2 4
6 10 15 2
1 5 3
1 4 3
2 4 9
*/
