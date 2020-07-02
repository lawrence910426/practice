#pragma GCC optimize("Ofast")

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;
const int MAXN = 3e5 + 5;
long long RA[MAXN], SA[MAXN], feed[MAXN], N;
string s;

pair<long long, long long> temp[MAXN];
void sort_index() {
    int i, order;
    for(i = 0;i < N;i++) temp[i] = {feed[i], i};
    sort(temp, temp + N);
    for(order = i = 0;i < N;i++) {
        RA[temp[i].second] = order;
        if(i != N - 1) order += (temp[i].first == temp[i + 1].first ? 0 : 1);
    }
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); getline(cin, s);
    for(char c = getchar_unlocked();c != '\n';c = getchar_unlocked()) s += c;
    s += s; N = s.size();
    int i, L;
    for(i = 0;i < N;i++) feed[i] = s[i];
    sort_index();
    for(L = 1;L < N;L <<= 1) {
        for(i = 0;i < N;i++) feed[i] = RA[i] * MAXN + (i + L < N ? RA[i + L] + 1 : 0);
        sort_index();
    }
    for(i = 0;i < N;i++) SA[RA[i]] = i;
    for(i = 0;i < N;i++) if(SA[i] < N / 2) cout << s[SA[i] + N / 2 - 1];
}
