#include <iostream>
#include <deque>
#include <memory.h>

using namespace std;
const int MAXN = 2e5 + 50;
int ans[MAXN] ,raw[MAXN];
int main() {
    int Q ,N ,colors;
    int i ,temp;
    for(cin >> Q;Q--;) {
        cin >> N;
        deque<int> circle;
        for(i = 0;i < N;i++) {
            cin >> raw[i];
            while(!circle.empty() && circle.back() == raw[i]) circle.pop_back();
            circle.push_back(raw[i]);
        }
        if(circle.back() == circle.front() && circle.size() != 1) circle.pop_back();
        if(circle.size() == 1) colors = 1;
        else {
            if(circle.size() % 2 == 0) colors = 2;
            if(circle.size() % 2 == 1) colors = 3;
        }

        memset(ans ,-1 ,sizeof(ans));
        if(colors == 1) for(i = 0;i < N;i++) ans[i] = 1;
        if(colors == 3) {
            ans[N - 1] = 3;
            for(i = N - 2;raw[i] == raw[i + 1];i--) ans[i] = 3;
        }
        if(colors == 2 || colors == 3) {
            for(i = 0;i < N && ans[i] == -1;i++) {
                if(i == 0) ans[i] = 1;
                else {
                    if(raw[i] == raw[i - 1]) ans[i] = ans[i - 1];
                    else ans[i] = (ans[i - 1] == 1 ? 2 : 1);
                }
            }
        }
        cout << colors << endl;
        for(i = 0;i < N;i++) cout << ans[i] << " ";
        cout << endl;
    }
}
