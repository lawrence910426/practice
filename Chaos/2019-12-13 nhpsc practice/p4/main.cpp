#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
const int MAXM = 1e3 + 50 ,MAXV = 1e4;
int M ,N ,K ,L;
vector<pair<int ,bool> > G[MAXV];
bitset<MAXV> visit;
int find_route(int on ,bool type) {
    if(visit[on]) return -1;
    visit[on] = true;;
    int longest = 0 ,result;
    for(auto edge : G[on]) if(edge.second == type) {
        //cout << on << " " << edge.first << " " << type << " " << "in" << endl;
        result = find_route(edge.first ,!type);
        //cout << on << " " << edge.first << " " << type << " " << result << endl;
        if(result == -1) continue;
        if(type && result % 2 == 0) longest = max(longest ,result);
        if(!type && result % 2 == 1) longest = max(longest ,result);
    }
    return (longest + 1);
}
int main() {
    int i ,src ,dst ,type ,ans ,result;
    while(cin >> M >> N >> K >> L) {
        for(i = 0;i < MAXV;i++) G[i] = vector<pair<int ,bool> >();
        for(i = 0;i < K;i++) {
            cin >> src >> dst >> type;
            dst += MAXM;
            G[src].push_back(pair<int ,bool>(dst ,type == 1));
            G[dst].push_back(pair<int ,bool>(src ,type == 1));
        }
        ans = -1;
        for(i = 1;i <= M;i++) {
            visit.reset();
            result = find_route(i ,false) - 1;
            //cout << endl;
            if(result == -1 || result % 2 == 0) continue;
            ans = max(ans ,result);
        }
        for(i = MAXM + 1;i <= MAXM + N;i++) {
            visit.reset();
            result = find_route(i ,false) - 1;
            //cout << endl;
            if(result == -1 || result % 2 == 0) continue;
            ans = max(ans ,result);
        }
        cout << ans << endl;
    }
}
