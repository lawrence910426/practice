#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    string a ,b;
    int Q;
    int i;
    for(cin >> Q;Q--;) {
        cin >> a >> b;
        if(a.size() != b.size()) cout << "NO" << endl;
        else {
            for(i = 0;i < a.size();i++) {
                if('A' <= a[i] && a[i] <= 'Z') a[i] = a[i] - 'A' + 'a';
                if('A' <= b[i] && b[i] <= 'Z') b[i] = b[i] - 'A' + 'a';
                if(a[i] != b[i]) break;
            }
            cout << (i == a.size() ? "YES" : "NO") << endl;
        }
    }
}
