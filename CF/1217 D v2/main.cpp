#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 2e5 + 10;

int monster[MAXN];
pair<int ,int> hero[MAXN]; /* first-power ,second-endureance */
int mrmq[MAXN][30] ,hrmq[MAXN][30];
inline int query_monster(int l ,int r) { int len = __lg(r - l); return max(mrmq[l][len] ,mrmq[r - (1 << len)][len]); }
inline int query_hero(int l ,int r) { int len = __lg(r - l); return max(hrmq[l][len] ,hrmq[r - (1 << len)][len]); }
int main() {
    int T ,mcount ,hcount ,l ,r ,mid ,killed ,days ,pos;
    int i ,j;
    bool unable;
    for(cin >> T;T--;) {
        cin >> mcount;
        for(i = 0;i < mcount;i++) cin >> monster[i];
        cin >> hcount;
        for(i = 0;i < hcount;i++) cin >> hero[i].first >> hero[i].second;
        sort(hero ,hero + hcount);
        for(i = 0;i < mcount;i++) mrmq[i][0] = monster[i];
        for(j = 1;j < 30;j++) for(i = 0;i < mcount;i++) {
            pos = min(mcount - 1 ,i + (1 << (j - 1)));
            mrmq[i][j] = max(mrmq[i][j - 1] ,mrmq[pos][j - 1]);
        }
        for(i = 0;i < hcount;i++) hrmq[i][0] = hero[i].second;
        for(j = 1;j < 30;j++) for(i = 0;i < hcount;i++) {
            pos = min(hcount - 1 ,i + (1 << (j - 1)));
            hrmq[i][j] = max(hrmq[i][j - 1] ,hrmq[pos][j - 1]);
        }
        unable = false;
        for(killed = days = 0;killed != mcount;days++) {
            for(l = killed ,r = mcount + 1;l != r - 1;) {
                mid = (l + r) / 2;
                int monster_strong = query_monster(killed ,mid);
                auto ptr = lower_bound(hero ,hero + hcount ,pair<int ,int>(monster_strong ,0));
                if(ptr == hero + hcount) { unable = true; break; }
                int hero_endure = query_hero(ptr - hero ,hcount);
                if(hero_endure >= (mid - killed)) l = mid;
                else r = mid;
            }
            if(l == killed || unable) { unable = true; break; }
            else killed = l;
        }
        cout << (unable ? -1 : days) << endl;
    }
}
/*
1
5
3 5 100 2 3
2
30 5
90 1
*/
