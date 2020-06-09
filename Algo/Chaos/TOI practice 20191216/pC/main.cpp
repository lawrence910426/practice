#include <iostream>
#include <memory.h>
using namespace std;
int T ,N ,D ,i ,j;
long long ans[100][100] ,pascal[100][100];
int main() {
    memset(pascal ,0 ,sizeof(pascal));
    pascal[1][0] = pascal[1][1] = 1;
    for(i = 2;i < 100;i++) pascal[i][0] = 1;
    for(i = 2;i < 100;i++) for(j = 1;j < 100;j++) pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
    for(i = 0;i < 100;i++) ans[1][i] = i + 1;
    for(i = 2;i < 100;i++) for(j = 0;j < 100;j++) ans[i][j] = ans[i - 1][j] + pascal[j][i];
    for(cin >> T;T--;) {
        cin >> D >> N;
        cout << ans[D][N] << endl;
    }
}
