#include <iostream>

typedef int index;
const int MAX_LIST = 7;

template <typename T>
struct Node{
public:
    T data_;
    index next_;
    Node();{}
    Node(T data, index next):data_(data), next_(next){}
};


template <typename T>
class ListArray{
public:

protected:
    Node<T> workspace[max_list];
    index available, last_used, head;
    int count;
//
    index new_node();
    void delete_node(index n) const;
    int current_position(index n) const;
    index set_position(int position) const;
};



index ListArray::new_node(){
/* 
    Pre: 
    Post: 
        if full , return -1
        return the new_index     */
    index new_index;
    if (available != -1){
        new_index = available;
        available = workspace[available].next;
    } else if (last_used < max_list-1){
        new_index = ++last_used;
    } else return -1;
    workspace[new_index].next = -1;
    return new_index;
}

void delete_node(index n) const{
/* 
    Pre: the list has a node stored in index old_index 
    Post: .... */
    index previous;
    if (old_index == head) head = workspace[old_index].next;
    else {
        previous = set_position(current_position(old_index) - 1);
        workspace[previous]next = workspace[old_index].next;
    }
    workspace[old_index].new_index = available;
    available = old_index;
}
int current_position(index n) const;
index set_position(int position) const;