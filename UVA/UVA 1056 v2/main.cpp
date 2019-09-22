#include <iostream>
#include <map>
#include <cstring>
#include <memory.h>

#define MAXN (1LL << 31) - 1
using namespace std;

int floyd[100][100];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    map<string ,int> codec;
    int counter = 0 ,P ,R ,code, maxi;
    int i ,j ,k;
    string a ,b;
    while(cin >> P >> R ,!(P == 0 && R == 0)) {
        codec.clear();
        code = 0;
        for(i = 0;i < P;i++) for(j = 0;j < P;j++) floyd[i][j] = MAXN;
        for(i = 0;i < R;i++) {
            cin >> a >> b;
            if(codec.find(a) == codec.end()) codec[a] = code++;
            if(codec.find(b) == codec.end()) codec[b] = code++;
            floyd[codec[a]][codec[b]] = floyd[codec[b]][codec[a]] = 1;
            floyd[codec[a]][codec[a]] = floyd[codec[b]][codec[b]] = 0;
        }
        for(k = 0;k < P;k++) for(i = 0;i < P;i++) for(j = 0;j < P;j++)
            if(floyd[i][k] == MAXN || floyd[k][j] == MAXN) continue;
            else floyd[i][j] = min(floyd[i][j] ,floyd[i][k] + floyd[k][j]);
        maxi = 0;
        for(i = 0;i < P;i++) for(j = 0;j < P;j++) maxi = max(floyd[i][j] ,maxi);
        cout << "Network " << ++counter << ": ";
        if(maxi == MAXN) cout << "DISCONNECTED\n\n";
        else cout << maxi << "\n\n";
    }
}
