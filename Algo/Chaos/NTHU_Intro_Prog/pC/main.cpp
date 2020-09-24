#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 1e3;
string content[MAXN];
int main() {
    int N;
    while(cin >> N) {
        for(int i = 0;i < N;i++) cin >> content[i];
        sort(content, content + N, [](string a, string b) {
             return a > b;
        });
        for(int i = 0;i < N;i++) cout << content[i];
        cout << endl;
    }
}
