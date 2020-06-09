#include <iostream>
#include <bitset>
using namespace std;
const int SIZ = (1LL << 8) ,MAXN = 3e5 + 50 ,MAXM = 10;
struct trie { trie *l ,*r; bool exist; } root;
int N ,M;
int data[MAXN][MAXM];
void release(trie *root) {
    if(root == nullptr) return;
    release(root->l) ,release(root->r);
    delete root;
}
trie* build(int depth) {
    trie* ans = new trie();
    if(--depth) {
        ans->l = build(depth);
        ans->r = build(depth);
    }
    ans->exist = false;
    return ans;
}
void addition(int N ,int depth ,trie* root) {
    if(root->l == nullptr) {
        root->exist = true;
    } else {
        if(N & (1LL << depth)) addition(N ,depth + 1 ,root->l);
        else addition(N ,depth + 1 ,root->r);
    }
}
bool exist(int N ,int depth ,trie *root) {
    if(root->l == nullptr) return exist;
    if(N & (1LL << depth)) return exist(N ,depth + 1 ,root->l) || exist(N ,depth + 1 ,root->r);
    else return exist(N ,depth + 1 ,root->l);
}
int main() {
    int i ,j;
    int L ,R ,M ,value;
    bool able;
    while(cin >> N >> M) {
        for(i = 0;i < N;i++) for(j = 0;j < M;j++) cin >> data[i][j];
        root = build(M);
        while(L != R - 1) {
            M = (L + R) / 2;
            able = false;
            for(i = 0;i < N;i++) {
                for(value = j = 0;j < M;j++) value |= (data[i][j] >= M ? 1 : 0) << j;
                addition(value ,0 ,root);
                able |= exist(value ,0 ,root);
            }

        }
        release(root);
    }
}
