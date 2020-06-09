#include <iostream>
#include <ext/rope>

using namespace __gnu_cxx;
using namespace std;

struct dsu {
    int boss ,depth;
};

inline dsu* make_dsu(int boss ,int depth) {
    auto ans = new dsu();
    ans->boss = boss;
    ans->depth = depth;
    return ans;
}

rope<dsu> *history[500005];
int N ,M ,date ,a ,b;

inline int boss(int pos ,auto *domain) {
    while(pos != domain->at(pos).boss) pos = domain->at(pos).boss;
    return pos;
}

inline void join(int a ,int b ,auto domain) {
    a = boss(a ,domain) ,b = boss(b ,domain);
    if(a == b) return;
    int dep_a = domain->at(a).depth ,dep_b = domain->at(b).depth;
    if(dep_a > dep_b) {
        domain->replace(b ,*make_dsu(a ,dep_b));
    } else if(dep_a < dep_b) {
        domain->replace(a ,*make_dsu(b ,dep_a));
    } else {
        domain->replace(b ,*make_dsu(a ,dep_b));
        domain->replace(a ,*make_dsu(a ,dep_a + 1));
    }
}

inline bool same(int a ,int b ,auto domain) {
    a = boss(a ,domain);
    b = boss(b ,domain);
    return a == b;
}

inline int get_join_date() {
    int l = 0 ,r = date + 1 ,mid;
    while(l + 1 != r) {
        mid = (l + r) / 2;
        /*cout << mid << endl;
        for(int z = 0;z <= N;z++) cout << z << " " << history[mid]->at(z).boss << " " << history[mid]->at(z).depth << endl;
        cout << endl;*/
        if(same(a, b, history[mid])) r = mid;
        else l = mid;
    }
    return l + (same(a, b, history[l]) ? 0 : 1);
}

int main() {
    int j;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> M) {
        for(date = 0;date < M;date++) {
            cin >> a >> b;
            if(date == 0) {
                history[0] = new rope<dsu>();
                for(j = 0;j <= N;j++) history[0]->push_back(*make_dsu(j ,1));
            } else {
                history[date] = history[date - 1];
            }

            if(same(a ,b ,history[date])) {
                cout << get_join_date() + 1 << '\n';
            } else {
                cout << "Mukyu" << '\n';
                if(date != 0) history[date] = new rope<dsu>(*history[date - 1]);
                join(a ,b ,history[date]);
            }
        }
    }
}

/*
3 3
1 2
2 3
1 3

2 3
2 1
1 2
2 1

6 8
1 2
2 1
1 3
4 3
3 2
3 5
1 5
1 4
*/
