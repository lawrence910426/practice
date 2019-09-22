#include <iostream>
#include <map>
#include <cstring>
#include <set>
using namespace std;

#define MAXN (1LL << 31) - 1
int main()
{
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    map<string ,map<string ,long long int> > floyd;
    set<string> names;
    int N ,M ,maxi ,code = 0;
    string a ,b;
    while(cin >> N >> M ,!(N == 0 && M == 0)) {
        floyd.clear();
        names.clear();
        while(M--) {
            cin >> a >> b;
            floyd[b][a] = floyd[a][b] = 1;
            names.insert(a);
            names.insert(b);
        }
        for(string i : names) for(string j : names) {
            if(floyd[i][j] == 0 && i != j) floyd[i][j] = MAXN;
        }

        for(string k : names) for(string i : names) for(string j : names) {
            if(floyd[i][k] == MAXN || floyd[k][j] == MAXN) continue;
            if(floyd[i][j] > floyd[i][k] + floyd[k][j])
                floyd[i][j] = floyd[i][k] + floyd[k][j];
        }

        maxi = 0;
        for(string i : names) for(string j : names) {
            maxi = (maxi > floyd[i][j] ? maxi : floyd[i][j]);
        }
        cout << "Network " << ++code << ": ";
        if(maxi == MAXN) cout << "DISCONNECTED\n\n";
        else cout << maxi << "\n\n";
    }
    cout << endl;
}
