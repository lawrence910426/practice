#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> basic, extend;
vector<pair<int ,int> > mq;

bool cmp(pair<int ,int> a, pair<int ,int> b) {
    return a.second > b.second;
}

int main()
{
    int N;
    int i ,eax;
    long long int ans;
    vector<pair<int ,int> >::iterator it;
    while(cin >> N) {
        basic = vector<int>() ,extend = vector<int>();
        mq = vector<pair<int ,int> >();
        for(i = 0;i < N;i++) cin >> eax ,basic.push_back(eax);
        for(i = 0;i < N;i++) cin >> eax ,extend.push_back(eax);

        ans = 0;
        mq.push_back(pair<int ,int>(-1 ,(1LL << 31) - 1));
        for(i = 0;i < basic.size();i++) {
            it = lower_bound(mq.begin() ,mq.end() ,pair<int ,int>(-1 ,basic[i] + extend[i]) ,cmp);

            if(it != mq.end()) {
                while(it->second <= basic[i] + extend[i]) it--;
                ans += i - it->first - 1;

                //for(eax = 0;eax < mq.size();eax++) printf("%d %d\n" ,mq[eax].first ,mq[eax].second);
                //printf("show: %d %d %d\n" ,it->first ,it->second ,i);
            }

            it = lower_bound(mq.begin() ,mq.end() ,pair<int ,int>(-1 ,basic[i]) ,cmp);
            mq.erase(it ,mq.end());
            mq.push_back(pair<int ,int>(i ,basic[i]));
        }
        cout << ans << endl;
    }
}

/*
8
1 2 2 3 4 4 3 1
0 0 0 0 0 0 0 0

5
5 4 1 1 3
0 0 4 0 1
*/

/*
passed the example testing data.
*/
