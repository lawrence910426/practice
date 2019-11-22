#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 3005;
struct pt {
    long long X ,Y;
    int code;
    pt() {}
    pt(long long x ,long long y):X(x) ,Y(y) {}
    pt operator- (pt p) { return pt(X - p.X ,Y - p.Y); }
} data[MAXN] ,convex[MAXN];
bool cmp(pt a ,pt b) { return a.X < b.X; }
long long det(pt a ,pt b) { return a.X * b.Y - a.Y * b.X; }
long long dis(pt a ,pt b) { return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y); }
int N ,len;

void build() {
    sort(data ,data + N ,cmp);
    int i ,blocker;
    convex[0] = data[0] ,convex[1] = data[1] ,len = 2;
    for(i = 2;i < N;i++) {
        while(len >= 2 && det(convex[len - 2] - convex[len - 1] ,data[i] - convex[len - 1]) <= 0) len--;
        convex[len++] = data[i];
    }
    blocker = len;
    for(i = N - 1;i >= 0;i--) {
        while(len > blocker && det(convex[len - 2] - convex[len - 1] ,data[i] - convex[len - 1]) <= 0) len--;
        convex[len++] = data[i];
    }
    /*cout << "length: " << len << endl;
    for(i = 0;i < len;i++) cout << convex[i].X << " " << convex[i].Y << " " << convex[i].code << endl;*/
}

long long ans ,ans_tmp;
int ans_a ,ans_b ,tmp_a ,tmp_b;
void update(pt a ,pt b) {
    ans_tmp = dis(a ,b);
    tmp_a = min(a.code ,b.code);
    tmp_b = max(a.code ,b.code);
    if(ans < ans_tmp) {
        ans = ans_tmp;
        ans_a = tmp_a;
        ans_b = tmp_b;
    } else if(ans == ans_tmp && tmp_a < ans_a) {
        ans_a = tmp_a;
        ans_b = tmp_b;
    } else if(ans == ans_tmp && tmp_a == ans_a && tmp_b < ans_b) {
        ans_b = tmp_b;
    }
}

void rotating_calliper() {
    convex[len] = convex[0];
    int lptr ,rptr;
    for(lptr = 0 ,rptr = 1;lptr < len;lptr++) {
        while(det(convex[lptr + 1] - convex[lptr] ,convex[rptr + 1] - convex[rptr]) < 0) {
            update(convex[lptr] ,convex[rptr]);
            update(convex[lptr + 1] ,convex[rptr + 1]);
            rptr = (rptr + 1) % len;
        }
        update(convex[lptr] ,convex[rptr]);
        update(convex[lptr + 1] ,convex[rptr + 1]);
    }
}

int main() {
    int i;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) cin >> data[i].X >> data[i].Y ,data[i].code = i;
        ans = -1;
        build();
        rotating_calliper();
        cout << ans_a << " " << ans_b << endl;
    }
}
