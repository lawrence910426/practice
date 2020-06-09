#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const long long MAXN = 5e4 ,INF = (1LL << 63) - 1;
struct pt { long long x ,y; } data[MAXN];
bool comp_x(pt a ,pt b) { return a.x < b.x; }
bool comp_y(pt a ,pt b) { return a.y < b.y; }
long long dis(pt a ,pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
long long DC(int l ,int r) {
    if(l == r - 1) return INF;
    if(l == r - 2) return dis(data[l] ,data[l + 1]);
    int mid = (l + r) / 2;
    long long D = min(DC(l ,mid) ,DC(mid ,r));
    vector<pt> pts;
    int i ,j;
    pts.push_back(data[mid]);
    for(i = mid + 1;data[i].x < data[mid].x + D && i < r;i++) pts.push_back(data[i]);
    for(i = mid - 1;data[i].x > data[mid].x - D && i >= l;i--) pts.push_back(data[i]);
    sort(pts.begin() ,pts.end() ,comp_y);
    for(i = 0;i < pts.size();i++)
        for(j = 1;j <= 3;j++)
            if(i + j < pts.size())
                D = min(D ,dis(pts[i] ,pts[i + j]));
    return D;
}

int main() {
    int N, i, j;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y;
        sort(data ,data + N ,comp_x);
        printf("%.6f\n" ,sqrt(DC(0 ,N)));
    }
}
