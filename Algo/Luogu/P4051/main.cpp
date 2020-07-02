#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 50;

int SA[MAXN];
long long feed[MAXN], RA[MAXN], N;
string s;

pair<int, int> temp[MAXN];
void sort_index(long long *value, long long *ranking) {
    int i, order = 0;
    for(i = 0;i < N;i++) temp[i] = {value[i], i};
    sort(temp, temp + N);
    for(i = 0;i < N;i++) {
        ranking[temp[i].second] = order;
        if(i != N - 1) order += (temp[i].first == temp[i + 1].first ? 0 : 1);
    }
}

int main() {
    getline(cin, s); s += s; N = s.size();
    int i, L;
    for(i = 0;i < N;i++) feed[i] = s[i];
    sort_index(feed, RA);
    for(L = 1;L < N;L <<= 1) {
        for(i = 0;i < N;i++) feed[i] = RA[i] * N + (i + L < N ? RA[i + L] : 0);
        sort_index(feed, RA);
    }
    for(i = 0;i < N;i++) SA[RA[i]] = i;
    for(i = 0;i < N;i++) if(SA[i] < N / 2) cout << s[SA[i] + N / 2 - 1];
    cout << endl;
    /* for(i = 0;i < N;i++) cout << i << " " << RA[i] << endl;
    for(i = 0;i < N;i++) {
        for(int j = SA[i];j < N;j++) cout << s[j];
        cout << endl;
    } */
}
