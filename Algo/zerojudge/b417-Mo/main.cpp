#pragma GCC optimize("Ofast")

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 50, MAXQ = 1e6 + 50;
vector<int> raw = vector<int>(MAXN);

class MoAlgo {
    int N, chunk, Q = 0;
    struct q { int l, r, ans, times; };
    vector<q> query = vector<q>(MAXQ);
    vector<int> MoChunk[500];
    vector<int> statistics = vector<int>(MAXN);

    void Maintain(int& ans, int& times, int iter) {
        statistics[raw[iter]] += 1;
        if(ans < statistics[raw[iter]]) { ans = statistics[raw[iter]]; times = 1; }
        else if(ans == statistics[raw[iter]]) times += 1;
    }
public:
    MoAlgo(int N) { this->N = N; this->chunk = sqrt(N); }
    void Request(int i, int l, int r) { query[i].l = l - 1; query[i].r = r; Q += 1; }
    void Run() {
        for(int i = 0;i < Q;i++) MoChunk[query[i].l / chunk].push_back(i);
        for(int i = 0;i <= chunk + 1;i++) 
            sort(
                    MoChunk[i].begin(), 
                    MoChunk[i].end(), 
                    [this](int a, int b) { return this->query[a].r < this->query[b].r; }
            );

        for(int i = 0;i <= chunk + 1;i++) {
            int pivot = (i + 1) * chunk, right = pivot; 
            int ans = 0, times = 1, ans_prev = 0, times_prev = 1;
            for(int j : MoChunk[i]) {
                if(query[j].r < pivot) {
                    for(int iter = query[j].l;iter < query[j].r;iter++) Maintain(ans, times, iter);
                    for(int iter = query[j].l;iter < query[j].r;iter++) statistics[raw[iter]] -= 1;
                    query[j].ans = ans; query[j].times = times;
                } else {
                    for(;right < query[j].r;right++) Maintain(ans, times, right);
                    ans_prev = ans; times_prev = times;
                    for(int iter = pivot - 1;iter >= query[j].l;iter--) Maintain(ans, times, iter);
                    query[j].ans = ans; query[j].times = times;
                    for(int iter = query[j].l;iter < pivot;iter++) statistics[raw[iter]] -= 1;
                } 
                ans = ans_prev; times = times_prev;
            }
            for(int iter = pivot;iter < right;iter++) statistics[raw[iter]] -= 1;
        }
    }
    void Response(int i, int& ans, int& times) { ans = query[i].ans; times = query[i].times; }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, Q;
    cin >> N >> Q;
    int i, l, r, ans, times;
    for(i = 0;i < N;i++) cin >> raw[i];
    MoAlgo Mo = MoAlgo(N);
    for(i = 0;i < Q;i++) { cin >> l >> r; Mo.Request(i, l, r); }
    Mo.Run();
    for(i = 0;i < Q;i++) { Mo.Response(i, ans, times); cout << ans << " " << times << '\n'; }
}
