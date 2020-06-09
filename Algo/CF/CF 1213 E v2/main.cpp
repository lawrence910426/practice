#include <iostream>
#include <cstring>
#include <set>

using namespace std;
string a, b;
set<string> ans;
#define allow(F ,S) !((F == a[0] && S == a[1]) || (F == b[0] && S == b[1]))
void dfs(int left[3] ,string s) {
    char tmp;
    if(left[0] == 0 && left[1] == 0 && left[2] == 0) ans.insert(s);
    for(int i = 0;i < 3;i++) {
        if(s == "" || (left[i] >= 1 && allow(s[s.size() - 1] ,i + 'a'))) {
            left[i] -= 1;
            tmp = 'a' + i;
            dfs(left ,s + tmp);
            left[i] += 1;
        }
    }
}

int main() {
    int N ,left[3];
    int i;
    string result;
    while(cin >> N) {
        cin >> a >> b;
        left[0] = left[1] = left[2] = 1;
        ans = set<string>();
        dfs(left ,"");
        cout << "YES\n";
        if(a[0] == a[1] && b[0] == b[1]) {
            result = *ans.begin();
            for(i = 0;i < N;i++) cout << result;
        } else if(a[0] == a[1] || b[0] == b[1]) {
            for(string s : ans)
                if(allow(s[0] ,s[1]) && allow(s[1] ,s[2]) && allow(s[2] ,s[0]))
                    result = s;

            for(i = 0;i < N;i++) cout << result;
        } else {
            result = *ans.begin();
            for(i = 0;i < N;i++) cout << result[0];
            for(i = 0;i < N;i++) cout << result[1];
            for(i = 0;i < N;i++) cout << result[2];
        }
        cout << endl;
    }
}
