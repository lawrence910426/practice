#include <iostream>
#include <assert.h>
#include <cstring>
using namespace std;

int main() {
    string s;
    while(cin >> s) {
        assert(s == "world");
        cout << "hello ," << s << endl;
    }
}
