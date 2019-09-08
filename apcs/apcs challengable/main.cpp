#include <iostream>

using namespace std;
#define N 200005
int basic[N] ,extend[N];
int main()
{
    long long int ans ,mqsize ,mqlast;
    int M;
    int i;
    while(cin >> M) {
        for(i = 0;i < M;i++) cin >> basic[i];
        for(i = 0;i < M;i++) cin >> extend[i];

        mqlast = basic[0];
        mqsize = 1;
        for(ans = 0, i = 1;i < M;i++) {
            if(mqlast < basic[i] + extend[i]) {
                ans += mqsize;
            }
            printf("%d %d %d %lld %lld\n" ,basic[i] ,extend[i] ,i ,mqlast ,mqsize);

            if(mqlast <= basic[i]) {
                mqlast = basic[i];
                mqsize += 1;
            } else {
                mqsize = 1;
                mqlast = basic[i];
            }
        }
        cout << ans << endl;
    }
}
/*
8
1 2 2 3 4 4 3 1
0 0 0 0 0 0 0 0

5
5 4 1 1 3
0 0 4 0 1
*/
