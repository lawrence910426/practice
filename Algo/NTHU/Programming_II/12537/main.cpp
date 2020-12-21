#pragma GCC optimize("Ofast")

#include <iostream>
#include <cstring>
#include <stack>
#include <vector>

#define endl '\n'
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int Q, x;
    string command;
    vector<int> storage;
    stack<pair<int, int> > mini, maxi;

    for(cin >> Q;Q--;) {
        cin >> command;
        if(command == "push_back") {
            cin >> x;
            storage.push_back(x);
            if(mini.empty() || mini.top().first > x) mini.push({x, storage.size()});
            if(maxi.empty() || maxi.top().first <= x) maxi.push({x, storage.size()});
        } else if(command == "pop_back") {
            if(!storage.empty()) storage.pop_back();
            while(!mini.empty() && mini.top().second > storage.size()) mini.pop();
            while(!maxi.empty() && maxi.top().second > storage.size()) maxi.pop();
        } else if(command == "find") {
            cin >> x;
            if(x <= storage.size()) cout << storage[x - 1] << endl;
        } else if(command == "min") { 
            if(!mini.empty()) cout << mini.top().first << " " << mini.top().second << endl;
        } else if(command == "max") {
            if(!maxi.empty()) cout << maxi.top().first << " " << maxi.top().second << endl;
        }
    }
}
