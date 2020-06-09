#include <iostream>
#include <stack>
#include <set>
#include <queue>
using namespace std;

set<int> se1 ,se2 ,seQ;
stack<int> st1 ,st2;
queue<int> Q;
void solve(int N, int order[]){
    int i;
    for(i = 1;i <= N;i++) Q.push(i) ,seQ.insert(i);
    for(i = 0;i < N;i++) {
        if(seQ.find(order[i]) != seQ.end()) {
            while(Q.front() != order[i]) {
                se1.insert(Q.front()) ,st1.push(Q.front());
                seQ.erase(Q.front()) ,Q.pop();
                push_train();
            }
            seQ.erase(Q.front()) ,Q.pop();
            push_train() ,move_station_1_to_2() ,pop_train();
        } else if(se1.find(order[i]) != se1.end()) {
            while(st1.top() != order[i]) {
                se2.insert(st1.top()) ,st2.push(st1.top());
                se1.erase(st1.top()) ,st1.pop();
                move_station_1_to_2();
            }
            se1.erase(st1.top()) ,st1.pop();
            move_station_1_to_2() ,pop_train();
        } else if(se2.find(order[i]) != se2.end()) {
            while(st2.top() != order[i]) {
                se1.insert(st2.top()) ,st1.push(st2.top());
                se2.erase(st2.top()) ,st2.pop();
                move_station_2_to_1();
            }
            se2.erase(st2.top()) ,st2.pop();
            pop_train();
        }
    }
}
