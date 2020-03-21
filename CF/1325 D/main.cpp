#include <iostream>
#include <vector>
using namespace std;

long long nxor ,sum ,diff;
int main() {
    while(cin >> nxor >> sum) {
        diff = sum - nxor;
        if(diff < 0 || diff % 2 == 1) cout << -1 << endl;
        else if(diff == 0) {
            if(sum == 0) cout << 0 << endl;
            else cout << 1 << endl << sum << endl;
        } else {
            diff /= 2;
            if((diff & nxor) == 0) cout << 2 << endl << (nxor ^ diff) << " " << diff << endl;
            else cout << 3 << endl << nxor << " " << diff << " " << diff << endl;
        }
    }
}
