#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 50 ,MAXD = 31;

int data[MAXN];
vector<int> appear[MAXD];
int main() {
    int N ,i ,j ,ans; cin >> N;
    for(i = 0;i < MAXD;i++) appear[i] = vector<int>();
    for(i = 0;i < N;i++) {
        cin >> data[i];
        for(j = 0;j < MAXD;j++) if((data[i] >> j) & 1)
            appear[j].push_back(i);
    }
    for(j = MAXD - 1;j >= 0;j--) if(appear[j].size() == 1) break;
    ans = (appear[j].size() == 1 ? appear[j][0] : -1);
    if(ans != -1) cout << data[ans] << " ";
    for(i = 0;i < N;i++) if(ans != i) cout << data[i] << " ";
    cout << endl;
}
