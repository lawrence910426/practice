#include <iostream>
#include <set>
using namespace std;

int main() {
    int N ,pos ,i ,counter ,lines ,prev;
    while(cin >> N) {
        if(N == 2) {
            cout << "1 2" << endl;
        } else if(N % 2 == 0) cout << "-1" << endl;
        else {
            counter = 0; lines = 1;
            set<int> used;
            for(i = 1;true;i++) {
                cout << endl << "siz: " << used.size() << endl;
                if(used.find(i) != used.end()) continue;
                pos = 0;
                used.insert(i); cout << endl << "insert: " << i << endl;
                do {
                    prev = pos;
                    pos += i;
                    pos %= N;

                    counter += 1;
                    if(counter == lines) {
                        lines += 1;
                        if(counter == 1) cout << prev + 1 << " ";
                        cout << pos + 1 << endl;
                        counter = 0;
                    } else {
                        if(counter == 1) cout << prev + 1 << " ";
                        cout << pos + 1 << " ";
                    }
                } while(pos != 0);
                used.insert(prev); cout << endl << "insert: " << prev << endl;
                if(used.size() == N - 1) break;
            }
        }
    }
}
