#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 10005;
int N ,ch_ptr;
struct pt { long long x ,y; int code; } data[MAXN] ,ch[MAXN];
long long cross(pt a ,pt b ,pt c) {  return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x); }
long long cross_2(pt a, pt b, pt o) { return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y); }
long long dis(pt a ,pt b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
bool cmp(pt& a ,pt& b) { return a.x < b.x; }
void convex() {
    int i ,tmp;
    sort(data ,data + N ,cmp);
    ch_ptr = 2;
    ch[0] = data[0] ,ch[1] = data[1];
    for(i = 2;i < N;i++) {
        while(ch_ptr >= 2 && cross(ch[ch_ptr - 2] ,ch[ch_ptr - 1] ,data[i]) <= 0) ch_ptr -= 1;
        ch[ch_ptr++] = data[i];
    }
    tmp = ch_ptr;
    for(i = N - 1;i >= 0;i--) {
        while(ch_ptr > tmp && cross(ch[ch_ptr - 2] ,ch[ch_ptr - 1] ,data[i]) <= 0) ch_ptr -= 1;
        ch[ch_ptr++] = data[i];
    }
}

long long ans ,ans_tmp;
int ans_a ,tmp_a ,ans_b ,tmp_b;
void update(pt a ,pt b) {
    ans_tmp = dis(a ,b);
    tmp_a = min(a.code ,b.code);
    tmp_b = max(a.code ,b.code);
    cout << ans_tmp << " " << a.code << " " << b.code << endl;
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

void callipers() {
    int lptr ,rptr;
    ch[ch_ptr] = ch[0];
    for(lptr = 0 ,rptr = 1;lptr < ch_ptr;lptr++) {
        while(cross_2(ch[lptr + 1] ,ch[rptr + 1] ,ch[lptr]) > cross_2(ch[lptr + 1] ,ch[rptr] ,ch[lptr]))
            rptr = (rptr + 1) % ch_ptr;
        update(ch[lptr] ,ch[rptr]);
        update(ch[lptr + 1] ,ch[rptr + 1]);
    }
}

void brute() { for(int i = 0;i < N;i++) for(int j = 0;j < N;j++) update(data[i] ,data[j]); }
int main() {
    int i;
    while(cin >> N ,N) {
        ans = -1;
        for(i = 0;i < N;i++) cin >> data[i].x >> data[i].y ,data[i].code = i;
        convex();
        callipers();
        /*brute();*/
        cout << ans_a << " " << ans_b << endl;
    }
}
