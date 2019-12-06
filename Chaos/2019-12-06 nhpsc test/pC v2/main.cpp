#include <iostream>

using namespace std;

int main() {
    long long N ,junk;
    int i;
    while(cin >> N) {
        cout << N * (N - 1) / 2 << endl;
        for(i = 0;i < 3 * N;i++) cin >> junk;
    }
}
