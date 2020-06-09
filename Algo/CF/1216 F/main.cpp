#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


int main() {
    string s;
    int i ,ptr;
    int n ,k;
    while(cin >> n >> k) {
        cin >> s;
        hubs.clear();
        for(i = n;i > 0;i--) {
            for(ptr = i;ptr > 0;ptr--) if(s[ptr - 1] == '1') break;

        }
    }
}
