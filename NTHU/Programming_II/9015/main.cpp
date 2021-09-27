#include <iostream>
#include <cstring>

using namespace std;

int main() {
    string s;
    int i;
    while(cin >> s) {
        for(i = 0;i < s.size();i++) if(s[i] != s[s.size() - i - 1]) break;
        cout << (i == s.size() ? "Yes" : "No") << '\n';
    }
}
