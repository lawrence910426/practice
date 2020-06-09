#pragma GCC optimize("Ofast")
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
struct person {
    long long duration;
    int name;
    person(long long D ,int N): duration(D) ,name(N) {}
    bool operator<(person p) const { return duration < p.duration; }
};
struct stellarium {
    multiset<person> data;
    long long current;
    stellarium() {
        current = 0;
        data = multiset<person>();
    }
    void insert(int name ,long long time) {
        time += current;
        data.insert(person(time ,name));
    }
    void modify(long long time ,vector<int>& ans) {
        current += time;
        auto ending = data.begin();
        while(ending != data.end()) {
            if(ending->duration <= current) {
                ans.push_back(ending->name);
                ending++;
            } else break;
        }
        data.erase(data.begin() ,ending);
    }
} handle[8];
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int i ,j ,status ,pcount;
    int ans ,q ,c ,t ,k ,z ,p;
    while(cin >> q) {
        pcount = ans = 0;
        for(i = 0;i < 8;i++) handle[i] = stellarium();
        for(i = 0;i < q;i++) {
            cin >> c;
            if(c == 1) {
                cin >> t >> k;
                t ^= ans;
                for(status = 0;k--;) {
                    cin >> z;
                    z ^= ans;
                    status |= (1 << (z - 1));
                }
                handle[status].insert(++pcount ,t);
            } else if(c == 2) {
                cin >> p >> t;
                vector<int> answer ,tmp;
                p ^= ans ,t ^= ans;
                for(j = 0;j < 8;j++) if((j >> (p - 1)) & 1) {
                    tmp.clear();
                    handle[j].modify(t ,tmp);
                    for(int i : tmp) answer.push_back(i);
                }
                sort(answer.begin() ,answer.end());
                cout << answer.size() << " ";
                for(int value : answer) {
                    cout << value << " ";
                    ans ^= value;
                }
                cout << '\n';
            } else return -1;
        }
    }
}
