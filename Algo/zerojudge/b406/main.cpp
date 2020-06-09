#include <iostream>
#include <ext/rope>
#include <cstring>
using namespace std;
using namespace __gnu_cxx;

rope<char> *data[50005];
int main() {
    int Q ,cmd ,v ,start ,length ,c = 0 ,version = 0;
    int i;
    string str;
    for(cin >> Q;Q--;) {
        cin >> cmd;
        if(cmd == 1) {
            cin >> start >> str;
            start -= c;
            version += 1;
            if(version == 1) data[version] = new rope<char>();
            else data[version] = new rope<char>(*data[version - 1]);
            for(i = 0;i < str.size();i++)
                data[version]->insert(start + i ,str[i]);
        } else if(cmd == 2) {
            cin >> start >> length;
            start -= c + 1 ,length -= c;
            version += 1;
            data[version] = new rope<char>(*data[version - 1]);
            data[version]->erase(start ,length);
        } else if(cmd == 3) {
            cin >> v >> start >> length;
            v -= c, start -= c + 1 ,length -= c;;
            for(i = start;i < start + length;i++) {
                c += (data[v]->at(i) == 'c' ? 1 : 0);
                cout << data[v]->at(i);
            }
            cout << endl;
        }
        //cout << *data[version] << endl;
    }
    //system("pause");
}
