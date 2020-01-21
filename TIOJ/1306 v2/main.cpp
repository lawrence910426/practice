#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;
const int WORDS = 26;
struct node {
    node *fail ,*kids[WORDS] ,*parent;
    int color;
    vector<int> emit;
    node() {
        parent = fail = nullptr;
        emit = vector<int>();
        for(int i = 0;i < WORDS;i++) kids[i] = nullptr;
        color = 0;
    }
    node(node* p ,int c): parent(p) ,color(c) {
        fail = nullptr;
        emit = vector<int>();
        for(int i = 0;i < WORDS;i++) kids[i] = nullptr;
    }
} *root;
void release(node* V) {
    if(V == nullptr) return;
    for(auto ptr : V->kids) release(ptr);
    delete(V);
}
void insert(node* V ,string& s ,int code) {
    for(char c : s) {
        if(V->kids[c - 'a'] == nullptr) V->kids[c - 'a'] = new node(V ,c - 'a');
        V = V->kids[c - 'a'];
    }
    V->emit.push_back(code);
}
void init() {
    int i;
    queue<node*> Q;
    root->fail = root;
    for(i = 0;i < WORDS;i++) if(root->kids[i] != nullptr) {
        Q.push(root->kids[i]);
        root->kids[i]->fail = root;
    }
    for(;!Q.empty();Q.pop()) {
        node *U = Q.front();
        for(auto V : U->kids) if(V != nullptr) {
            node *F = U->fail;
            while(F != root && F->kids[V->color] == nullptr) F = F->fail;
            if(F->kids[V->color] == nullptr) F = root;
            else F = F->kids[V->color];
            V->fail = F;
            for(int e : F->emit) V->emit.push_back(e);
            Q.push(V);
        }
    }
}
map<int ,int> result;
void execute(string& s ,node* V) {
    result = map<int ,int>();
    for(char c : s) {
        while(V != root && V->kids[c - 'a'] == nullptr) V = V->fail;
        if(V->kids[c - 'a'] != nullptr) V = V->kids[c - 'a'];
        for(int emit : V->emit) result[emit] = result[emit] + 1;
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    int T ,N ,i;
    string A ,B;
    for(cin >> T;T--;) {
        cin >> A;
        cin >> N;
        root = new node();
        for(i = 0;i < N;i++) {
            cin >> B;
            insert(root ,B ,i);
        }
        init();
        execute(A ,root);
        for(i = 0;i < N;i++) cout << result[i] << '\n';
        release(root);
    }
}
