#include <iostream>
#include <memory.h>

using namespace std;
long long int one[70] ,ans[70];
int main() {
    int N;
    int i ,j ,k ,c ,a ,r ,d ,tmp;
    while(cin >> N) {
        memset(one ,0 ,sizeof(one));
        memset(ans ,0 ,sizeof(ans));
        for(i = 0;i < N;i++) {
            cin >> c >> a >> r >> d;
            tmp = 1 << (c - 1);
            tmp = (tmp << 3) | (a << 2) | (r << 1) | d;
            one[tmp] += 1;
        }
        for(i = 0;i < 64;i++) for(j = i + 1;j < 64;j++) for(k = j + 1;k < 64;k++) {
            if(one[i] * one[j] * one[k] != 0) {
                tmp = i | j | k;
                ans[tmp] += one[i] * one[j] * one[k];
            }
        }
        cout << ans[63] << endl;
    }
}
