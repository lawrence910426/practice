#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 2e6;
struct person {
    long long time ,score ,vscore;
} data[MAXN];
bool cmp(person& a ,person& b) { return a.time < b.time; }

int N;
int main() {
    int i ,j;
    long long ans;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> data[i].time >> data[i].score >> data[i].vscore;
        sort(data ,data + N ,cmp);
        ans = 0;
        for(i = 0;i < N;i++) for(j = 0;j < N;j++) {
            if(i == j) continue;
            if(i < j) {
                if(data[i].score > data[j].score && data[i].vscore > data[j].vscore) ans += 1;
                if(data[i].score < data[j].score && data[i].vscore < data[j].vscore) ans += 1;
            } else {
                if(data[i].score > data[j].score && data[i].vscore < data[j].vscore) ans += 1;
                if(data[i].score < data[j].score && data[i].vscore > data[j].vscore) ans += 1;
            }
        }
        cout << ans << endl;
    }
}
