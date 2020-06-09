#include <iostream>
#include <cstring>
using namespace std;

string codec;

char encode(char s) {
    if('A' <= s && s <= 'Z') return codec[s - 'A'];
    if('a' <= s && s <= 'z') return codec[s - 'a' + 26];
    if('0' <= s && s <= '9') return codec[s - '0' + 26 + 26];
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N ,M;
    string raw, a ,b;
    char eax;
    int i ,j;
    while(cin >> N >> M) {
        cin >> raw >> a >> b;
        codec = "";
        for(eax = 'A';eax <= 'Z';eax++) codec += eax;
        for(eax = 'a';eax <= 'z';eax++) codec += eax;
        for(eax = '0';eax <= '9';eax++) codec += eax;
        //cout << codec << endl;
        for(i = 0;i < a.size();i++) for(j = 0;j < codec.size();j++) if(codec[j] == a[i]) codec[j] = b[i];
        //cout << codec << endl;
        for(i = 0;i < raw.size();i++) cout << encode(raw[i]);
        cout << endl;
    }
}
/*
4 3
abcd
abd
bca

1 6
a
abcdef
bcdeaf

5 3
aA0aA
aA9
9aA
*/
