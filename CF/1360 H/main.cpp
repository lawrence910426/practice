#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int T, N, M; char temp;
    long long eax, amount;
    long long l, r ,mid;
    long long median, median_index;
    vector<long long> container;
    for(cin >> T;T--;) {
        cin >> N >> M;
        container = vector<long long>();
        while(N--) {
            eax = 0;
            for(int i = 0;i < M;i++) {
                cin >> temp;
                eax <<= 1;
                eax |= (temp == '1');
            }
            container.push_back(eax);
        }
        median_index = (1LL << M) - container.size();
        if(median_index % 2 == 0) median_index = median_index / 2 - 1;
        else median_index = median_index / 2;

        sort(container.begin(), container.end());
        l = 0; r = (1LL << M);
        while(l != r - 1) {
            mid = (l + r) / 2;
            amount = lower_bound(container.begin(), container.end(), mid) - container.begin();
            amount = mid - amount;
            if(amount <= median_index) l = mid;
            if(amount > median_index) r = mid;
        }
        median = l;

        for(int i = 0;i < M;i++) cout << ((median >> (M - i - 1)) % 2 == 1 ? '1' : '0');
        cout << endl;
    }
}
/*
5
4 3
000
111
100
011
*/
