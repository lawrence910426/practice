#include <iostream>
#include <cmath>

using namespace std;

long long int raw[300005];
struct segment {
    long long int value ,sum;
    int l ,r;
    bool all_one;
    segment *ls, *rs;
};

inline void pull_up(segment* seg) {
    seg->sum = 0;
    seg->sum += (seg->ls == nullptr ? 0 : seg->ls->sum);
    seg->sum += (seg->rs == nullptr ? 0 : seg->rs->sum);
    seg->all_one = true;
    seg->all_one &= (seg->ls == nullptr ? true : seg->ls->all_one);
    seg->all_one &= (seg->rs == nullptr ? true : seg->rs->all_one);
}

inline void init(long long int val ,segment* seg) {
    seg->value = val;
    seg->sum = val;
    seg->all_one = (val == 1);
}

segment* build(int l ,int r) {
    if(l == r) return nullptr;
    segment* seg = new segment();
    seg->l = l ,seg->r = r;
    seg->ls = seg->rs = nullptr;
    if(r - l == 1) {
        init(raw[l] ,seg);
    } else {
        seg->ls = build(l ,(l + r) / 2);
        seg->rs = build((l + r) / 2 ,r);
        pull_up(seg);
    }
    return seg;
}

void modify(segment* seg ,int l ,int r) {
    if(l == r || seg == nullptr || seg->all_one) return;
    if(seg->r - seg->l == 1) {
        init(sqrt(seg->value) ,seg);
    } else {
        int center = (seg->l + seg->r) / 2;
        if(l < center && r < center) {
            modify(seg->ls ,l ,r);
        } else if(center <= l && center <= r) {
            modify(seg->rs ,l ,r);
        } else if(l < center && center <= r) {
            modify(seg->ls ,l ,center);
            modify(seg->rs ,center ,r);
        }
        pull_up(seg);
    }
}

long long int query(segment* seg ,int l ,int r) {
    if(l == r || seg == nullptr) return 0;
    if(l == seg->l && r == seg->r) return seg->sum;
    long long int ans = 0;
    int center = (seg->l + seg->r) / 2;
    if(l < center && r < center) {
        ans += query(seg->ls ,l ,r);
    } else if(center <= l && center <= r) {
        ans += query(seg->rs ,l ,r);
    } else if(l < center && center <= r) {
        ans += query(seg->ls ,l ,center);
        ans += query(seg->rs ,center ,r);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,Q ,cmd ,l ,r;
    long long int ans;
    int i;
    while(cin >> N >> Q) {
        for(i = 0;i < N;i++) cin >> raw[i];
        segment* seg = build(0 ,N);
        while(Q--) {
            cin >> cmd >> l >> r;
            if(cmd == 0) {
                ans = query(seg ,l - 1 ,r);
                cout << ans << '\n';
            }
            if(cmd == 1) modify(seg ,l - 1 ,r);
        }
    }
}

/*
15 5
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
0 1 2
1 1 3
0 1 2
*/
