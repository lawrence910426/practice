#include <iostream>
#include <cstring>

using namespace std;

class Solution {
    const int N = 3005;
    int extend(int l, int r, string& s) {
        int ans = 0;
        while(0 <= l && r < s.size() && s[l] == s[r]) { ans += 1; l -= 1; r += 1; }
        return ans;
    }
public:
    string longestPalindrome(string s) {
        string ss = "$";
        for(int i = 0;i < s.size();i++) { ss += s[i]; ss += "$"; }
        // cout << ss << endl;

        int Z[N];
        for(int i = 0;i < N;i++) Z[i] = 0;
        int pos = 0; Z[0] = 1;
        for(int i = 1;i < ss.size();i++) {
            if(pos + Z[pos] <= i) {
                Z[i] = extend(i, i, ss);
                pos = i;
            } else {
                int mirror = 2 * pos - i;
                if(i + Z[mirror] == pos + Z[pos]) {
                    Z[i] = Z[mirror] + extend(i - Z[mirror], i + Z[mirror], ss);
                    pos = i;
                } else {
                    Z[i] = min(Z[mirror], pos + Z[pos] - i);
                }
            }
        }
        // for(int i = 0;i < ss.size();i++) cout << i << " " << Z[i] << " " << ss[i] << endl;
        int maxi = 0;
        for(int i = 0;i < ss.size();i++) if(Z[i] > Z[maxi]) maxi = i;

        string ans = "";
        for(int i = maxi - Z[maxi] + 1;i <= maxi + Z[maxi] - 1;i++) if(ss[i] != '$') ans += ss[i];
        return ans;
    }
};

int main() {
    string s; cin >> s;
    Solution sol = Solution();
    cout << sol.longestPalindrome(s) << endl;
}
/*
ABABA
*/
