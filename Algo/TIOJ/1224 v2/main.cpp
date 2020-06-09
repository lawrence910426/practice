#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <memory.h>
using namespace std;

#define MAXN 1000005
struct segment {
    int value ,ans;
}seg[MAXN * 5];
tuple<int ,int ,int ,bool> lines[200005];

void modify(int l ,int r ,int ql ,int qr ,int id ,int value) {
    if(qr <= l || r <= ql) return;
    if(ql <= l && r <= qr) {
        seg[id].value += value;
    } else {
        modify(l ,(l + r) / 2 ,ql ,qr ,id * 2 + 1 ,value);
        modify((l + r) / 2 ,r ,ql ,qr ,id * 2 + 2 ,value);
    }

    if(seg[id].value == 0) {
        if(l + 1 == r) seg[id].ans = 0;
        else seg[id].ans = seg[id * 2 + 1].ans + seg[id * 2 + 2].ans;
    } else seg[id].ans = r - l;
}

int main()
{
    memset(seg ,0 ,sizeof(seg));
    int l ,r ,u ,d ,N ,last ,pos ,val;
    int i;
    long long int ans ,tmp;
    cin >> N;
    for(i = 0;i < N * 2;i += 2) {
        cin >> l >> r >> u >> d;
        lines[i] = {l ,u ,d ,true};
        lines[i + 1] = {r ,u ,d ,false};
    }
    sort(lines ,lines + N * 2);
    ans = last = 0;
    for(i = 0;i < N * 2;i++) {
        pos = get<0>(lines[i]);
        val = (get<3>(lines[i]) ? 1 : -1);
        tmp = pos - last;
        tmp *= seg[0].ans;
        ans += tmp;
        last = pos;
        modify(0 ,MAXN ,get<1>(lines[i]) ,get<2>(lines[i]) ,0 ,val);
    }
    cout << ans << endl;
    //system("pause");
}
