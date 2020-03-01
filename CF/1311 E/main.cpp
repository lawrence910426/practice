#include <iostream>
#include <set>
#include <stack>

using namespace std;
const int MAXN = 5e3 + 50;
int T ,N ,D ,sum ,mini ,a ,b;
int i;
struct vertex { int depth ,par ,kid; } V[MAXN];
stack<int> dep[MAXN];
set<int> removable;

int main() {
    for(cin >> T;T--;) {
        cin >> N >> D;
        for(i = 0;i < MAXN;i++) dep[i] = stack<int>();
        removable = set<int>();
        for(i = 1;i <= N;i++) { V[i].depth = V[i].par = i - 1; dep[i - 1].push(i); V[i].kid = 1; }
        mini = V[N].kid = 0; removable.insert(N);
        for(sum = N * (N - 1) / 2;sum > D;) {
            while(dep[mini].empty()) mini += 1;
            a = dep[mini].top();
            while(!removable.empty() && V[a].depth >= V[*removable.rbegin()].depth) removable.erase(*removable.rbegin());
            if(removable.empty()) break;
            else b = *removable.rbegin();
            if(sum - V[b].depth + V[a].depth + 1 >= D) {
                sum = sum - V[b].depth + V[a].depth + 1;
                if(++V[a].kid == 2) dep[mini].pop();
                if(--V[V[b].par].kid == 0) removable.insert(V[b].par);
                V[b].depth = V[a].depth + 1; V[b].par = a;
                removable.insert(b); removable.erase(a);
            } else {
                for(int U : removable) {
                    for(i = 0;i < MAXN;i++) if(!dep[i].empty()) {
                        if(sum - V[U].depth + i + 1 == D) {
                            sum = D; V[U].par = dep[i].top();
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if(sum == D) {
            cout << "YES" << endl;
            for(i = 2;i <= N;i++) cout << V[i].par << " ";
        } else cout << "NO" << endl;
    }
}
