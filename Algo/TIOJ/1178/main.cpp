#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 1e6 + 10;
struct pt {
    long long x ,y;
    pt(long long X ,long long Y): x(X) ,y(Y) {}
    pt() {}
    bool operator< (pt& p) {
        if(x == p.x) return y < p.y;
        else return x < p.x;
    }
}data[MAXN];

inline int get_status(int a ,int b ,int c) {
    pt &A = data[a] ,&B = data[b] ,&C = data[c];
    pt v1 = pt(A.x - B.x ,A.y - B.y) ,v2 = pt(C.x - B.x ,C.y - B.y);
    long long det = v1.x * v2.y - v2.x * v1.y;
    if(det == 0) return 0;
    if(det > 0) return 1;
    if(det < 0) return -1;
}

int N;
int main() {
    int i ,len;
    vector<int> upper ,lower ,ans;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y;
        if(N <= 3) {
            cout << N << endl;
            continue;
        }
        sort(data ,data + N);

        upper = vector<int>();
        upper.push_back(0); upper.push_back(1);
        for(i = 2;i < N;i++) {
            upper.push_back(i);
            while(true) {
                len = upper.size();
                if(len >= 3 && get_status(upper[len - 1] ,upper[len - 2] ,upper[len - 3]) <= 0) upper.erase(upper.end() - 2);
                else break;
            }
        }
        lower = vector<int>();
        lower.push_back(N - 1); lower.push_back(N - 2);
        for(i = N - 3;i >= 0;i--) {
            lower.push_back(i);
            while(true) {
                len = lower.size();
                if(len >= 3 && get_status(lower[len - 1] ,lower[len - 2] ,lower[len - 3]) <= 0) lower.erase(lower.end() - 2);
                else break;
            }
        }

        ans = vector<int>();
        for(i = 0;i < upper.size();i++) ans.push_back(upper[i]);
        for(i = 0;i < lower.size();i++) ans.push_back(lower[i]);
        sort(ans.begin() ,ans.end());
        auto it = unique(ans.begin() ,ans.end());
        cout << it - ans.begin() << endl;
    }
}
