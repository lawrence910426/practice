#include <iostream>
#include <set>
#include <assert.h>

using namespace std;
const int MAXN = 100000 + 10;
struct seg {
    int L ,R ,value;
    seg() {}
    seg(int l ,int r ,int v): L(l) ,R(r) ,value(v) {}
    bool operator> (const seg& s) const { return (value == s.value ? (L == s.L ? R > s.R : L > s.L) : value > s.value); }
    bool operator< (const seg& s) const { return (value == s.value ? (L == s.L ? R < s.R : L < s.L) : value < s.value); }
    seg operator+ (seg& s) const {
        assert(R == s.L);
        return seg(L ,s.R ,value + s.value);
    }
    bool operator== (seg& s) const { return L == s.L && R == s.R && value == s.value; }
};
seg rseg[MAXN][2] ,real_seg[MAXN][2] ,raw[MAXN];

int main() {
    int T ,N ,K ,D;
    int i ,eax;
    set<seg> mini ,maxi;
    seg min_tmp ,max_tmp;
    for(cin >> T;T--;) {
        cin >> N >> K >> D;
        for(i = 0;i < N;i++) {
            cin >> eax;
            raw[i] = seg(i ,i + 1 ,eax);
        }
        rseg[0][0] = rseg[0][1] = raw[0];
        for(i = 1;i < N;i++) {
            min_tmp = rseg[i - 1][0] + raw[i];
            max_tmp = rseg[i - 1][1] + raw[i];
            if(min_tmp.value > raw[i].value) rseg[i][0] = raw[i];
            else {
                rseg[i][0] = min_tmp;
                rseg[i - 1][0] = seg(-1 ,-1 ,0);
            }
            if(max_tmp.value < raw[i].value) rseg[i][1] = raw[i];
            else {
                rseg[i][1] = max_tmp;
                rseg[i - 1][1] = seg(-1 ,-1 ,0);
            }
        }
        mini = set<seg>() ,maxi = set<seg>();
        for(i = 0;i < N;i++) {
            if(rseg[i][0].L != -1) mini.insert(rseg[i][0]);
            real_seg[i][0] = *mini.begin();
            if(rseg[i][1].L != -1) maxi.insert(rseg[i][1]);
            real_seg[i][1] = *(prev(maxi.end()));
        }

        for(seg s : mini) cout << s.L << " " << s.R << " " << s.value << endl;
        cout << endl;
        for(seg s : maxi) cout << s.L << " " << s.R << " " << s.value << endl;
    }
}
