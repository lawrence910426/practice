#include <iostream>

using namespace std;

int data[200005];
int main() {
    int N ,M ,K ,ans;
    int i ,ptr;
    while(cin >> N >> M >> K) {
        for(i = 0;i < N;i++) cin >> data[i];
        ans = 0;
        for(ptr = K;ptr < N;ptr += K * 2 + 1)
            ans += data[ptr];
        ptr -= K + 1;
        if(ptr != N - 1) {
            ans += data[N - 1];
        }
        cout << ans << endl;
    }
}
/* not done yet */
/*
6 2 1
3 3 3 1 3 2

3 8 1
6 9 6

5 2 1
3 5 4 5 3

7 1 2
2 2 3 2 3 2 2

7 7 1
7 7 1 1 2 2 2
*/
