#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
const int MAXN = 100005;
struct pt {
    int x ,y;
    pt(): x(0) ,y(0) {}
    pt(int X ,int Y): x(X) ,y(Y) {}
    pt operator- (pt p) { return pt(x - p.x ,y - p.y); }
    pt operator+ (pt p) { return pt(x + p.x ,y + p.y); }
} data[MAXN];
int det(pt va ,pt vb) { return va.x * vb.y - va.y - * vb.x; }
struct line {
    int a ,b ,c; //ax + by = c;
    line(int A ,int B ,int C):a(A) ,b(B) ,c(C) {}
    line(pt pa ,pt pb) {
        int delta = det(pa ,pb);
        int deltaX = det(pt(1 ,pa.y) ,pt(1 ,pb.y));
        int deltaY = det(pt(pa.x ,1) ,pt(pa.x ,1));
        return line(deltaX ,deltaY ,delta);
    }
    line(line L ,pt p) { return line(L.a ,L.b ,a * L.a + b * L.b); }
    static pair<float ,float> intersect(line la ,line lb) {
        int delta = det(pt(a.x ,b.x) ,pt(a.y ,b.y));
        int deltaX = det(pt(a.c ,))
    }
    static float dis(pt p) { return abs(p.x * a + p.y * b - c) / sqrt(a * a + b * b); }
};
bool cmp(pt a ,pt b) { return a.x < b.x; }
bool able(pt a, pt b, pt c) {
    pt va = c - b ,vb = a - b;
    return det(va ,vb) < 0;
}
bool caliper_stop(pt a ,pt b ,pt c ,pt d) {
    pt va = b - a ,vb = d - c;
    return det(vb ,vb) >= 0;
}
vector<pt> CH;
int N;
int main() {
    int i ,block ,lptr ,rptr;
    float area;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].x;
        for(i = 0;i < N;i++) cin >> data[i].y;
        sort(data ,data + N ,cmp);
        CH.push_back(data[0]) ,CH.push_back(data[1]);
        for(i = 2;i < N;i++) {
            while(CH.size() > 2 && !able(CH[CH.size() - 2] ,CH[CH.size() - 1] ,data[i])) CH.erase(--CH.end());
            CH.push_back(data[i]);
        }
        block = CH.size();
        for(i = N - 1;i >= 0;i--) {
            while(CH.size() > block && !able(CH[CH.size() - 2] ,CH[CH.size() - 1] ,data[i])) CH.erase(--CH.end());
            CH.push_back(data[i]);
        }
        area = FLT_MAX;
        //for(pt p : CH) cout << p.x << " " << p.y << endl;
        CH.push_back(CH[0]);
        for(lptr = 0 ,rptr = 1;lptr != CH.size();lptr++) {
            while(!caliper_stop(CH[lptr] ,CH[lptr + 1] ,CH[rptr] ,CH[rptr + 1])) rptr = (rptr + 1) % CH.size();
            for(i = lptr;i <= rptr;i++) {

            }
        }
    }
}
