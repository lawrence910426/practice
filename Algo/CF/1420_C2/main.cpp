#pragma GCC optimize("Ofast")

#include <iostream>
#include <map>

using namespace std;

const int MAXN = 3e5 + 50;
long long A[MAXN];
int N;

class Concave {
    long long get_concavity(int i) {
        if(i == 0) {
            return A[i] > A[i + 1] ? 1 : -1;   
        } else if(i == N - 1) {
            return A[i] > A[i - 1] ? 1 : -1;
        } else {
            if(A[i] > A[i - 1] && A[i] > A[i + 1]) return 1;
            else if(A[i] < A[i - 1] && A[i] < A[i + 1]) return -1;
            else return 0;
        }
    }

    map<int, long long> storage;
public:
    long long sum = 0;
    Concave() {
        sum = 0;
        for(int i = 0;i < N;i++) {
            storage[i] = get_concavity(i) * A[i];
            sum += storage[i];
        }
        Normalize();
    }

    void Normalize() {
        if(storage.begin()->second < 0) {
            sum -= storage.begin()->second;
            storage.erase(storage.begin()->first);
        }
        if(storage.rbegin()->second < 0) {
            sum -= storage.rbegin()->second;
            storage.erase(storage.rbegin()->first);
        }
    }

    void Modify(int pos, long long value) {
        A[pos] = value;

        long long temp = get_concavity(pos) * A[pos];
        sum += temp - storage[pos];
        storage[pos] = temp;

        if(pos != 0) {
            temp = get_concavity(pos - 1) * A[pos - 1];
            sum += temp - storage[pos - 1];
            storage[pos - 1] = temp;
        }

        if(pos != N - 1) {
            temp = get_concavity(pos + 1) * A[pos + 1];
            sum += temp - storage[pos + 1];
            storage[pos + 1] = temp;
        } 
    }
};

struct { int l, r; } oper[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T, Q;
    int i;
    for(cin >> T;T--;) {
        cin >> N >> Q;
        for(i = 0;i < N;i++) cin >> A[i];
        for(i = 0;i < Q;i++) {
            cin >> oper[i].l >> oper[i].r;
            oper[i].l -= 1;
            oper[i].r -= 1;
        }
        
        if(N == 1) {
            cout << A[0] << '\n';
            while(Q--) cout << A[0] << '\n';
        } else {
            Concave Concavity = Concave();    
            cout << Concavity.sum << '\n';
               
            for(i = 0;i < Q;i++) {
                long long l = A[oper[i].l], r = A[oper[i].r];
                Concavity.Modify(oper[i].l, r);
                Concavity.Modify(oper[i].r, l);
                Concavity.Normalize();
                cout << Concavity.sum << '\n';                
            }
        }
    }
}
