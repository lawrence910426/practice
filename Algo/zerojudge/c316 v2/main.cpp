#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 1e3 + 50;
struct pt { long long x ,y; int code; } Points[MAXN];
bool cmp(pt a ,pt b) { return (a.x == b.x ? a.y < b.y : a.x < b.x); }
long long Det(pt a1 ,pt a2 ,pt b1 ,pt b2) {
    pt x = pt{a1.x - a2.x ,a1.y - a2.y} ,y = pt{b1.x - b2.x ,b1.y - b2.y};
    return x.x * y.y - x.y * y.x;
}
long long Dis(pt a ,pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
long long dis; int ansi ,ansj; vector<pt> Convex;
void Update(int a ,int b) {
    if(Dis(Convex[a] ,Convex[b]) > dis) {
        dis = Dis(Convex[a] ,Convex[b]);
        ansi = Convex[a].code; ansj = Convex[b].code;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N ,block;
    int i ,lptr ,rptr;
    while(cin >> N) {
        Convex = vector<pt>(); dis = 0;
        for(i = 0;i < N;i++) { cin >> Points[i].x >> Points[i].y; Points[i].code = i; }
        sort(Points ,Points + N ,cmp);
        if(N >= 3) {
            Convex.push_back(Points[0]); Convex.push_back(Points[1]);
            for(i = 2;i < N;i++) {
                while(Convex.size() >= 2 && Det(Convex[Convex.size() - 2] ,Convex.back() ,Points[i] ,Convex.back()) <= 0) Convex.pop_back();
                Convex.push_back(Points[i]);
            }
            block = Convex.size();
            for(i = N - 2;i >= 0;i--) {
                while(Convex.size() > block && Det(Convex[Convex.size() - 2] ,Convex.back() ,Points[i] ,Convex.back()) <= 0) Convex.pop_back();
                Convex.push_back(Points[i]);
            }
        } else for(i = 0;i <= N;i++) Convex.push_back(Points[i % N]);
        for(lptr = 0 ,rptr = 1;lptr < Convex.size();lptr++) {
            while(Det(Convex[lptr] ,Convex[lptr + 1] ,Convex[rptr] ,Convex[rptr + 1]) < 0) rptr = (rptr + 1) % Convex.size();
            Update(lptr ,rptr); Update(lptr ,rptr + 1);
        }
        cout << min(ansi ,ansj) << " " << max(ansi ,ansj) << '\n';
    }
}
