#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;
#define NN 200005
struct node {
    int capacity ,amount ,digit;
}data[NN];
int N ,M;

int best(int on ,int raw) {
    if(on > NN) return -1;


}

int get_max(int on) {

}

int main() {
    int i ,j ,tmp;
    while(cin >> N >> M) {
        memset(data ,0 ,sizeof(data));
        for(i = 0;i < N;i++) {
            cin >> tmp;
            data[tmp].capacity = data[tmp].amount = data[tmp].capacity + 1;
        }
        i = 1 ,j = 0;
        while(i < NN) {
            data[i].digit = j;
            i <<= 1 ,j += 1;
        }
        for(i = 0;i < NN;i++) if()
    }
}
