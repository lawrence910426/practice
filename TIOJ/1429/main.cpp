#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 50;
struct node {
    int parent; long long cost ,lead; vector<int> kids;
    node() { kids = vector<int>();}
} Ninja[MAXN];

int Limit;
class Catalogue {
    map<long long ,long long> data = map<long long ,long long>();
    long long remain = Limit ,sum = 0;
public:
    Catalogue(long long value) { data[value] = sum = 1; remain -= value; }
    long long Size() { return sum; }
    long long Upper_Gauss(long long a ,long long b) { return (a + b - 1) / b; }
    void Join(Catalogue* item) {
        Catalogue *master = this ,*slave = item;
        if(this->data.size() < item->data.size()) swap(master ,slave);
        while(!slave->data.empty()) {
            auto sit = slave->data.begin() ,mit = prev(master->data.end());
            long long unit = sit->first ,amount = sit->second ,yield ,msiz = mit->first;
            if(unit * amount > master->remain) {
                if(sit->first < msiz) {
                    yield = min(Upper_Gauss(unit * amount ,msiz) ,mit->second);
                    master->sum -= yield;
                    master->data[msiz] -= yield;
                    master->remain += yield * msiz;
                    if(master->data[msiz] == 0) master->data.erase(msiz);
                }
                amount = master->remain / unit;
                if(amount == 0) break;
            }
            master->remain -= unit * amount;
            master->sum += amount;
            master->data[unit] = master->data[unit] + amount;
            slave->data[unit] -= amount;
            if(slave->data[unit] == 0) slave->data.erase(unit);
        }
        this->data = master->data; this->remain = master->remain;
    }
};

Catalogue* dfs(int on ,long long& ans) {
    Catalogue *self = new Catalogue(Ninja[on].cost) ,*ptr;
    for(int kid : Ninja[on].kids) { self->Join(ptr = dfs(kid ,ans)); delete ptr; }
    ans = max(ans ,Ninja[on].lead * self->Size());
    return self;
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int N; long long ans;
    int i;
    while(cin >> N >> Limit) {
        for(i = 0;i < MAXN;i++) Ninja[i] = node();
        Ninja[0].lead = 0;
        for(i = 1;i <= N;i++) {
            cin >> Ninja[i].parent >> Ninja[i].cost >> Ninja[i].lead;
            Ninja[Ninja[i].parent].kids.push_back(i);
        }
        ans = -1; dfs(0 ,ans); cout << ans << endl;
    }
}
