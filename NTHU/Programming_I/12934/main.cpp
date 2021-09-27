#include <iostream>
#include <cstring>

using namespace std;

int mirror[10] = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};

int main() {
    string s;
    int i;
    cin >> s;
    for(i = 0;i < s.size();i++) {
        if(!('0' <= s[i] && s[i] <= '9') || mirror[s[i] - '0'] == -1) break;
        else s[i] = mirror[s[i] - '0'];
    }
    if(i != s.size()) {
        cout << "No" << endl;
    } else {
        for(i = 0;s[s.size() - 1 - i] == 0;i++) ;
        for(;i < s.size();i++) cout << (char)(s[s.size() - 1 - i] + '0');
        cout << endl;
    }
}
