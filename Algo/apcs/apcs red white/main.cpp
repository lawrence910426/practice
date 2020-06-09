#include <iostream>
#include <memory.h>
#include <map>
#include <vector>
#include <set>

using namespace std;
#define N 100005
int dsu[N] ,gsize[N];
map<int ,set<int> > query;
int n;

int getboss(int i) {
    if(dsu[i] == -1) return -1;
    else if(dsu[i] == i) return i;
    else return dsu[i] = getboss(dsu[i]);
}

void combine(int a ,int b) {
    int aboss = getboss(a) ,bboss = getboss(b);
    dsu[aboss] = bboss;
    query[gsize[aboss]].erase(aboss);
    query[gsize[bboss]].erase(bboss);
    gsize[bboss] += gsize[aboss];
    query[gsize[bboss]].insert(bboss);

    if(query[gsize[aboss]].empty()) query.erase(gsize[aboss]);
}

void init(int eax) {
    if(query.find(gsize[eax]) == query.end()) {
        query[gsize[eax]] = set<int>();
    }
    query[gsize[eax]].insert(eax);
}

int main() {
    int k ,mini ,maxi;
    int i ,eax;
    while(cin >> n >> k) {
        memset(dsu ,0 ,sizeof(dsu)), memset(gsize ,0 ,sizeof(gsize));
        query = map<int ,set<int> >();

        for(i = 0;i < n;i++) {
            cin >> eax;
            if(eax == 0) {
                dsu[i] = -1;
            } else {
                dsu[i] = i;
                gsize[i] = 1;
                if(i != 0 && dsu[i - 1] != -1) {
                    dsu[i] = dsu[i - 1];
                    gsize[getboss(i)] += 1;
                }
            }
        }

        for(i = 0;i < n;i++) {
            if(dsu[i] == i) {
                init(i);
            }
        }


        mini = query.begin()->first ,maxi = (--query.end())->first;
        while(k--) {
            cin >> eax;
            eax -= 1;

            dsu[eax] = eax;
            gsize[eax] = 1;
            init(eax);

            if(eax == 0) {
                if(dsu[eax + 1] != -1) {
                    combine(eax ,eax + 1);
                }
            } else if(eax == n - 1) {
                if(dsu[eax - 1] != -1) {
                    combine(eax ,eax - 1);
                }
            } else {
                if(dsu[eax + 1] != -1) {
                    combine(eax ,eax + 1);
                }
                if(dsu[eax - 1] != -1) {
                    combine(eax ,eax - 1);
                }
            }
            mini += query.begin()->first;
            maxi += (--query.end())->first;
        }
        printf("%d\n%d\n" ,maxi ,mini);
    }
}

/*
5 1
1 0 1 0 1
2

9 3
0 1 1 0 0 1 0 1 0
5 1 7
*/
