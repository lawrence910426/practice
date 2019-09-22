#include <iostream>

using namespace std;
struct square {
    int x[2] ,y[2];
}data[3];

inline square* intersect(square* a ,square* b) {
    square* ans = new square();
    ans->x[0] = max(a->x[0] ,b->x[0]);
    ans->x[1] = min(a->x[1] ,b->x[1]);
    ans->y[0] = max(a->y[0] ,b->y[0]);
    ans->y[1] = min(a->y[1] ,b->y[1]);
    if(ans->x[0] >= ans->x[1] || ans->y[0] >= ans->y[1])
        ans->x[0] = ans->x[1] = ans->y[0] = ans->y[1] = 0;
    return ans;
}

inline long long int area(square* ans) {
    long long int tmp = ans->x[1] - ans->x[0];
    return tmp * (ans->y[1] - ans->y[0]);
}

int main() {
    cin >> data[0].x[0] >> data[0].y[0] >> data[0].x[1] >> data[0].y[1]
        >> data[1].x[0] >> data[1].y[0] >> data[1].x[1] >> data[1].y[1]
        >> data[2].x[0] >> data[2].y[0] >> data[2].x[1] >> data[2].y[1];
    long long int ans = area(&data[0]) ,
        inter_a = area(intersect(&data[0] ,&data[1])),
        inter_b = area(intersect(&data[0] ,&data[2])),
        inter_c = area(intersect(&data[0] ,intersect(&data[1] ,&data[2])));

    //cout << ans << endl << inter_a << endl << inter_b << endl << inter_c << endl;
    ans -= inter_a;
    ans -= inter_b;
    ans += inter_c;
    cout << (ans == 0 ? "NO" : "YES") << endl;
}
