#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

const int MAXN = 1e2 + 50;

class Node {
public:
    Node *l, *r; int val;
    Node(int v): val(v), l(nullptr), r(nullptr) {}
    static void Preorder(Node* pos) {
        if(pos == nullptr) return;
        cout << pos->val << " ";
        Preorder(pos->l);
        Preorder(pos->r);
    }
} *Root;

int inorder[MAXN], postorder[MAXN], cases = 0;
int main() {
    int N;
    int i;
    while(cin >> N) {
        for(i = 0;i < N;i++) cin >> inorder[i];
        for(i = 0;i < N;i++) cin >> postorder[i];
        unordered_map<int, int> inv;
        map<int, Node*> near;
        for(i = 0;i < N;i++) inv[inorder[i]] = i;
        for(i = N - 1;i >= 0;i--) {
            int pos = inv[postorder[i]];
            Node* item = new Node(postorder[i]);
            if(i == N - 1) {
                Root = item;
            } else {
                auto it = near.lower_bound(pos);
                if(it == near.end()) {
                    it = prev(it);
                    it->second->r = item;
                } else if(it == near.begin() && pos < it->first) {
                    it->second->l = item;
                } else {
                    if(it->second->l == nullptr) it->second->l = item;
                    else {
                        it = prev(it);
                        it->second->r = item;
                    }
                }
            }
            near[pos] = item;
        }
        cout << "testcase" << ++cases << ": "; Node::Preorder(Root); cout << endl;
        for(auto p : near) delete p.second;
    }
}
