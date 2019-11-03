#include <iostream>
#include <memory.h>
using namespace std;
int N ,M ,best;
long long int raw[3005][3005];
int main() {
    int i ,j;
    while(cin >> N >> M) {
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> raw[i][j];
        for(i = 0;i < N - 1;i++) for(j = 0;j < M;j++) raw[i + 1][j] = raw[i][j] + raw[i + 1][j];
        for(best = i = 0;i < M;i++) if(raw[N - 1][best] < raw[N - 1][i]) best = i;
        cout << best << " " << raw[N - 1][best] << endl;
    }
}
