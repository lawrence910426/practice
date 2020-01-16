#include <iostream>

using namespace std;
const int MAXN = 100;
struct pt {
    int x ,y;
    pt(): x(0) ,y(0) {}
    pt(int X ,int Y): x(X) ,y(Y) {}
    pt operator- (pt p) { return pt(x - p.x ,y - p.y); }
    pt operator+ (pt p) { return pt(x + p.x ,y + p.y); }
} data[MAXN];

int main() {
    int minx ,miny ,maxx ,maxy;
    int N ,i;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].x;
        for(i = 0;i < N;i++) cin >> data[i].y;
        minx = miny = (1LL << 31) - 1;
        maxx = maxy = -1;
        for(i = 0;i < N;i++) {
            minx = min(minx ,data[i].x) ,miny = min(miny ,data[i].y);
            maxx = max(maxx ,data[i].x) ,maxy = max(maxy ,data[i].y);
        }
        printf("%d %d " ,minx ,miny);
        printf("%d %d " ,minx ,maxy);
        printf("%d %d " ,maxx ,miny);
        printf("%d %d " ,maxx ,maxy);
    }
}
