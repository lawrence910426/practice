#include <iostream>
#include <cstring>
using namespace std;
string s;
int N;
int main() {
    int len ,lptr ,rptr ,i ,j;
    bool able;
    int ans_times;
    string ans ,ans_tmp;
    while(cin >> N) {
        ans_times = 0;
        getline(cin ,s);
        getline(cin ,s);
        for(lptr = 0;lptr < N;lptr++) for(rptr = lptr + 1;rptr <= N;rptr++) {
            for(len = 1;len <= rptr - lptr;len++) {
                if((rptr - lptr) % len != 0) continue;
                able = true;
                for(j = 0;j < len;j++) for(i = lptr + j;i + len < rptr;i += len) able &= s[i] == s[i + len];
                if(able) {
                    for(ans_tmp = "" ,i = lptr;i < lptr + len;i++) ans_tmp += s[i];
                    if(ans_times < (rptr - lptr) / len) {
                        ans = ans_tmp;
                        ans_times = (rptr - lptr) / len;
                    } else if(ans_times == (rptr - lptr) / len) {
                        if(ans.size() < ans_tmp.size()) ans = ans_tmp;
                        else if(ans.size() == ans_tmp.size() && ans > ans_tmp) ans = ans_tmp;
                    }
                }
            }
        }
        cout << ans << endl << ans_times << endl;
    }
}
