#include <iostream>

using namespace std;
const int MAXN = 1e5 + 10;

/* --------------------------------------------- */
struct treap {
    treap *l ,*r;
    int pri ,key ,sum;
};
/* --------------------------------------------- */


/* --------------------------------------------- */
vector<int> G[MAXN];
struct node {
    int maxson;
    vector<int> kids;
};
/* --------------------------------------------- */

int main() {

}
