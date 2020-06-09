#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
const int MAXN = 3e5 + 50;
struct pt {
    long long x ,y;
    bool operator==(pt a) { return a.x == x && a.y == y; }
} Point[MAXN];

long long Det(pt a ,pt mid ,pt b) {
    pt x = pt{a.x - mid.x ,a.y - mid.y} ,y = pt{b.x - mid.x ,b.y - mid.y};
    return x.x * y.y - x.y * y.x;
}
bool cmp(pt a ,pt b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

int main() {
    vector<pt> Convex;
    int N ,block;
    int i ,lptr ,rptr;
    cin >> N;
    for(i = 0;i < N;i++) cin >> Point[i].x >> Point[i].y;
    sort(Point ,Point + N ,cmp);
    Convex = vector<pt>();
    if(N <= 3) {
        for(i = 0;i < N;i++) Convex.push_back(Point[i]);
    } else {
        Convex.push_back(Point[0]); Convex.push_back(Point[1]);
        for(i = 2;i < N;i++) {
            while(Convex.size() >= 2 && Det(Convex[Convex.size() - 2] ,Convex.back() ,Point[i]) <= 0) Convex.pop_back();
            Convex.push_back(Point[i]);
        }
        block = Convex.size();
        for(i = N - 1;i >= 0;i--) {
            while(Convex.size() > block && Det(Convex[Convex.size() - 2] ,Convex.back() ,Point[i]) <= 0) Convex.pop_back();
            Convex.push_back(Point[i]);
        }
        sort(Convex.begin() ,Convex.end() ,cmp);
        Convex.erase(unique(Convex.begin() ,Convex.end()) ,Convex.end());
    }
    cout << Convex.size() << endl;
}
