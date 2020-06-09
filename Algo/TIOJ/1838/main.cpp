#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const int MAXN = 1e5 + 10;
struct node {
    int parent ,depth;
    vector<pair<int ,int> > edges;
    inline node(): parent(-1) ,depth(0) ,edges(vector<pair<int ,int> >()) {}
}V[MAXN];
inline void build_edge(int src, int dst ,int val) { V[src].edges.push_back(pair<int ,int>(dst ,val)) ,V[dst].edges.push_back(pair<int ,int>(src ,val)); }

int dsu[MAXN];
int boss(int i) { return (i == dsu[i] ? i : dsu[i] = boss(dsu[i])); }
inline void join(int a ,int b) { if(boss(a) != boss(b)) dsu[boss(a)] = boss(b); }
int N ,M ,L;

bitset<MAXN> visit;
int get_farest(int node ,int depth ,int parent) {
    if(visit[node]) return -1;
    visit[node] = true;
    V[node].parent = parent;
    V[node].depth = depth;
    int result ,farest = node;
    for(auto p : V[node].edges) {
        result = get_farest(p.first ,depth + p.second ,node);
        if(result == -1) continue;
        if(V[result].depth > V[farest].depth) farest = result;
    }
    return farest;
}

inline void get_center(int node ,int& radius ,int& center ,int& diameter) {
    int nodeA ,nodeB;
    visit.reset() ,nodeA = get_farest(node ,0 ,-1);
    visit.reset() ,nodeB = get_farest(nodeA ,0 ,-1);
    int radiusA ,radiusB ,node_tmp;
    radius = (1LL << 31) - 1 ,diameter = V[nodeB].depth;
    for(node_tmp = nodeB;node_tmp != -1;node_tmp = V[node_tmp].parent) {
        radiusA = V[node_tmp].depth ,radiusB = diameter - radiusA;
        if(radius > max(radiusA ,radiusB)) {
            radius = max(radiusA ,radiusB);
            center = node_tmp;
        }
    }
}

bool gin(int &a){
    char c;
    while(c=getchar_unlocked(),c<'0'||c>'9')if(c==-1)return 0;
    a=c-'0';
    while(c=getchar_unlocked(),c>='0'&&c<='9')a=a*10+c-'0';
    return 1;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int src, dst ,val ,maxi1 ,maxi2 ,maxi3 ,rad ,dia ,ans;
    int i ,rad_tmp ,cent_tmp ,dia_tmp;
    vector<int> radi ,cent;
    while(gin(N) ,gin(M) ,gin(L)) {
        for(i = 0;i < MAXN;i++) dsu[i] = i;
        radi = vector<int>() ,cent = vector<int>();
        for(i = 0;i < MAXN;i++) V[i] = node();
        while(M--) {
            gin(src) ,gin(dst) ,gin(val);
            build_edge(src ,dst ,val);
        }
        for(i = 0;i < N;i++) for(auto p : V[i].edges) join(i ,p.first);
        maxi1 = maxi2 = maxi3 = rad = -1;
        for(i = 0;i < N;i++) if(dsu[i] == i) {
            get_center(i ,rad_tmp ,cent_tmp ,dia_tmp);
            if(rad < rad_tmp) rad = rad_tmp ,dia = dia_tmp ,maxi1 = cent.size();
            radi.push_back(rad_tmp) ,cent.push_back(cent_tmp);
        }
        for(rad = -1 ,i = 0;i < cent.size();i++) if(i != maxi1 && rad < radi[i]) rad = radi[i] ,maxi2 = i;
        for(rad = -1 ,i = 0;i < cent.size();i++) if(i != maxi1 && i != maxi2 && rad < radi[i]) rad = radi[i] ,maxi3 = i;
        ans = dia;
        if(maxi2 != -1) ans = max(ans ,radi[maxi2] + L + radi[maxi1]);
        if(maxi2 != -1 && maxi3 != -1) ans = max(ans ,radi[maxi2] + L + L + radi[maxi3]);
        cout << ans << '\n';
    }
}
