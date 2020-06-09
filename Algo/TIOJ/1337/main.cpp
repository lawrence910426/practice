#include <iostream>
#include <set>

const int MAXRANGE = 1e9+10;
const int MAXNODE = 1e6+10;
const int MAXN = 1e5+10;
using namespace std;
struct seg {
    int l ,r;
    int value ,tag;
    seg *left ,*right ,*parent;
}data[MAXNODE];
int nodes;
pair<int ,int> ranges[MAXN];

void build(seg* father) {
    if(father->l == father->r - 1) return;
    seg *L = &data[nodes++] ,*R = &data[nodes++];
    L->tag = R->tag = L->value = R->value = 0;
    L->left = L->right = R->left = R->right = nullptr;
    L->l = father->l ,L->r = R->l = (father->l + father->r) >> 1 ,R->r = father->r;
    father->left = L ,father->right = R;
    L->parent = R->parent = father;
}

int L ,R;
void modify(seg* on ,bool more ,int code) {
    if(R <= on->l || on->r <= L) return;
    if(L <= on->l && on->r <= R) {
        on->tag += (more ? 1 : -1);
    } else {
        if(on->left == nullptr) build(on);
        modify(on->left ,more ,code);
        modify(on->right ,more ,code);
    }

    if(on->left == nullptr) {
        on->value = on->tag;
    } else {
        on->value = max(on->left->value ,on->right->value);
        on->value += on->tag;
    }
}

seg* query(seg* on) {
    if(on->left == nullptr) return on;
    if(on->left->value < on->right->value) return query(on->right);
    else return query(on->left);
}

int main() {
    int N ,K ,code ,top;
    int i ,j;
    seg *root ,*ans;
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    while(cin >> N >> K) {
        root = &data[0];
        root->left = root->right = nullptr;
        root->l = -MAXRANGE ,root->r = MAXRANGE;
        root->value = root->tag = 0;
        root->parent = root;
        nodes = 1;

        for(i = 0;i < N;i++) {
            cin >> L >> R;
            ranges[i].first = L ,ranges[i].second = R;
            modify(root ,true ,i);
        }
        for(i = 0;i < K;i++) {
            ans = query(root);
            top = ans->l;
            code = -1;
            for(j = 0;j < N;j++) if(ranges[j].first <= top && top < ranges[j].second)
                if(code == -1 || ranges[code].second - ranges[code].first < ranges[j].first - ranges[j].second)
                    code = j;
            L = ranges[code].first ,R = ranges[code].second;
            modify(root ,false ,code);
        }
        cout << root->value << endl;
    }
}
