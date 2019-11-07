#include <iostream>

using namespace std;
struct seg {
    int L ,R ,value;
    seg() {}
    seg(int l ,int r ,int v): L(l) ,R(r) ,value(v) {}
};
struct zkw {
    int sum;
    seg pos ,neg;
};
int main() {
    cout << "Hello world!" << endl;
    return 0;
}
