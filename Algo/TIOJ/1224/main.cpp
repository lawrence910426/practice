#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct Segment {
    long long int l ,r ,u ,d ,xc ,yc ,kid_style;
    bool draw ,leaf;
    Segment *kids[4];
};
vector<int> kid_list[3];

Segment* build(int l ,int r ,int u , int d) {
    if(l == r && u == d) return nullptr;
    Segment* root = new Segment();
    root->l = l ,root->r = r ,root->u = u ,root->d = d;
    root->kids[0] = root->kids[1] = root->kids[2] = root->kids[3] = nullptr;
    root->xc = (l + r) / 2, root->yc = (u + d) / 2;
    if(root->l + 1 != root->r && root->u + 1 != root->d) root->kid_style = 0;
    if(root->l + 1 == root->r && root->u + 1 != root->d) root->kid_style = 1;
    if(root->l + 1 != root->r && root->u + 1 == root->d) root->kid_style = 2;
    root->draw = false, root->leaf = (root->l + 1 == root->r && root->u + 1 == root->d);
    return root;
}

void draw(Segment* root ,int l ,int r ,int u ,int d) {
    assert(root != nullptr);
    if(r <= root->l || root->r <= l || d <= root->u || root->d <= u) return;
    if(l <= root->l && root->r <= r && u <= root->u && root->d <= d) {
        root->draw = true;
        return;
    }
    if(root->kids[0] == nullptr && !root->leaf)
        for(int k : kid_list[root->kid_style]) {
            int xc = (root->xc == root->l ? root->r : root->xc);
            int yc = (root->yc == root->u ? root->d : root->yc);
            if(k == 0) root->kids[0] = build(root->l ,xc ,root->u ,yc);
            if(k == 1) root->kids[1] = build(root->l ,xc ,yc ,root->d);
            if(k == 2) root->kids[2] = build(xc ,root->r ,root->u ,yc);
            if(k == 3) root->kids[3] = build(xc ,root->r ,yc ,root->d);
        }
    for(int k : kid_list[root->kid_style]) draw(root->kids[k] ,l ,r ,u ,d);

    bool all_draw = true;
    for(int k : kid_list[root->kid_style]) all_draw &= root->kids[k]->draw;
    root->draw |= all_draw;
}

long long int get_area(Segment* root) {
    long long int ret = 0;
    if(root->draw) ret = (root->r - root->l) * (root->d - root->u);
    else for(int k : kid_list[root->kid_style]) if(root->kids[k] != nullptr) ret += get_area(root->kids[k]);
    return ret;
}

int main()
{
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    kid_list[0] = vector<int>{0 ,1, 2 ,3};
    kid_list[1] = vector<int>{0 ,1};
    kid_list[2] = vector<int>{0 ,2};
    int N ,l ,r ,u, d;
    Segment* root = build(0 ,1 << 24 ,0 ,1 << 24);
    for(cin >> N;N--;) {
        cin >> l >> r >> u >> d;
        draw(root ,l ,r ,u ,d);
    }
    cout << get_area(root) << endl;
}
/*
1
1 1000000 1 1000000
*/
