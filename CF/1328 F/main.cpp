///#pragma GCC optimize("Ofast")

#include <iostream>
#include <map>
using namespace std;
int N ,K ,mini ,maxi ,smini ,smaxi;
map<int ,int> counter;
long long cost = 0;

bool small() {
    if(counter[mini] + counter[smini] > K) {
        cost += (smini - mini) * (K - counter[mini]);
        return true;
    } else {
        cost += (smini - mini) * counter[mini];
        counter[smini] += counter[mini];
        counter.erase(mini);
        return false;
    }
}

bool big() {
    if(counter[maxi] + counter[smaxi] > K) {
        cost += (maxi - smaxi) * (K - counter[maxi]);
        return true;
    } else {
        cost += (maxi - smaxi) * counter[maxi];
        counter[smaxi] += counter[maxi];
        counter.erase(maxi);
        return false;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cin >> N >> K;
    int i ,temp;
    for(i = 0;i < N;i++) { cin >> temp; counter[temp] = counter[temp] + 1; }
    while(true) {
        mini = counter.begin()->first ,smini = (++counter.begin())->first;
        maxi = counter.rbegin()->first ,smaxi = (++counter.rbegin())->first;
        if(smini - mini < maxi - smaxi)
            if(small()) break;
        if(smini - mini > maxi - smaxi)
            if(big()) break;
        if(smini - mini == maxi - smaxi) {
            if(counter[smini] < counter[smaxi])
                { if(big()) break; }
            else
                { if(small()) break; }
        }
    }
    cout << cost << endl;
}
