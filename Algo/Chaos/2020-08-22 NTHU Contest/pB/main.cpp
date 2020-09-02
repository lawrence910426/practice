#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 50, MAXQ = 1e5 + 50;
struct Query { int L, R, K, ans; } query[MAXQ];
int sequence[MAXN];

bool able(int ans, int query_id) {

}

void solve(int l, int r, vector<int>& queries) {
    if(l == r - 1) {
        for(int i : queries) query[i].ans = l;
        return;
    }
    int mid = (l + r) / 2;
    vector<int> left, right;

}

int main() {
    int N, Q;
    int i;
    cin >> N >> Q;
    for(i = 0;i < N;i++) cin >> sequence[i];
    for(i = 0;i < Q;i++) cin >> query[i].L >> query[i].R >> query[i].K;

}
