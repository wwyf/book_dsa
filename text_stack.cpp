#include<iostream>
using namespace std;

typedef int Node_entry;
struct Node{
    Node_entry entry;
    Node *next;
    Node(){
        next = NULL;
    }
    Node(Node_entry item, Node *add_on = NULL){
        entry = item;
        next = add_on;        
    }
};

class Stack{
public:
    Stack(){
        top_node = NULL;
        size = 0;
    }
    void push(Node_entry item){
        if (empty()){
            top_node = new Node(item);
            size++;
            return ;
        }
        Node *new_node = new Node(item, top_node);
        top_node = new_node;
        size++;
        return ;
    }
    void pop(){
        if(empty()){
            return ;
        }
        Node *del_node = top_node;
        top_node = top_node->next;
        delete del_node;
        size--;
        return ;
    }    
    Node_entry top(){
        if (empty()){
            return 0;
        }
        return top_node->entry;
    }
    Stack(const Stack & rhs){
        Node *new_cpy = NULL;
        Node *new_top = NULL;
        int new_size = 0;
        Node *ori_node = rhs.top_node;
        if (rhs.empty()){
            new_top = NULL;
            new_size = 0;
        }
        else {
            new_cpy = new_top = new Node(ori_node->entry);
            while (ori_node->next != NULL){
                ori_node = ori_node->next;
                new_cpy->next = new Node(ori_node->entry);
                new_cpy = new_cpy->next;
            }
            new_size = rhs.count();
        }
        top_node = new_top;
        size = new_size;
    }
    const Stack & operator=(const Stack & rhs){
        Node *new_cpy = NULL,*new_top = NULL, *ori_node = rhs.top_node;
        int new_size = 0;
        if (rhs.empty()){
            new_top = NULL;
            new_size = 0;
        }
        else {
            new_cpy = new_top = new Node(ori_node->entry);
            while(ori_node->next != NULL){
                ori_node = ori_node->next;
                new_cpy->next = new Node(ori_node->entry);
                new_cpy = new_cpy->next;
            }
            new_size = rhs.count();
        }
        while (!empty()){
            pop();
        }
        top_node = new_top;
        size = new_size;
        return rhs ;
    }
    void print() const {
        Node *cur_node = top_node;
        while(cur_node != NULL){
            cout << cur_node->entry << " ";
            cur_node = cur_node->next;
        }
        cout << endl;
    }
    bool empty() const {
        return !size;
    }
    int count() const {
        return size;
    }
private:
    Node *top_node;
    int size;
};
int main(){
    Stack test;
    for (int i = 0; i < 10; i++){
        test.push(i);
    }
    test.print();
    Stack test2(test);
    test2.print();
    test2.pop();
    test = test2;
    test.print();
    for (int i = 0; i < 20; i++){
        cout << test.top() << "!!  ";
        test.pop();
        test.print();
    }
    return 0;
}