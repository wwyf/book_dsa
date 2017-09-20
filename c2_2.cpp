#include<iostream>
#define MAX 100
using namespace std;


template <typename T>
class Stack_array{
public:
    typedef int size_t;
    Stack_array(){
        data = new T[MAX];
        size = 0;
    }
    void push(T item) 
    {
        data[size] = item;
        size++;
    }
    void pop(){
        if (empty()){
            return;
        }
        size--;
    }
    T top() const{
        if (empty()){
            return 0 ;
        }
        return data[size];
    }
    bool empty() const{
        return (!size);
    }
    void print() const {
        for (int i = size-1; i >= 0; i--){
            cout << data[i] << " ";
        }
        cout << endl;
    }
    ~Stack_array(){
        delete data;
    }
private:
    T* data;
    size_t size;
};

int main(){
    Stack_array<char> test;
    test.push('a');
    for (char i = 'a'; i < 'z'; i++){
        test.push(i);
        test.print();
    }
    for (char i = 0; i < 24; i++){
        cout << test.top() << endl;
        test.pop();
        test.print();
    }
    return 0;
}