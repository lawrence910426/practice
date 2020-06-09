#include <iostream>

using namespace std;
const int MAXN = 2e5 + 50;
int maxi[30] ,ans[MAXN];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N;
    int i ,temp;
    char val ,ptr;
    for(i = 0;i < 30;i++) maxi[i] = 0;
    cin >> N;
    for(i = 0;i < N;i++) {
        cin >> val;
        temp = 0;
        for(ptr = val + 1;ptr <= 'z';ptr++) temp = max(temp ,maxi[ptr - 'a']);
        temp += 1;
        maxi[val - 'a'] = temp;
        ans[i] = temp;
    }
    temp = 0;
    for(ptr = 'a';ptr <= 'z';ptr++) temp = max(temp ,maxi[ptr - 'a']);
    cout << temp << endl;
    for(i = 0;i < N;i++) cout << ans[i] << " ";
}
