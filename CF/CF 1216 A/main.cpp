#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int length ,diff;
    int i;
    string s;
    while(cin >> length) {
        cin >> s;
        for(diff = i = 0;i < length;i += 2) {
            if(s[i] == s[i + 1]) {
                if(s[i] == 'a') s[i] = 'b';
                else s[i] = 'a';
                diff += 1;
            }
        }
        cout << diff << endl << s << endl;
    }
}
