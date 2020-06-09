#include <iostream>

using namespace std;
int A[100005];
int main() {
    int N ,ans;
    int i ,j;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> A[i];
        ans = 0;
        for(j = 1;j < N;j++) {
            if(j == 1) i = 0;
            if(A[j - 1] > A[i]) i = j - 1;
            ans = max(ans ,A[i] - A[j]);
        }
        cout << ans << endl;
    }
}
