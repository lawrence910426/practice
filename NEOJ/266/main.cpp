#include <iostream>
#include <map>
#include <cstring>
using namespace std;

struct trie {
    map<char ,trie*> kids;
    char value;
    int sum;
    trie(char c): value(c) ,sum(0) {}
};

void insert(trie *t ,string& s) {
    for(int i = 0;i < s.size();i++) {
        if(t->kids.find(s[i]) == t->kids.end()) t = t->kids[s[i]] = new trie(s[i]);
        else t = t->kids[s[i]];
    }
    t->sum += 1;
}

int count(trie* t ,string& s) {
    for(int i = 0;i < s.size();i++) {
        if(t->kids.find(s[i]) == t->kids.end()) return 0;
        else t = t->kids[s[i]];
    }
    return t->sum;
}

int main() {
    int N ,Q;
    trie *root;
    string s;
    while(cin >> N >> Q) {
        root = new trie('\0');
        while(N--) {
            cin >> s;
            insert(root ,s);
        }
        while(Q--) {
            cin >> s;
            cout << count(root ,s) << endl;
        }
    }
}
