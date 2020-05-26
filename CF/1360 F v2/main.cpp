#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int main() {
    int T, N, M, diff;
    for(cin >> T;T--;) {
        cin >> N >> M;
        vector<string> raw; string temp; bool valid = false;
        for(int i = 0;i < N;i++) { cin >> temp; raw.push_back(temp); }
        for(int pos = 0;pos < M;pos++) {
            for(char c = 'a';c <= 'z';c++) {
                temp = raw[0]; temp[pos] = c; valid = true;
                for(int i = 1;i < N;i++) {
                    diff = 0;
                    for(int j = 0;j < M;j++) if(temp[j] != raw[i][j]) diff += 1;
                    valid &= (diff <= 1);
                }
                if(valid) goto done;
            }
        }
        valid = false;
    done:
        if(valid) cout << temp << endl;
        else cout << -1 << endl;
    }
}
