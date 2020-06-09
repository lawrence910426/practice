#include <iostream>
#define NN 150005
using namespace std;
int raw[NN] ,suffix[NN];

int main() {
    int T ,N ,ans;
    int i;
    for(cin >> T;T--;) {
        cin >> N;
        for(i = 0;i < N;i++) cin >> raw[i];
        for(i = N - 1;i >= 0;i--)
            if(i == N - 1) suffix[i] = raw[i];
            else suffix[i] = min(raw[i] ,suffix[i + 1]);
        for(ans = i = 0;i < N - 1;i++) {
            if(suffix[i + 1] < raw[i]) ans += 1;
        }
        cout << ans << endl;
    }
}
