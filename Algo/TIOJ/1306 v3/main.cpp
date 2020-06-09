#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <memory.h>
using namespace std;
const int WORDS = 26 ,MAXN = 3.5e5 ,root = 0 ,MAXR = 1e5;
struct trie {
    int parent ,kids[WORDS] ,fail;
    vector<int> emit;
    trie() {
        fail = parent = root;
        for(int i = 0;i < WORDS;i++) kids[i] = -1;
    }
    trie(int p ,int c):parent(p) {
        fail = root;
        for(int i = 0;i < WORDS;i++) kids[i] = -1;
    }
} graph[MAXN];
int used;
void insert(string& s ,int code) {
    int ptr = root;
    for(char c : s) {
        if(graph[ptr].kids[c - 'a'] == -1) {
            graph[ptr].kids[c - 'a'] = used;
            graph[used++] = trie(ptr ,c - 'a');
            if(used == MAXN) throw;
        }
        ptr = graph[ptr].kids[c - 'a'];
    }
    graph[ptr].emit.push_back(code);
}
void init() {
    int i ,U ,V ,F;
    queue<int> Q;
    for(i = 0;i < WORDS;i++) {
        U = graph[root].kids[i];
        if(U == -1) continue;
        Q.push(U);
        graph[U].fail = root;
    }
    for(;!Q.empty();Q.pop()) {
        U = Q.front();
        for(i = 0;i < WORDS;i++) {
            V = graph[U].kids[i];
            if(V == -1) continue;
            F = graph[U].fail;
            while(graph[F].kids[i] == -1 && F != root) F = graph[F].fail;
            if(graph[F].kids[i] != -1) F = graph[F].kids[i];
            graph[V].fail = F;
            for(int item : graph[F].emit) graph[V].emit.push_back(item);
            Q.push(V);
        }
    }
}
int result[MAXR];
void exec(string &s) {
    memset(result ,0 ,sizeof(result));
    int ptr = root;
    for(char c : s) {
        while(ptr != root && graph[ptr].kids[c - 'a'] == -1) ptr = graph[ptr].fail;
        if(graph[ptr].kids[c - 'a'] != -1) ptr = graph[ptr].kids[c - 'a'];
        for(int item : graph[ptr].emit) result[item] += 1;
    }
}
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0);
    string A ,B;
    int T ,N ,i;
    for(cin >> T;T--;) {
        used = 1;
        graph[root] = trie();
        cin >> A >> N;
        for(i = 0;i < N;i++) {
            cin >> B;
            try { insert(B ,i); } catch(exception e) { return -1; }
        }
        init() ,exec(A);
        for(i = 0;i < N;i++) cout << result[i] << '\n';
    }
}
