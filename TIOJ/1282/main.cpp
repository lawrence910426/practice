#include <iostream>

using namespace std;

const int MAXN = 1e5 + 10;
long long gcd(long long a ,long long b) {
    if(a == -1) return b;
    if(b == -1) return a;
    return (a % b == 0 ? b : gcd(b ,a % b));
}
int N ,Q;
long long raw[MAXN];
struct seg { bool leaf; long long val ,lazy; }data[MAXN * 10];

void push_down(int code) {
    if(data[code].lazy == -1) return;
    data[code].val = gcd(data[code].val ,data[code].lazy);
    data[code * 2].lazy = gcd(data[code * 2].lazy ,data[code].lazy);
    data[code * 2 + 1].lazy = gcd(data[code * 2 + 1].lazy ,data[code].lazy);
    data[code].lazy = -1;
}

void pull_up(int code) {
    if(data[code].leaf) return;
    data[code].val = gcd(data[code * 2].val ,data[code * 2 + 1].val);
}

void build(int code ,int L ,int R) {
    data[code].lazy = -1;
    if(L == R - 1) {
        data[code].leaf = true;
        data[code].val = raw[L];
    } else {
        data[code].leaf = false;
        build(code * 2 ,L ,(L + R) / 2);
        build(code * 2 + 1 ,(L + R) / 2 ,R);
    }
    pull_up(code);
}

long long query(int code ,int L ,int R ,int qL ,int qR) {
    if(qR <= L || R <= qL) return -1;
    push_down(code);
    int mid = (L + R) / 2 ,ans = -1;
    if(qL <= L && R <= qR) ans = data[code].val;
    else {
        int rL = query(code * 2 ,L ,mid ,qL ,qR);
        int rR = query(code * 2 + 1 ,mid ,R ,qL ,qR);
        ans = gcd(rL ,rR);
    }
    pull_up(code);
    return ans;
}

void update(int code ,int L ,int R ,int qL ,int qR ,int value) {
    if(qR <= L || R <= qL) return;
    push_down(code);
    if(qL <= L && R <= qR) {
        data[code].lazy = gcd(data[code].lazy ,value);
    } else {
        int mid = (L + R) / 2;
        update(code * 2 ,L ,mid ,qL ,qR ,value);
        update(code * 2 + 1 ,mid ,R ,qL ,qR ,value);
    }
    pull_up(code);
}

int main() {
    int i ,c ,l ,r ,k;
    while(cin >> N >> Q) {
        for(i = 0;i < N;i++) cin >> raw[i];
        build(1 ,0 ,N);
        while(Q--) {
            cin >> c;
            if(c == 1) {
                cin >> l >> r >> k;
                l -= 1;
                update(1 ,0 ,N ,l ,r ,k);
            } else {
                cin >> l >> r;
                l -= 1;
                cout << query(1 ,0 ,N ,l ,r) << endl;
            }
        }
    }
}
/*
5 6
3 6 9 12 4
2 1 3
2 3 4
1 1 3 11
2 1 3
*/
