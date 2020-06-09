#include <iostream>
#include <set>
#include <deque>

using namespace std;
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    set<int> exist;
    deque<int> line;
    int Q ,N;
    int eax;
    while(cin >> Q >> N) {
        exist = set<int>() ,line = deque<int>();
        while(Q--) {
            cin >> eax;
            if(exist.find(eax) == exist.end()) {
                exist.insert(eax);
                line.push_front(eax);
                if(line.size() > N) {
                    exist.erase(line.back());
                    line.pop_back();
                }
            }
        }
        cout << line.size() << endl;
        for(;!line.empty();line.pop_front()) cout << line.front() << ' ';
        cout << endl;
    }
}
