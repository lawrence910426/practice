#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 100005
int prime[MAXN];
vector<int> ps;
void linear_sieve() {
    int i;
    for(i = 0;i < MAXN;i++) prime[i] = i;
    for(i = 2;i < MAXN;i++) {
        if(prime[i] == i) ps.push_back(i);
        for(int p : ps) {
            if(p * i >= MAXN) break;
            prime[p * i] = p;
            if(i % p == 0) break;
        }
    }
}

int N;
string a ,b;
#define allow(F ,S) !((a[0] == F && a[1] == S) || (b[0] == F && b[1] == S))
string dfs(int left[3] ,string s) {
    string result;
    char tmp;
    if(left[0] == 0 && left[1] == 0 && left[2] == 0)
        if(N == 1 || N == prime[N] || allow(s[s.size() - 1] ,s[0]))
            return s;
    for(int i = 0;i < 3;i++) {
        if(left[i] >= 1 && (s == "" || allow(s[s.size() - 1] ,i + 'a'))) {
            left[i] -= 1;
            tmp = i + 'a';
            result = dfs(left ,s + tmp);
            left[i] += 1;
            if(result != "") return result;
        }
    }
    return "";
}

int main() {
    string result;
    int left[3];
    int i;
    linear_sieve();
    while(cin >> N) {
        cin >> a >> b;
        if(N == 1) {
            left[0] = left[1] = left[2] = 1;
            result = dfs(left ,"");
            if(result == "") cout << "NO\n";
            else cout << "YES\n" << result << endl;
        } else {
            left[0] = left[1] = left[2] = prime[N];
            result = dfs(left ,"");
            cout << "YES\n";
            for(i = 0;i < N / prime[N];i++) cout << result;
            cout << endl;
        }
    }
}
