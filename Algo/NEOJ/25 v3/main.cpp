#include <iostream>
#include <cstring>
using namespace std;
struct item {
    item *prev ,*next;
    int value;
    item(int v): prev(nullptr) ,next(nullptr) ,value(v) {}
};
class linked_list {
    item *head ,*tail;
    bool empty = true;
public:
    linked_list():empty(true) ,head(nullptr) ,tail(nullptr) {}
    void push_back(int val) {
        if(empty) {
            head = tail = new item(val);
            empty = false;
        } else {
            item* tmp = new item(val);
            tail->next = tmp;
            tmp->prev = tail;
            tail = tmp;
        }
    }
    bool pop_front() {
        if(!empty) {
            head = head->next;
            if(head == nullptr) empty = true;
            else head->prev = nullptr;
            return false;
        } else return true;
    }
    void merge(linked_list*& L) {
        if(L->empty) return;
        if(empty) {
            head = L->head;
            tail = L->tail;
            empty = false;
        } else {
            tail->next = L->head;
            L->head->prev = tail;
            tail = L->tail;
        }
        L = new linked_list();
    }
    string print() {
        string ret;
        if(empty) ret += "empty ";
        else for(item* i = head;i != nullptr;i = i->next) ret += to_string(i->value) + " ";
        return ret.substr(0 ,ret.size() - 1);
    }
} *L[300];

int main() {
    int N ,Q;
    int i ,a ,b;
    string cmd;
    while(cin >> N >> Q) {
        for(i = 1;i <= N;i++) L[i] = new linked_list();
        while(Q--) {
            cin >> cmd;
            if(cmd == "ADD") {
                cin >> a >> b;
                L[a]->push_back(b);
            } else if(cmd == "LEAVE") {
                cin >> a;
                if(L[a]->pop_front()) cout << "queue " << a << " is empty!" << endl;
            } else {
                cin >> a >> b;
                L[b]->merge(L[a]);
            }
        }
        for(i = 1;i <= N;i++) cout << "queue " << i << ": " << L[i]->print() << endl;
    }
}
