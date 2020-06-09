#include <iostream>
#include <cmath>
#include <queue>
#include <set>
#include <assert.h>

const int MAXN = 1005;
const float eps = 1e6;
/* [-1]:end ,[0]:intersect ,[1]:start */
int N;
struct pt {
    float x ,y;
    int code ,style;
    bool is_null() { return code == -1; }
    pt(float X ,float Y ,int c ,int s):x(X) ,y(Y) ,code(c) ,style(s) {}
    pt operator- (pt p) { return pt(x - p.x ,y - p.y ,-1 ,-1); }
    bool operator< (pt p) {
        if(abs(x - p.x) < eps) return code > p.code;
        else return x < p.x;
    }
    bool operator> (pt p) {
        if(abs(x - p.x) < eps) return code < p.code;
        else return x > p.x;
    }
    bool operator== (pt p) {
        if(style == 0 && p.style == 0) return (abs(x - p.x) < eps) && (abs(y - p.y) < eps);
        else return (abs(x - p.x) < eps) && (abs(y - p.y) < eps) && code == p.code && style == p.style;
    }
};
float xpos;
struct seg {
    pt pa ,pb;
    seg(pt a ,pt b): pa(a) ,pb(b) {}
    pt intersect(seg s) {

    }
    float get_pos() {
        assert(abs(pb.x - pa.x) >= eps);
        return (xpos - pa.x) / (pb.x - pa.x) * (pb.y - pa.y) + pa.y;
    }
    bool operator< (seg s) { return get_pos < s.get_pos(); }
} segs[MAXN];

using namespace std;
int main() {
    int isec_count;
    int i;
    while(cin >> N) {
        map<pt ,int> Event;
        set<seg> S;
        for(i = 0;i < N;i++) {
            segs[i].pa.code = segs[i].pb.code = i;
            cin >> segs[i].pa.x >> segs[i].pa.y >> segs[i].pb.x >> segs[i].pb.y;
            segs[i].pa.style = 1 ,segs[i].pb.style = -1;
            Event[segs[i].pa] = Event[segs[i].pa] + 1;
            Event[segs[i].pb] = Event[segs[i].pb] + 1;
        }
        isec_count = 0;
        while(!PQ.empty()) {
            pt event = PQ.top();
            PQ.pop();
            xpos = event.x;
            if(event.style == 1) {
                S.insert(segs[event.code]);
            } else if(tmp.style == -1) {

            } else {

            }
        }
    }
}
// I quit.
// This algorithm is too hard to implement and it can be only used in several occasions.
