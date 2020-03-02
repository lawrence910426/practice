#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e6 + 50;
struct Rect { int x1 ,x2 ,y1 ,y2 ,wei; } raw[MAXN];
struct Event { int l ,r ,w; };

class seg {
    struct item { int maxi ,tag ,l ,r; } data[MAXN * 5];
    int siz ,root ,cnt = 0;
    int Build(int id ,int l ,int r) {
        if(l == r - 1) data[id] = item{0 ,0 ,-1 ,-1};
        else data[id] = item{0 ,0 ,Build(cnt++ ,l ,(l + r) / 2) ,Build(cnt++ ,(l + r) / 2 ,r)};
        return id;
    }
    void Pull_Up(int id) {
        data[id].maxi = 0;
        if(data[id].l != -1) data[id].maxi = max(data[id].maxi ,data[data[id].l].maxi);
        if(data[id].r != -1) data[id].maxi = max(data[id].maxi ,data[data[id].r].maxi);
        data[id].maxi += data[id].tag;
    }
    void Modify(int id ,int ql ,int qr ,int l ,int r ,int val) {
        if(r <= ql || qr <= l) return;
        if(ql <= l && r <= qr) data[id].tag += val;
        else {
            Modify(data[id].l ,ql ,qr ,l ,(l + r) / 2 ,val);
            Modify(data[id].r ,ql ,qr ,(l + r) / 2 ,r ,val);
        }
        Pull_Up(id);
    }
public:
    seg() {}
    seg(int N):siz(N) { root = Build(cnt++ ,0 ,N); }
    void Modify(int l ,int r ,int val) { Modify(root ,l ,r ,0 ,siz ,val); }
    int Query(int l ,int r) { return data[root].maxi; }
} st;

vector<int> X ,Y;
vector<Event> Process[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,ans ,sum; cin >> N; st = seg(MAXN);
    int i;
    for(i = 0;i < N;i++) {
        cin >> raw[i].x1 >> raw[i].y1 >> raw[i].x2 >> raw[i].y2 >> raw[i].wei;
        X.push_back(raw[i].x1); X.push_back(raw[i].x2);
        Y.push_back(raw[i].y1); Y.push_back(raw[i].y2);
    }
    sort(X.begin() ,X.end()); sort(Y.begin() ,Y.end());
    auto x_last = ++unique(X.begin() ,X.end()) ,y_last = ++unique(Y.begin() ,Y.end());
    for(i = 0;i < N;i++) {
        raw[i].x1 = lower_bound(X.begin() ,x_last ,raw[i].x1) - X.begin();
        raw[i].x2 = lower_bound(X.begin() ,x_last ,raw[i].x2) - X.begin();
        raw[i].y1 = lower_bound(Y.begin() ,y_last ,raw[i].y1) - Y.begin();
        raw[i].y2 = lower_bound(Y.begin() ,y_last ,raw[i].y2) - Y.begin();
    }
    for(i = 0;i < N;i++) {
        st.Modify(raw[i].y1 ,raw[i].y2 + 1 ,raw[i].wei);
        Process[raw[i].x1].push_back(Event{raw[i].y1 ,raw[i].y2 + 1 ,raw[i].wei});
        Process[raw[i].x2 + 1].push_back(Event{raw[i].y1 ,raw[i].y2 + 1 ,-raw[i].wei});
    }
    ans = st.Query(0 ,MAXN); sum = 0;
    for(i = 0;i < x_last - X.begin();i++) {
        for(Event e : Process[i]) { st.Modify(e.l ,e.r ,-e.w); sum += e.w; }
        //cout << st.Query(0 ,MAXN) + sum << endl;
        ans = max(ans ,st.Query(0 ,MAXN) + sum);
    }
    cout << ans << endl;
}
