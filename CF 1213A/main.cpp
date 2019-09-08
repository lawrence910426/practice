#include <iostream>

using namespace std;

int main() {
    int N ,odd ,even ,in;
    while(cin >> N) {
        odd = even = 0;
        while(N--) {
            cin >> in;
            if(in % 2 == 1) {
                odd +=1;
            }
            if(in % 2 == 0) {
                even +=1;
            }
        }
        if(odd >= even) cout << even << endl;
        if(odd < even) cout << odd << endl;
    }
}
