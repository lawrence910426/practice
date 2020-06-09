#pragma GCC optimize("Ofast")
#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 3e5 + 50 ,INF = (1LL << 31) - 1;

int H ,W ,dx[4] = {0 ,0 ,-1 ,-1} ,dy[4] = {0 ,-1 ,0 ,-1} ,prefix[MAXN];
struct infor { int x ,y ,value; } mp[MAXN];
vector<vector<int> > seat;
bool cmp(infor a ,infor b) { return a.value < b.value; }

class seg {
    struct { int l ,r ,mini ,cnt ,lazy; } data[MAXN * 3];
    int codec ,root ,N;
    void push_down(int id) {
        if(data[id].l != -1 && data[id].r != -1) {
            data[data[id].l].lazy += data[id].lazy;
            data[data[id].r].lazy += data[id].lazy;
        }
        data[id].mini += data[id].lazy;
        data[id].lazy = 0;
    }
    void pull_up(int id) {
        if(data[id].l == -1 || data[id].r == -1) return;
        if(data[data[id].l].mini > data[data[id].r].mini) {
            data[id].mini = data[data[id].r].mini;
            data[id].cnt = data[data[id].r].cnt;
        } else if(data[data[id].l].mini < data[data[id].r].mini) {
            data[id].mini = data[data[id].l].mini;
            data[id].cnt = data[data[id].l].cnt;
        } else {
            data[id].mini = data[data[id].l].mini;
            data[id].cnt = data[data[id].l].cnt + data[data[id].r].cnt;
        }
    }
    int build(int id ,int L ,int R) {
        if(L != R - 1) {
            data[id].l = build(codec++ ,L ,(L + R) / 2);
            data[id].r = build(codec++ ,(L + R) / 2 ,R);
            pull_up(id);
        } else {
            data[id].cnt = 1;
            data[id].mini = prefix[L];
            data[id].l = data[id].r = -1;
        }
        return id;
    }
    void modify(int id ,int qL ,int qR ,int L ,int R ,int value) {
        push_down(id);
        if(qR <= L || R <= qL) return;
        if(qL <= L && R <= qR) {
            data[id].lazy += value;
            push_down(id);
        } else {
            modify(data[id].l ,qL ,qR ,L ,(L + R) / 2 ,value);
            modify(data[id].r ,qL ,qR ,(L + R) / 2 ,R ,value);
            pull_up(id);
        }
    }
public:
    seg() {}
    seg(int siz):codec(0) ,N(siz) { root = build(codec++ ,0 ,N); }
    void modify(int l ,int r ,int value) { if(l != r) modify(root ,l ,r ,0 ,N ,value); }
    int get_ans() { push_down(root); return data[root].cnt; }
} st;

void pattern(int x ,int y ,int val ,bool init) {
    int A[4] = { seat[x][y] ,seat[x][y + 1] ,seat[x + 1][y] ,seat[x + 1][y + 1] };
    sort(A ,A + 4);
    if(init) {
        prefix[A[0]] += 1; prefix[A[1]] -= 1;
        prefix[A[2]] += 1; prefix[A[3]] -= 1;
    } else {
        st.modify(A[0] ,A[1] ,val);
        st.modify(A[2] ,A[3] ,val);
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int i ,j;
    long long ans;
    while(cin >> H >> W) {
        for(i = 0;i < H * W;i++) prefix[i] = 0;
        for(i = 0;i < H + 2;i++) {
            seat.push_back(vector<int>());
            for(j = 0;j < W + 2;j++) seat[i].push_back(H * W);
        }
        for(i = 1;i <= H;i++) for(j = 1;j <= W;j++) {
            cin >> seat[i][j];
            seat[i][j] -= 1;
            mp[(i - 1) * W + (j - 1)] = infor{i ,j ,seat[i][j]};
        }
        sort(mp ,mp + H * W ,cmp);

        for(i = 0;i <= H;i++) for(j = 0;j <= W;j++) pattern(i ,j ,1 ,true);
        for(i = 1;i < H * W;i++) prefix[i] = prefix[i - 1] + prefix[i];
        st = seg(H * W); ans = st.get_ans();

        for(i = 0;i < H * W - 1;i++) {
            for(j = 0;j < 4;j++) pattern(mp[i].x + dx[j] ,mp[i].y + dy[j] ,-1 ,false);
            st.modify(i ,i + 1 ,INF);
            seat[mp[i].x][mp[i].y] = H * W;
            for(j = 0;j < 4;j++) pattern(mp[i].x + dx[j] ,mp[i].y + dy[j] ,1 ,false);
            ans += st.get_ans();
        }
        cout << ans << '\n';
    }
}
