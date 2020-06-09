#include <iostream>

using namespace std;
const int MAXN = 2e5 + 50;
int A[MAXN] ,B[MAXN] ,X[MAXN];
int main() {
    int N; cin >> N;
    int i;
    for(i = 0;i < N;i++) cin >> B[i];
    X[0] = 0; A[0] = B[0];
    for(i = 1;i < N;i++) {
        X[i] = max(X[i - 1] ,A[i - 1]);
        A[i] = B[i] + X[i];
    }
    for(i = 0;i < N;i++) cout << A[i] << " ";
    cout << endl;
}
