#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long int Q ,N ,M ,cycles ,remainder ,ans;
    int i ,tmp;
    vector<int> table[10];
    int table_sum[10];
    for(i = 0;i < 10;i++) {
        table_sum[i] = 0;
        table[i] = vector<int>();
        tmp = 0;
        do {
            tmp += i;
            tmp %= 10;
            table_sum[i] += tmp;
            table[i].push_back(tmp);
        } while(tmp != 0);
    }
    for(cin >> Q;Q--;) {
        cin >> N >> M;
        cycles = (N / M) / table[M % 10].size();
        remainder = (N / M) % table[M % 10].size();
        ans = cycles * table_sum[M % 10];
        for(i = 0;i < remainder;i++) ans += table[M % 10][i];
        cout << ans << endl;
    }
}
