#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sum;
vector<int> data;
bool dfs(int status[4] ,int depth) {
    if(status[0] > sum / 4 || status[1] > sum / 4 || status[2] > sum / 4 || status[3] > sum / 4)
        return false;
    if(status[0] == sum / 4 && status[1] == sum / 4 && status[2] == sum / 4)
        return true;
    if(data.size() == -1)
        return false;

    //printf("%d %d %d\n" ,data[0] ,data[1] ,data[2]);

    for(int i = 0;i < 4;i++) {
        status[i] += data[depth];
        if(dfs(status ,depth +- 1)) return true;
        status[i] -= data[depth];
    }
    return false;
}

int main() {
    int i = 0,T ,value ,n ,status[4];
    for(cin >> T;T--;) {
        sum = 0 ,data = vector<int>() ,status[0] = status[1] = status[2] = status[3] = 0;
        for(cin >> n;n--;) {
            cin >> value;
            data.push_back(value);
            sum += value;
        }
        if(sum % 4 == 0) {
            sort(data.begin() ,data.end());
            cout << (dfs(status ,data.size() - 1) ? "yes" : "no") << endl;
        } else cout << "no" << endl;

        //if(i++ > 10) return 0;
    }

}


/*
5
8 1 7 2 6 4 4 3 5
*/








/*
int sum;
vector<int> inputs;

bool test(int data[3] ,int depth) {
    #define d3 (sum - data[0] - data[1] - data[2])
    if(data[0] == data[1] && data[0] == data[2] && data[0] == d3)
        return true;



    if(data[0] > sum / 4 || data[1] > sum / 4 || data[2] > sum / 4) return false;
    if(depth == inputs.size()) return false;

    if(data[0] == sum / 4 && data[1] == sum / 4) {
        printf("%d %d %d %d %d\n" ,data[0] ,data[1] ,data[2] ,d3 ,depth);
        system("pause");
    }

    int i = 0;
    for(i = 0;i < 3;i++) {
        data[i] += inputs[depth];
        if(test(data ,depth + 1)) return true;
        data[i] -= inputs[depth];
    }
    return false;
}

int main()
{
    int n ,m ,tmp ,ttmp[3];
    for(cin >> n;n--;) {
        ttmp[0] = ttmp[1] = ttmp[2] = 0;

        inputs = vector<int>(); sum = 0;
        for(cin >> m;m--;) {
            cin >> tmp;
            inputs.push_back(tmp);
            sum += tmp;
        }

        if(sum % 4 == 0) {
            sort(inputs.begin() ,inputs.end());
            cout << (test(ttmp ,0) ? "yes" : "no") << endl;
        } else {
            cout << "no" << endl;
        }
    }
    //system("pause");
}*/


