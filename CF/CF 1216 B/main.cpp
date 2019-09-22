#include <iostream>
#include <algorithm>
using namespace std;
struct p{
    int value ,code;
} data[10000];

bool cmp(p a ,p b) {
    return a.value > b.value;
}

int main() {
    int N ,ans;
    int i;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].value ,data[i].code = i;
        sort(data ,data + N ,cmp);
        ans = 0;
        for(i = 0;i < N;i++) {
            ans += data[i].value * i + 1;
        }
        cout << ans << endl;
        for(i = 0;i < N;i++) cout << data[i].code + 1 << " ";
        cout << endl;
    }
}
