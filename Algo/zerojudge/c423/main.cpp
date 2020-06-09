#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <assert.h>

using namespace std;
int get_root(string s) {
    int i;
    if(s.size() == 1) return s[0] - '0';
    int sum = 0;
    for(i = 0;i < s.size();i++) sum += s[i] - '0';
    string str = "";
    if(sum == 0) str = "0";
    else {
        char c;
        for(;sum;sum /= 10) {
            c = sum % 10 + '0';
            str += c;
        }
    }
    return get_root(str);
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,R;
    int i ,j;
    string s ,tmp;
    char c;
    vector<string> password;
    vector<char> roots;
    while(cin >> N >> R) {
        cin >> s;
        assert(N == s.size() + 1);
        password = vector<string>();
        roots = vector<char>();
        for(c = '0';c <= '9';c++) if(get_root(s + c) == R) roots.push_back(c);
        for(char C : roots) {
            assert('0' <= C && C <= '9');
            for(i = 0;i <= s.size();i++) {
                tmp = "";
                for(j = 0;j < i;j++) tmp = tmp + s[j];
                tmp = tmp + C;
                for(;j < s.size();j++) tmp = tmp + s[j];
                password.push_back(tmp);
            }
        }
        sort(password.begin() ,password.end());
        auto last = unique(password.begin() ,password.end());
        //assert(last - password.begin() >= 10);
        for(auto it = password.begin();it != last;it++) {
            if(it == password.begin() || it == prev(last)) continue;
            cout << *it << endl;
        }
    }
}
