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

class Queue{
public:
    Queue(){
        front = NULL;
        rear = NULL;
        count = 0;
    }
    void append(Node_entry item){
        if (empty()){
            Node *new_node = new Node(item);
            front = rear = new_node;
            count++;
            return ;
        }
        else {
            Node *new_node = new Node(item);
            rear->next = new_node;
            rear = new_node;
            count++;
            return ;
        }
    }
    void serve(){
        if (empty()){
            return ;
        }
        Node *del_node = front;
        front = front->next;
        if (size() == 1){ rear = front;}
        delete del_node;
        count--;
        return ;
    }
    
    Node_entry retrieve(){
        if (empty()){
            return 0;
        }
        else {
            return front->entry;
        }
    }
    
    Queue(const Queue & rhs){
        Node *new_cpy = NULL, *new_front = NULL, *new_rear = NULL;
        Node *old_front = rhs.front, *old_rear = rhs.front;
        if (!rhs.empty()){
            new_rear = new_cpy = new_front = new Node(old_front->entry);
            while (old_front->next != NULL){
                old_front = old_front->next;
                new_rear->next = new Node(old_front->entry);
                new_rear = new_rear->next;
            }            
        }
        front = new_front;
        rear = new_rear;
        count = rhs.size();
    }
    void operator=(const Queue & rhs) {
        Node *new_front = NULL, *new_rear = NULL;
        Node *old_front = rhs.front;
        if (!rhs.empty()){
            new_rear = new_front = new Node(old_front->entry);
            while (old_front->next != NULL){
                old_front = old_front->next;
                new_rear->next = new Node(old_front->entry);
                new_rear = new_rear->next;
            }
        }
        while (!empty()){
            serve();
        }
        front = new_front;
        rear = new_rear;
        count = rhs.size();
    }
    bool empty() const{
        return !count;
    }
    
    void print() const{
        Node *cur_node = front;
        while (cur_node != NULL){
            cout << cur_node->entry << " ";
            cur_node = cur_node->next;
        }
        cout << endl;
    }
    
    int size() const{
        return count;
    }
private:
    Node *front;
    Node *rear;
    int count;    
};

int main(){
    Queue test;
    for (int i = 0; i < 10; i++){
        test.append(i);
        test.print();
    }
    test.print();
    Queue test2(test);
    test2.serve();
    test2.print();
    test = test2;
    test.print();
    for (int i = 0; i < 15; i++){
        cout << test.retrieve() << "!!! ";
        test.serve();
        test.print();
    }
}