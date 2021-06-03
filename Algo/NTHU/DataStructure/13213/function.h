#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <cstdlib>
#include <stddef.h>
#include <iostream>
#include <memory.h>

using namespace std;

// TODO: Implement the sorting algorithm
const int MAXN = 2e5 + 50;
struct { int val, idx; } gem[MAXN], temp[MAXN];
int count[MAXN][2], x[2][2];

void msort(int l, int r) {
    if(l == r - 1) return;
    int mid = (l + r) / 2;
    msort(l, mid);
    msort(mid, r);
    
    int lptr = l, rptr = mid, ptr = l;
    while(lptr < mid && rptr < r && ptr < r) {
        if(gem[lptr].val < gem[rptr].val) temp[ptr++] = gem[lptr++];
        else temp[ptr++] = gem[rptr++];
    }
    while(rptr < r) temp[ptr++] = gem[rptr++];
    while(lptr < mid) temp[ptr++] = gem[lptr++];

    for(ptr = l;ptr < r;ptr++) gem[ptr] = temp[ptr];
}

void solve() {
    long long N, L, R, C, ans, M = 0, temp;

    cin >> N >> L >> R >> C;
    memset(count, 0, sizeof(count));
    memset(x, 0, sizeof(x));

    for(int i = 0;i < N;i++) {
        cin >> gem[i].val;
        gem[i].idx = i;
    }

    msort(0, N);
    for(int i = 0;i < N;i++) count[i + 1 < N && gem[i].val == gem[i + 1].val ? M : M++][gem[i].idx >= L ? 1 : 0] += 1;
    for(int i = 0;i < M;i++) {
        temp = min(count[i][0], count[i][1]);
        count[i][0] -= temp;
        count[i][1] -= temp;
    }
    for(int i = 0;i < M;i++) for(int j = 0;j < 2;j++) {
        x[j][0] += count[i][j] - count[i][j] / 2 * 2;
        x[j][1] += count[i][j] / 2 * 2;
    }
    // cout << x[0][0] << " " << x[0][1] << endl << x[1][0] << " " << x[1][1] << endl;
    
    ans = temp = min(x[0][0], x[1][0]);
    x[0][0] -= temp;
    x[1][0] -= temp;

    ans += min(x[0][1], x[1][0]) + min(x[0][0], x[1][1]);
    temp = min(x[0][1], x[1][0]);
    x[0][1] -= temp;
    x[1][0] -= temp;
    temp = min(x[0][0], x[1][1]);
    x[0][0] -= temp;
    x[1][1] -= temp;

    ans += x[0][0] + x[1][0] + (x[0][1] + x[1][1]) / 2;

    cout << ans * C << endl;
}


// The codes bellow prevent you from using bulit-in sorting function and from importing C++ containers.
// Nothing needed to be implemented below.
// Do not modify the codes below.

void qsort(void* , std::size_t , std::size_t , void*);

template <class RandomAccessIterator> 
void sort (RandomAccessIterator , RandomAccessIterator );

template <class RandomAccessIterator, class Compare> 
void sort (RandomAccessIterator , RandomAccessIterator , Compare );

#endif
#ifndef vector
#define vector
#endif
#ifndef list
#define list
#endif
#ifndef forward_list
#define forward_list
#endif
#ifndef deque
#define deque
#endif
#ifndef array
#define array
#endif
#ifndef set
#define set
#endif
#ifndef multiset
#define multiset
#endif
#ifndef map
#define map
#endif
#ifndef multimap
#define multimap
#endif
#ifndef unordered_set
#define unordered_set
#endif
#ifndef unordered_multiset
#define unordered_multiset
#endif
#ifndef unordered_map
#define unordered_map
#endif
#ifndef unordered_multimap
#define unordered_multimap
#endif
#ifndef bitset
#define bitset
#endif
#ifndef valarray
#define valarray
#endif
#ifndef stack
#define stack
#endif
#ifndef queue
#define queue
#endif
#ifndef priority_queue
#define priority_queue
#endif
