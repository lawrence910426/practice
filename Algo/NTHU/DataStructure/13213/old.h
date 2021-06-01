#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <cstdlib>
#include <stddef.h>
#include <iostream>

using namespace std;

// TODO: Implement the sorting algorithm
const int MAXN = 2e5 + 50;
struct pii { 
    int val, idx; 
    bool operator < (pii b) const { return val < b.val; }
    bool operator <= (pii b) const { return val <= b.val; }
} gems[MAXN];
int count[MAXN][2];

void mysort(pii* arr, int l, int r) {
    if(l >= r - 1) return;
    int pivot = (l + r) / 2, center = l;
    int i, j;

    for(i = l;i < r;i++) if(arr[i] < arr[pivot]) center += 1;
    swap(arr[pivot], arr[center]);

    i = l;
    j = center;
    while(i < center && j < r) {
        if(arr[center] <= arr[i] && arr[j] < arr[center]) {
            swap(arr[i], arr[j]);
            i += 1;
            j += 1;
        } else {
            if(arr[center] <= arr[i]) j += 1;
            else i += 1;
        }
    }

    mysort(arr, l, center);
    mysort(arr, center + 1, r);
}

void solve() {
    long long N, L, R, C, ans = 0, x[2][2] = { {0, 0}, {0, 0} }, M = 0;
    cin >> N >> L >> R >> C;
    for(int i = 0;i < N;i++) {
        cin >> gems[i].val;
        gems[i].idx = i;
    }
    mysort(gems, 0, N);
    for(int i = 0;i < N;i++) count[i][0] = count[i][1] = 0;
    for(int i = 0;i < N;i++) count[i + 1 < N && gems[i].val == gems[i + 1].val ? M : M++][gems[i].idx < L ? 0 : 1] += 1;
    for(int i = 0;i < M;i++) {
        count[i][0] -= min(count[i][0], count[i][1]);
        count[i][1] -= min(count[i][0], count[i][1]);
    }
    for(int i = 0;i < M;i++) for(int j = 0;j < 2;j++) {
        x[j][0] += count[i][j] - count[i][j] / 2LL * 2LL;
        x[j][1] += count[i][j];
    }

    if(x[0][1] < x[1][1]) swap(x[0], x[1]);
    if(x[0][0] > x[1][1]) ans = x[0][0] + (x[0][1] - x[0][0]) / 2;
    else ans = (x[0][1] + x[1][1]) / 2;

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
