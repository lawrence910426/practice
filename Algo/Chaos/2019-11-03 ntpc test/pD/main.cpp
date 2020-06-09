#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int N ,K ,ans ,sum;
struct p {
    int age ,disappoint;
}data[100005];
bool cmp(p a ,p b) { return a.disappoint < b.disappoint; }

int main() {
    int i;
    set<int> mini;
    while(cin >> N >> K) {
        sum = ans = 0;
        mini.clear();
        for(i = 0;i < N;i++) cin >> data[i].age >> data[i].disappoint;
        sort(data ,data + N ,cmp);
        for(i = N - 1;i >= 0;i--) {
            mini.insert(data[i].age);
            sum += data[i].age;
            while(mini.size() > K) {
                sum -= *mini.begin();
                mini.erase(mini.begin());
            }
            ans = max(ans ,data[i].disappoint * sum);
        }
        cout << ans << endl;
    }
}
