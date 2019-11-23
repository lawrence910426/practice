#include <iostream>

using namespace std;
const int MAXN = 1000005 ,INF = (1LL << 31) - 1;
struct pt {
    long long x ,y;
    pt() {}
    pt(long long X ,long long Y):x(X) ,y(Y) {}
} data[MAXN];
inline long long det(long long a ,long long b ,long long c ,long long d) { return a * d - b * c; }
bool intersect(pt p1 ,pt p2 ,pt p3 ,pt p4 ,bool edge = true) {
    long long delta = det(p2.x - p1.x ,-(p4.x - p3.x) ,p2.y - p1.y ,-(p4.y - p3.y));
    long long delta_x = det(p3.x - p1.x ,-(p4.x - p3.x) ,p3.y - p1.y ,-(p4.y - p3.y));
    long long delta_y = det(p2.x - p1.x ,p3.x - p1.x ,p2.y - p1.y ,p3.y - p1.y);
    if(delta == 0) return (delta_x == 0 && delta_y == 0);
    if(edge) {
        if(delta > 0) return (0 <= delta_x && delta_x <= delta) && (0 <= delta_y && delta_y <= delta);
        if(delta < 0) return (delta <= delta_x && delta_x <= 0) && (delta <= delta_y && delta_y <= 0);
    } else {
        if(delta > 0) return (0 < delta_x && delta_x < delta) && (0 < delta_y && delta_y < delta);
        if(delta < 0) return (delta < delta_x && delta_x < 0) && (delta < delta_y && delta_y < 0);
    }
}

int N;
pt a ,b;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,inter_a ,inter_b;
    bool obstacle;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y;
        cin >> a.x >> a.y >> b.x >> b.y;
        data[N] = data[0];
        for(inter_a = i = 0;i < N;i++) if(intersect(a ,pt(0 ,INF) ,data[i] ,data[i + 1])) inter_a += 1;
        for(inter_b = i = 0;i < N;i++) if(intersect(b ,pt(0 ,INF) ,data[i] ,data[i + 1])) inter_b += 1;
        if(inter_a % 2 == 0 && inter_b % 2 == 0) cout << "ERROR!" <<'\n';
        else if(inter_a % 2 == 0 && inter_b % 2 == 1) cout << "A troll!" << '\n';
        else if(inter_a % 2 == 1 && inter_b % 2 == 0) cout << "B troll!" << '\n';
        else {
            obstacle = false;
            for(i = 0;i < N - 1;i++)
                obstacle |= intersect(a ,b ,data[i] ,data[i + 1] ,false);
            if(obstacle) cout << "Bug!" << '\n';
            else cout << "Okay!" << '\n';
        }
    }
}
