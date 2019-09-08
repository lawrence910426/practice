#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

set<string> possible;
set<char> leftover;

void remove_permu(string s) {
    if(s[0] != s[1]) {
        leftover = set<char>();
        leftover.insert('a') ,leftover.insert('b') ,leftover.insert('c');
        leftover.erase(s[0]) ,leftover.erase(s[1]);
        possible.erase(*leftover.begin() + s);
        possible.erase(s + *leftover.begin());
        string tmp = "";
        tmp = (tmp + s[1] + *leftover.begin() + s[0]);
        possible.erase(tmp);
    }
}

int main() {
    string a ,b;
    int N;
    int i;
    string str;

    while(cin >> N) {
        cin >> a >> b;
        str = "abc";
        possible = set<string>();
        do {
            possible.insert(str);
        } while(next_permutation(str.begin() ,str.end()));
        remove_permu(a) ,remove_permu(b);
        cout << "YES" << endl;
        for(i = 0;i < N;i++) cout << *possible.begin();
        cout << endl;
    }
}
