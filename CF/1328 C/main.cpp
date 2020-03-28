#include <iostream>
#include <cstring>
using namespace std;

string s ,a ,b;
int T ,N;
int main() {
    int i;
    bool has_appear;
    for(cin >> T;T--;) {
        cin >> N >> s;
        has_appear = false;
        a = b = "";
        for(i = 0;i < N;i++) {
            if(s[i] == '0') { a += '0'; b += '0'; }
            if(s[i] == '1') {
                if(has_appear) { a += '0'; b += '1'; }
                else {  a += '1'; b += '0'; has_appear = true; }
            }
            if(s[i] == '2') {
                if(has_appear) { a += '0'; b += '2'; }
                else {  a += '1'; b += '1'; }
            }
        }
        cout << a << endl << b << endl;
    }
}
