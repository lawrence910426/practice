#include <iostream>
#include <map>
using namespace std;

map<int ,int> data;
int raw[1000000] ,ans;

void insert(int value) {
    if(data.find(value) == data.end()) data[value] = 1;
    else data[value] += 1;
}

void remove(int value) {
    map<int ,int>::iterator it = data.find(value);
    if(it->second == 1) data.erase(it);
    else it->second -= 1;
}

void update() {
    int diff = (--data.end())->first - data.begin()->first;
    if(diff > ans) ans = diff;
}

int main()
{
    int N ,L;
    int i;
    while(cin >> N >> L) {
        data.clear();
        ans = -1;
        for(i = 0;i < L && i < N;i++) {
            cin >> raw[i];
            insert(raw[i]);
            update();
        }
        for(;i < N;i++) {
            cin >> raw[i];
            remove(raw[i - L]);
            insert(raw[i]);
            update();
        }
        cout << ans << endl;
    }
}
