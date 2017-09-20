#include <iostream>

using namespace std;
// API
template < typename T >
class Stack{
public:
    struct Node;
    typedef Node* NodePosition ;
    typedef int size_t ;
    struct Node{
        T item;
        NodePosition next;
        Node(T _item, NodePosition _next = nullptr):item(_item), next(_next){}
    };
    Stack(){
        TopNode = nullptr;
        size = 0;
    }
    void push(T data){
        if(empty()){
            NodePosition newNode = new Node(data);
            TopNode = newNode;
            size++;
            return ;
        }
        NodePosition newNode = new Node(data,TopNode);
        TopNode = newNode;
        size++;
        return ;
    }   
    T top() const {
        if (empty()){
            return 0;
        }
        return TopNode->item;
    }
    void pop() {
        NodePosition delNode = TopNode;
        TopNode = TopNode->next;
        delete delNode;
        size--;
    }
    bool empty() const{
        return (!size);
    }
    void print() const{
        NodePosition iter = TopNode;
        while(iter != nullptr){
            cout << iter->item << " ";
            iter = iter->next;
        }
        cout << endl;
    }
private:
    size_t size;
    NodePosition TopNode;
};


int main(){
    Stack<int> test;
    for (int i = 3; i < 9; i++){
        test.push(i);
        test.print();
    }
    test.print();
    test.pop();
    test.print();
    return 0;
}