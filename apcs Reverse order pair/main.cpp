#include <iostream>
#include <memory.h>
using namespace std;
long long int N ,data[1000000] ,tmp[1000000] ,ans;

void merge_sort(int l, int r) {
    if(r == l + 1) {
        return;
    }

    #define center ((l + r) / 2)
    merge_sort(l ,center);
    merge_sort(center ,r);
    int lptr = l, rptr = center ,ptr = l;
    while(lptr < center && rptr < r && ptr < r) {
        if(data[lptr] <= data[rptr]) {
            tmp[ptr] = data[lptr];
            lptr += 1;
        } else {
            tmp[ptr] = data[rptr];
            rptr += 1;
            ans += center - lptr;
        }
        ptr += 1;
    }
    while(lptr < center && ptr < r) {
        tmp[ptr] = data[lptr];
        lptr += 1;
        ptr += 1;
    }
    while(rptr < r && ptr < r) {
        tmp[ptr] = data[rptr];
        rptr += 1;
        ptr += 1;
    }

    for(ptr = l;ptr < r;ptr++) data[ptr] = tmp[ptr];
}

int main() {
    int i;
    while(cin >> N ,N) {
        for(i = 0;i < N;i++) cin >> data[i];
        ans = 0;

        merge_sort(0 ,N);
        //for(i = 0;i < N;i++) cout << data[i] << endl;
        printf("%lld\n" ,ans);
    }
}
