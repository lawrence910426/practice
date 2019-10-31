#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int alen ,blen ,best = -1 ,cnt;
    int i, j;
    string a ,b;
    cin >> a >> b;
    alen = a.size() ,blen = b.size();
    for(j = 0;j < blen;j++) {
        cnt = 0;
        for(i = 0;true;i++) {
            if(!(0 <= i && i < alen)) break;
            if(!(0 <= i + j && i + j < blen)) break;
            cnt += (a[i] == b[i + j] ? 1 : 0);
        }
        best = max(best ,cnt);
    }
    for(j = 0;j < blen;j++) {
        cnt = 0;
        for(i = j;true;i++) {
            if(!(0 <= i && i < alen)) break;
            if(!(0 <= i - j && i - j < blen)) break;
            cnt += (a[i] == b[i - j] ? 1 : 0);
        }
        best = max(best ,cnt);
    }
    cout << best << '\n';
}
