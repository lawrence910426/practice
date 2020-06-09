#include <iostream>
#include <list>
#include <cstring>
using namespace std;
list<int> L[300];
int main() {
    int N ,Q ,a ,b;
    int i;
    string cmd;
    while(cin >> N >> Q) {
        for(i = 1;i <= N;i++) L[i] = list<int>();
        while(Q--) {
            cin >> cmd;
            if(cmd == "ADD") {
                cin >> a >> b;
                L[a].push_back(b);
            } else if(cmd == "LEAVE") {
                cin >> a;
                if(L[a].empty()) cout << "queue 3 is empty!" << endl;
                else L[a].pop_front();
            } else {
                cin >> a >> b;
                L[b].emplace_back(L[a]);
                L[a].clear();
            }
        }
        for(i = 1;i <= N;i++) {
            cout << "queue " << i << ":";
            if(L[i].empty()) cout << " empty";
            else for(int tmp : L[i]) cout << tmp << " ";
            cout << endl;
        }
    }
}
