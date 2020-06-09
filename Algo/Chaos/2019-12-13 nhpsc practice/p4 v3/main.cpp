#include <iostream>
#include <vector>
#include <memory.h>
#include <bitset>
using namespace std;
const int MAXN = 1000 + 5;
int match[MAXN] ,M ,N ,L ,;
bitset<MAXN> visit;
vector<int> G[MAXN];
int hungarian(int on) {

}
int M ,N ,K ,L;
int main() {
    int src ,dst ,val;
    while(cin >> M >> N >> K >> L) {
        while(K--) {
            cin >> src >> dst >> val;
            if(val == 1) {
                match[src] = dst;
                match[dst] = src;
            }

        }
    }
}
