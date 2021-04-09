#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <iostream>
using namespace std;

// TODO: Implement all member functions in BaseStack
template < class T >
class BaseStack
{
public:
    // Constructor
    BaseStack() {
        _top = -1;
        capacity = 1;
        _stack = new T[capacity];
    }

    // Destructor
    ~BaseStack() { delete [] _stack; }

    // Check if the stack is empty
    bool empty() { return _top == -1; }

    // Return the size of the stack
    int size() { return _top + 1; }

    // Return the top element
    T& top() { return _stack[_top]; }

    // Insert a new element at top
    void push(const T& item) {
        _top += 1;
        if(_top == capacity) resize();
        _stack[_top] = item;
    }

    // Delete one element from top
    void pop() { _top -= 1; }

private:
    void resize() {
        T* buffer = new T[capacity * 2];
        for(int i = 0; i < capacity; i++) buffer[i] = _stack[i];
        delete [] _stack;
        _stack = buffer;
        capacity *= 2;
    }

    T* _stack;
    int _top;
    int capacity;
};

// TODO: Implement all member functions in BaseQueue
template < class T >
class BaseQueue
{
public:
    // Constructor
    BaseQueue() {
        capacity = 1;
        _queue = new T[capacity];
        _front = _rear = 0;
    }

    // Destructor
    ~BaseQueue() { delete [] _queue; }

    // Check if the stack is empty
    bool empty() { return _front == _rear; }

    // Return the size of the queue
    int size() { return _rear - _front; }

    // Return the front element
    T& front() { return _queue[_front]; }

    // Insert a new element at rear
    void push(const T& item) {
        if(_rear == capacity) extend();
	_queue[_rear++] = item;
    }

    // Delete one element from front
    void pop() { _front += 1; }

private:
    void extend() {
        T* buffer = new T[capacity * 2];
        for(int i = 0; i < _rear - _front; i++) buffer[i] = _queue[_front + i];
        delete [] _queue;
        _queue = buffer; 
        _rear -= _front;
        _front = 0;
        capacity *= 2;
    }
    T* _queue;
    int _front, _rear;
    int capacity;
};

BaseQueue<char> *Q = new BaseQueue<char>[100];
BaseStack<string> *S = new BaseStack<string>();
// TODO: Implement five types of command
void insert(int L) {
    int offset;
    string name; 
    cin >> offset >> name;
    
    int maxi = -1;
    for(int i = offset; i < offset + name.length(); i++) maxi = max(maxi, Q[i].size());

    for(int i = offset; i < offset + name.length(); i++) {
        while(Q[i].size() < maxi) Q[i].push('@');
        Q[i].push(name[i - offset]);
    }
}
string first_row(int L, bool print = false) {
    string ans;
    for(int i = 0; i < L; i++) ans += (Q[i].empty() ? '~' : Q[i].front());
    if(print) cout << "BOTTOM_ROW" << endl << ans << endl;
    return ans;
}
void query(int L) {
    string row = first_row(L), name;
    cin >> name;
    for(int i = 0; i < L; i++) {
        int j;
        for(j = 0; j < name.length() && i + j < L; j++) if(row[i + j] != name[j]) break;
        if(j == name.length()) {
            for(j = i; j < i + name.length(); j++) Q[j].pop();
            S->push(name);
            break;
        }
    }
}
void flush() {
    cout << "FLUSH" << endl;
    while(!S->empty()) {
        cout << S->top() << endl;
        S->pop();
    }
}
void reset(int L) {
    delete [] Q;
    Q = new BaseQueue<char>[L];
    delete S;
    S = new BaseStack<string>();
}

// The codes bellow prevent you from importing C++ containers.
// Nothing needed to be implemented below.
// Do not modify the codes below.
#endif
#ifndef vector
#define vector
#endif
#ifndef list
#define list
#endif
#ifndef forward_list
#define forward_list
#endif
#ifndef deque
#define deque
#endif
#ifndef array
#define array
#endif
#ifndef set
#define set
#endif
#ifndef multiset
#define multiset
#endif
#ifndef map
#define map
#endif
#ifndef multimap
#define multimap
#endif
#ifndef unordered_set
#define unordered_set
#endif
#ifndef unordered_multiset
#define unordered_multiset
#endif
#ifndef unordered_map
#define unordered_map
#endif
#ifndef unordered_multimap
#define unordered_multimap
#endif
#ifndef bitset
#define bitset
#endif
#ifndef valarray
#define valarray
#endif
#ifndef stack
#define stack
#endif
#ifndef queue
#define queue
#endif
#ifndef priority_queue
#define priority_queue
#endif
