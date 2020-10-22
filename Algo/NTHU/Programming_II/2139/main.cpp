#include <iostream> 
#include <cstring>

using namespace std;
int X, Y, Z;

class Node {
    Node *left, *right;
    string symbol;
    
    static bool IsOperation(string& symbol) { return symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/"; }

    static int GetValue(string& symbol) {
        if(symbol == "x") return X;
        if(symbol == "y") return Y;
        if(symbol == "z") return Z;

        int ans = 0;
        for(int i = 0;i < symbol.size();i++) {
            ans *= 10;
            ans += symbol[i] - '0';
        }
        return ans;
    }

public:
    Node(): left(nullptr), right(nullptr) {}
    static Node* Build() {
        Node* ans = new Node();
        cin >> ans->symbol;
        if(IsOperation(ans->symbol)) {
            ans->left = Build();
            ans->right = Build();
        }
        return ans;
    }

    int Execute() {
        if(this->symbol == "+") {
            return this->left->Execute() + this->right->Execute();
        } else if(this->symbol == "-") {
            return this->left->Execute() - this->right->Execute();
        } else if(this->symbol == "*") {
            return this->left->Execute() * this->right->Execute();
        } else if(this->symbol == "/") {
            return this->left->Execute() / this->right->Execute();
        } else {
            return GetValue(this->symbol);
        }
    }

    void Show() {
        if(IsOperation(this->symbol)) {
            this->left->Show();
            cout << this->symbol;
            this->right->Show();
        } else {
            cout << this->symbol;
        }
    }
};

int main() {
    Node* root = Node::Build();
    cin >> X >> Y >> Z;
    root->Show();
    cout << endl << root->Execute() << endl;
}
