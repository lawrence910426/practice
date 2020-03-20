#pragma GCC optimize("Ofast")

#include <iostream>
#include <deque>
#include <vector>

using namespace std;
const int MAXN = 1005;
int A ,B ,N ,ans;
int raw[MAXN][MAXN] ,maxi[MAXN][MAXN] ,mini[MAXN][MAXN];
deque<pair<int ,int> > maximum ,minimum;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int i ,j;
    while(cin >> A >> B >> N) {
        for(i = 0;i < A;i++) for(j = 0;j < B;j++) cin >> raw[i][j];
        for(i = 0;i < A;i++) {
            maximum = deque<pair<int ,int> >(); minimum = deque<pair<int ,int> >();
            for(j = 0;j < B;j++) {
                while(!maximum.empty() && maximum.front().first <= j - N) maximum.pop_front();
                while(!maximum.empty() && maximum.back().second < raw[i][j]) maximum.pop_back();
                maximum.push_back({j ,raw[i][j]});

                while(!minimum.empty() && minimum.front().first <= j - N) minimum.pop_front();
                while(!minimum.empty() && minimum.back().second > raw[i][j]) minimum.pop_back();
                minimum.push_back({j ,raw[i][j]});

                maxi[i][j] = maximum.front().second; mini[i][j] = minimum.front().second;
            }
        }
        ans = (1LL << 31) - 1;
        for(j = N - 1;j < B;j++) {
            maximum = deque<pair<int ,int> >(); minimum = deque<pair<int ,int> >();
            for(i = 0;i < A;i++) {
                while(!maximum.empty() && maximum.front().first <= i - N) maximum.pop_front();
                while(!maximum.empty() && maximum.back().second < maxi[i][j]) maximum.pop_back();
                maximum.push_back({i ,maxi[i][j]});

                while(!minimum.empty() && minimum.front().first <= i - N) minimum.pop_front();
                while(!minimum.empty() && minimum.back().second > mini[i][j]) minimum.pop_back();
                minimum.push_back({i ,mini[i][j]});

                if(i >= N - 1) ans = min(maximum.front().second - minimum.front().second ,ans);
            }
        }
        cout << ans << '\n';
    }
}
