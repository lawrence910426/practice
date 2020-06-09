#include <iostream>
#include <map>
#include <vector>
#include <memory.h>

using namespace std;

map<int ,int> parent;
vector<int> kid[105];
vector<int> ans[105];
int N ,m ,root ,a ,b;

void dfs(int on) {
    int raw_on = on;
    if(kid[on].size() == 0) {
        on = parent[on];
        if(on == root) ans[raw_on].push_back(-1);
        while(on != root) {
            ans[raw_on].push_back(on);
            on = parent[on];
        }
    } else for(int item : kid[on]) dfs(item);
}

int main() {
    for(cin >> N;N--;cout << endl) {
        parent = map<int ,int>();
        memset(kid ,0 ,sizeof(kid));
        memset(ans ,0 ,sizeof(ans));
        for(cin >> m;m--;) {
            scanf("%d,%d" ,&a ,&b);
            if(b == 99) root = a;
            else {
                parent[a] = b;
                kid[b].push_back(a);
            }
        }
        dfs(root);
        for(int i = 0;i < 105;i++) {
            if(ans[i].size() != 0) {
                printf("%d:" ,i);
                if(ans[i][0] == -1) printf("N\n");
                else {
                    printf("{");
                    for(int j = 0;j < ans[i].size();j++)
                        if(j == ans[i].size() - 1) printf("%d" ,ans[i][j]);
                        else printf("%d," ,ans[i][j]);
                    printf("}\n");
                }
            }
        }
    }
}
