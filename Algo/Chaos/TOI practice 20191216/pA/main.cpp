#include <iostream>

using namespace std;
long long N ,step ,V ,i ,times ,src ,dst;
int main() {
    while(cin >> N >> step) {
        for(i = 1LL;i <= N;i++) {
            if(step % (1LL << i) == (1LL << (i - 1))) {
                V = i;
                break;
            }
        }
        times = (step / (1LL << V)) + 1;
        if(V % 2 == N % 2) {
            if(times % 3 == 0) {
                src = 2 ,dst = 1;
            } else if(times % 3 == 1) {
                src = 1 ,dst = 3;
            } else {
                src = 3 ,dst = 2;
            }
        } else {
            if(times % 3 == 0) {
                src = 3 ,dst = 1;
            } else if(times % 3 == 1) {
                src = 1 ,dst = 2;
            } else {
                src = 2 ,dst = 3;
            }
        }
        cout << "move " << V << " from " << src << " to " << dst << endl;
    }
}
