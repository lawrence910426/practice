#include <iostream>
#include <unordered_set>
#include <cstring>

using namespace std;

unordered_multiset<char> S;

int main() {
    int N, M;
    string a, b;
    int i;

    while(cin >> N >> M >> a >> b) {
        S.clear();
        for(i = 0;i < N;i++) S.insert(a[i]);
        for(i = 0;i < M;i++) {
            if(S.find(b[i]) == S.end()) break;
            else S.erase(S.find(b[i]));
        }
        cout << (i == M && S.empty() ? "YES" : "NO") << endl;
    }
}
