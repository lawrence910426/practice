#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1e3;

int main() {
    int T, i, ptr, k;
    string s, t;
    for(cin >> T;T--;) {
        cin >> s;
        for(k = 1;k <= s.size();k++) {
            t = "";
            for(ptr = i = 0;i < k;i++) t += s[ptr++];
            while(i < s.size()) {
                while(s[i] != t[ptr - k]) {
                    t[ptr] = t[ptr - k];
                    ptr += 1;
                    if(s.size() * 2 < t.size()) goto done;
                }
                t[ptr++] = s[i];
                i += 1;
                if(s.size() * 2 < t.size()) goto done;
            }
        done:
            if(t.size() <= s.size() * 2) break;
        }
        cout << t << endl;
    }
}
