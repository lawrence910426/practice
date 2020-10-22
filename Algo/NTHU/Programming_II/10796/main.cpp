#include <iostream>

using namespace std;

int data[30][30];
int main() {
    int N;
    cin >> N;
    int i, j;

    for(i = 0;i < N;i++) for(j = 0;j < N;j++) cin >> data[i][j];
    for(i = 0;i < N;i++) for(j = 0;j <= i;j++) cout << data[i - j][j] << (j == i ? '\n' : ' ');
    for(i = 1;i < N;i++) for(j = 0;i + j < N;j++) cout << data[N - j - 1][i + j] << (i + j == N - 1 ? '\n' : ' ');
}
