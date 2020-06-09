#pragma GCC optimize("Ofast,no-stack-protector")
#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
const int MAXM = 1e6+10;
struct p { int fan ,money; }data[MAXM];
bool cmp(p a ,p b) {
    if(a.money == b.money) return a.fan < b.fan;
    else return a.money > b.money;
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int N ,M ,fan ,money;
    int i;
    while(cin >> N >> M) {
        memset(data ,0 ,sizeof(data));
        for(i = 0;i < N;i++) data[i].fan = i;
        for(i = 0;i < M;i++) {
            cin >> fan >> money;
            data[fan].money += money;
        }
        sort(data ,data + N ,cmp);
        for(i = 0;i < N;i++) cout << data[i].fan << " " << data[i].money << endl;
    }
}
