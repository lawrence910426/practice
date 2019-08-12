#include <iostream>
#include <set>
#include <string>
#include <memory.h>
#include <stack>

using namespace std;
set<string> ans;
set<string> visit[50][50];
stack<char> cstack;
int LCS[50][50] ,previous[50][50];
string a, b;

void run_lcs() {
    int i ,j;
    for(i = 1;i <= a.size();i++) for(j = 1;j <= b.size();j++) {
        LCS[i][j] = max(LCS[i][j - 1] ,LCS[i - 1][j]);
        if(a[i - 1] == b[j - 1]) LCS[i][j] = max(LCS[i - 1][j - 1] + 1 ,LCS[i][j]);
        if(LCS[i][j] == LCS[i - 1][j - 1] + 1 && a[i - 1] == b[j - 1]) previous[i][j] |= 1;
        if(LCS[i][j] == LCS[i][j - 1]) previous[i][j] |= 2;
        if(LCS[i][j] == LCS[i - 1][j]) previous[i][j] |= 4;
    }
}

inline string getstring() {
    string ret;
    stack<char> s = cstack;
    while(!s.empty()) {
        ret += s.top();
        s.pop();
    }
    return ret;
}

void trace_back(int x ,int y) {
    string s = getstring();
    if(visit[x][y].find(s) != visit[x][y].end()) return;
    visit[x][y].insert(s);

    if(x == 0 || y == 0 || cstack.size() == LCS[a.size()][b.size()]) {
        ans.insert(s);
    } else {
        if((previous[x][y]) & 1) {
            cstack.push(a[x - 1]);
            trace_back(x - 1 ,y - 1);
            cstack.pop();
        }
        if((previous[x][y] >> 1) & 1) trace_back(x ,y - 1);
        if((previous[x][y] >> 2) & 1) trace_back(x - 1 ,y);
    }
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    int T ,cases = 0;
    int i ,j;
    for(cin >> T;T--;) {
        cin >> a >> b;
        memset(LCS ,0 ,sizeof(LCS));
        memset(previous ,0 ,sizeof(previous));
        for(i = 0;i <= a.size();i++) for(j = 0;j <= b.size();j++) visit[i][j] = set<string>();
        ans = set<string>();
        cstack = stack<char>();

        run_lcs();
        trace_back(a.size() ,b.size());
        cout << "Case #" << ++cases << ": " << ans.size() << '\n';
        for(string s : ans) cout << s << '\n';
    }
}
// Hsu Pang ,I dont like this problem QQ.
// 許胖，我不喜歡這題
