#include <iostream>
#include <cstring>
#include <memory.h>

using namespace std;
int N ,Q ,counter = 0 ,a ,b;
string cmd;
struct linked_list {
    int prev ,next ,value;
} llist[3000000];
int head[300] ,tail[300];


int main() {
    int i ,on;
    while(cin >> N >> Q) {
        counter = 0;
        memset(llist ,0 ,sizeof(llist));
        for(i = 1;i <= N;i++) {
            head[i] = counter;
            tail[i] = -1;
            counter += 1;
        }
        while(Q--) {
            cin >> cmd;
            if(cmd == "ADD") {
                cin >> a >> b;
                if(tail[a] == -1) {
                    tail[a] = head[a];
                    llist[head[a]].prev = llist[head[a]].next = head[a];
                    llist[head[a]].value = b;
                } else {
                    llist[tail[a]].next = counter;
                    llist[counter].prev = tail[a];
                    llist[counter].next = counter;
                    llist[counter].value = b;
                    tail[a] = counter;
                    counter += 1;
                }
            } else if(cmd == "LEAVE") {
                cin >> a;
                if(tail[a] == -1) {
                    cout << "queue " << a << " is empty" << endl;
                } else {
                    if(head[a] == tail[a]) {
                        tail[a] = -1;
                    } else {
                        head[a] = llist[head[a]].next;
                        llist[head[a]].prev = head[a];
                    }
                }
            } else {
                cin >> a >> b;
                if(tail[a] == -1) continue;
                if(tail[b] == -1) {
                    head[b] = head[a];
                    tail[b] = tail[a];
                } else {
                    llist[tail[b]].next = head[a];
                    llist[head[a]].prev = tail[b];
                    tail[b] = tail[a];
                }
                head[a] = counter++;
                tail[a] = -1;
            }
        }
        for(i = 1;i <= N;i++) {
            cout << "queue " << i << ": ";
            if(tail[i] == -1) cout << "empty";
            else {
                for(on = head[i];on != tail[i];on = llist[on].next) cout << llist[on].value << " ";
                cout << llist[on].value << " ";
            }
            cout << endl;
        }
    }
}
