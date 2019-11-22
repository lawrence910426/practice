#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct pt {
    long long X ,Y;
    int code;
    pt(){}
    pt(long long a ,long long b):X(a) ,Y(b){}
    pt operator- (const pt& a) const { return pt(X - a.X ,Y - a.Y); }
} data[100000];;
bool cmp(pt& a, pt& b) { return a.X < b.X; }
vector<int> pack ,upper ,lower;
int N;

long long det(pt va ,pt vc) { return va.X * vc.Y - va.Y * vc.X; }
int formula(pt& a ,pt& b ,pt& c) {
    long long D = det(a - b ,c - b);
    if(D == 0) return 0;
    return (D > 0 ? 1 : -1);
}
long long dis(pt& a ,pt& b) { return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y); }

void build() {
    pack = upper = lower = vector<int>();
    int i;
    if(N < 3) {
        for(i = 0;i < N;i++) pack.push_back(i);
    } else {
        sort(data ,data + N ,cmp);
        upper.push_back(0) ,upper.push_back(1);
        for(i = 2;i < N;i++) {
            upper.push_back(i);
            while(upper.size() >= 3 && formula(data[upper[upper.size() - 3]] ,data[upper[upper.size() - 2]] ,data[upper[upper.size() - 1]]) <= 0) upper.erase(upper.end() - 2);
        }
        lower.push_back(N - 1) ,lower.push_back(N - 2);
        for(i = N - 3;i >= 0;i--) {
            lower.push_back(i);
            while(lower.size() >= 3 && formula(data[lower[lower.size() - 3]] ,data[lower[lower.size() - 2]] ,data[lower[lower.size() - 1]]) <= 0) lower.erase(lower.end() - 2);
        }
        for(i = 0;i < upper.size();i++) pack.push_back(upper[i]);
        for(i = 0;i < lower.size();i++) pack.push_back(lower[i]);
    }
}

int ans_a ,ans_b ,tmp_a ,tmp_b;
long long ans ,tmp_dis;
void update(int lptr ,int rptr) {
    tmp_dis = dis(data[lptr] ,data[rptr]);
    tmp_a = min(data[lptr].code ,data[rptr].code);
    tmp_b = max(data[lptr].code ,data[rptr].code);
    if(ans < tmp_dis) {
        ans = tmp_dis;
        ans_a = tmp_a;
        ans_b = tmp_b;
    } else if(ans == tmp_dis && tmp_a < ans_a) {
        ans_a = tmp_a;
        ans_b = tmp_b;
    } else if(ans == tmp_dis && tmp_a == ans_a && tmp_b < ans_b) {
        ans_b = tmp_b;
    }
}

int main() {
    int i ,lptr ,rptr ,len;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) cin >> data[i].X >> data[i].Y ,data[i].code = i;
        build();
        ans_a = ans_b = ans = -1;
        len = pack.size(); pack.push_back(pack[0]);
        for(lptr = 0 ,rptr = 1;lptr < len;lptr++) {
            while(formula(data[pack[lptr + 1]] ,data[pack[rptr + 1]] ,data[pack[lptr]]) > formula(data[pack[lptr + 1]] ,data[pack[rptr]] ,data[pack[lptr]])) rptr = (rptr + 1) % len;
            update(pack[lptr] ,pack[rptr]);
            update(pack[lptr + 1] ,pack[rptr + 1]);
        }
        cout << ans_a << " " << ans_b << endl;
    }
}
