#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N;
    multiset<int> S;
    while(cin >> N) {
        if(N == 0) {
            break;
        } else if(N == -1) {
            if(!S.empty()) {
                cout << *S.begin() << " ";
                S.erase(S.begin());
            }
        } else if(N == -2) {
            if(!S.empty()) {
                cout << *prev(S.end()) << " ";
                S.erase(prev(S.end()));
            }
        } else {
            S.insert(N);
        }
    }
}
