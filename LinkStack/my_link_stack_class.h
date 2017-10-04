#include<iostream>
using namespace std;

template <typename T>
struct Node{
    T data_;
    Node *next_;
    Node():next_(NULL){};
    Node(T data, Node *next):data_(data),next_(next){}
};

template <typename T>
class LinkStack{
public:
    LinkStack():top_node_(NULL){}
    LinkStack(const LinkStack & rhs){
        Node *new_copy = NULL, *new_top = NULL, *old_top = top_node_;
        if (!rhs.empty()){
            new_copy = new_top = new Node(old_top->data);
            while (old_top->next){
                old_top = old_top->next;
                new_copy->next = new Node(old_top->data);
                new_copy = new_copy->next;
            }
        }
    }
    void push(T data){
        Node *new_node = new Node(data, top_node_);
        top_node_ = new_node;
    }

    void pop() {
        if (empty()){
            return ; // TODO:need to solve some exception;
        }
        Node *del_node = top_node_;
        top_node_ = top_node_->next;
        delete del_node;
        return ;
    }

    T top() const {
        if (empty()){
            return ; // TODO: need to slove some exception;
        }
    }

    const LinkStack & operator=(const LinkStack & rhs) const{
        Node *new_copy = NULL, *new_top = NULL, *old_top = rhs.top_node_;
    }

    LinkStack operator=(LinkStack rhs) {
        swap(this->top_node_,rhs.top_node_);
        return rhs;
    }


private:
    Node *top_node_;
};