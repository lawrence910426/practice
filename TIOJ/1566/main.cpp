#include <iostream>
#include <deque>
#include <vector>

using namespace std;
long long N ,M ,K;
struct status { long long value ,index; };
int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    long long i ,value ,ans;
    while(cin >> N >> M >> K) {
        vector<pair<long long ,long long> > answer;
        deque<status> maxi ,mini;
        for(i = 0;i < N + M;i++) {
            if(i < N) {
                cin >> value;
                while(!maxi.empty() && maxi.rbegin()->value <= value) maxi.pop_back();
                while(!mini.empty() && mini.rbegin()->value >= value) mini.pop_back();
                maxi.push_back(status{value ,i});
                mini.push_back(status{value ,i});
            }
            while(!maxi.empty() && maxi.begin()->index <= i - M) maxi.pop_front();
            while(!mini.empty() && mini.begin()->index <= i - M) mini.pop_front();
            if(i != 0 && i != N + M - 1) {
                if(maxi.begin()->value - mini.begin()->value == K)
                    answer.push_back(pair<long long ,long long>(max(1LL ,i - M + 2LL) ,min(i + 1LL ,N)));
            }
        }
        cout << answer.size() << endl;
        for(auto p : answer) cout << p.first << " " << p.second << '\n';
    }
}
