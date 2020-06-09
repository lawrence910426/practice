#include <iostream>
#include <algorithm>
#include <sstream>
#include <float.h>
#include <stack>
#include <vector>

using namespace std;
char symbols[30];
double numbers[30];
int N;

inline double get_value() {
    vector<pair<double ,char> > seq;
    stack<char> tmp;
    seq.push_back(pair<double ,char>(numbers[0] ,'\0'));
    for(int i = 1;i < N;i++) {
        if(!tmp.empty() && (tmp.top() == '*' || tmp.top() == '/') && (symbols[i - 1] == '+' || symbols[i - 1] == '-'))
            for(;!tmp.empty();tmp.pop()) seq.push_back(pair<double ,char>(0 ,tmp.top()));
        tmp.push(symbols[i - 1]);
        seq.push_back(pair<double ,char>(numbers[i] ,'\0'));
    }
    for(;!tmp.empty();tmp.pop()) seq.push_back(pair<double ,char>(0 ,tmp.top()));
    stack<double> tmp2;
    for(auto item : seq) {
        if(item.second == '\0') tmp2.push(item.first);
        else {
            double beta = tmp2.top(); tmp2.pop();
            double alpha = tmp2.top(); tmp2.pop();
            if(item.second == '+') tmp2.push(alpha + beta);
            if(item.second == '-') tmp2.push(alpha - beta);
            if(item.second == '*') tmp2.push(alpha * beta);
            if(item.second == '/') tmp2.push(alpha / beta);
        }
    }
    return tmp2.top();
}

int main() {
    ios::sync_with_stdio(0) ,cin.tie(0) ,cout.tie(0);
    string s1 ,s2;
    getline(cin ,s1);
    stringstream ss = stringstream(s1);
    for(N = 0;ss >> numbers[N];N++) ;
    getline(cin ,s2);
    ss = stringstream(s2);
    for(int i = 0;ss >> symbols[i];i++) ;
    sort(symbols ,symbols + N - 1);

    double ans = -1e100;
    do {
        ans = max(ans ,get_value());
    } while(next_permutation(symbols ,symbols + N - 1));
    printf("%.2lf\n" ,ans);

}
