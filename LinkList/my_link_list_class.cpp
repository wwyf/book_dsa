#include "my_link_list_class.h"

template<typename T>
Node<T> * LinkList<T>::set_position(int position) const// 可以优化，使用一个变量保存之前访问过的对象
/* 
    Pre: 0 <= pos < count
    Post: Return a pointer to the Node in position */
{
    Node<T> *q = head;
    for (int i = 0; i < position; i++) q = q->next_;
    return q;
}

// void set_position(int position) const// after optimize
// {
// /* 
//     Pre:
//     Post: set current referrences the Node at position */
//     if (position < current_position){
//         current_position = 0;
//         current = head;
//     }
//     for (; current_position != position; current_position++)
//         current = current->next;
// }


template<typename T>
LinkList<T>::LinkList(){
    head = NULL;
    count = 0;
}

template<typename T>
LinkList<T>::~LinkList(){
    clear();
}

template<typename T>
void LinkList<T>::clear(){ 
    Node<T> *cur_node = head, *del_node = NULL;
    // while (!empty())  
    while (cur_node)
    {
        del_node = cur_node;
        cur_node = cur_node->next_;
        count--;
        delete del_node;
    }
}

template<typename T>
bool LinkList<T>::empty() const{
    return (head == NULL);
}

template<typename T>
bool LinkList<T>::full() const{
    return false;
}

template<typename T>
int LinkList<T>::size() const{
    return count;
}

template<typename T>
Error_code LinkList<T>::insert(int position, const T & x){
/* 
    Pre: position: no limitation, maybe return Error_code
    Post: if position < 0 and position > count, return Error_code
          else insert a new Node before corresponding Node in the positionition
          position == count insert a new Node in the end */
    if (position < 0 || position > count){
        return range_error;
    }
    Node<T> *previous = NULL, *following = NULL, *new_node = NULL;
    if (position == 0){
        following = head;
    }
    else{
        previous = set_position(position-1);
        following = previous->next_;
    }
    new_node = new Node<T>(x, following);
    if (position == 0)
        head = new_node;
    else
        previous->next_ = new_node;
    count++;
    return success;
}

template<typename T>
Error_code LinkList<T>::remove(int position, T & x){
/* 
    Pre: position : no limit
    Post: 
        if position don't make sense, return error_code*/
    if (position < 0 || position >= count)
        return range_error;
    Node<T> *previous = NULL, *following = NULL, *del_node = NULL;

    if (position == 0){
        del_node = head;        
        following = head->next_;
    }
    else {
        previous = set_position(position-1);
        del_node = previous->next_;
        following = del_node->next_;
    }
    x = del_node->data_;
    delete del_node;
    if (position == 0){
        head = following;
    }
    else {
        previous->next_ = following;
    }
    count--;
    return success;
}

template<typename T>
Error_code LinkList<T>::retrieve(int position, T & x) const{
/* 
    Pre:
    Post: 
        if 0 <= position < count,  */
    if (position < 0 || position >= count)
        return range_error;
    x = set_position(position)->data_;
    return success;
}

template<typename T>
Error_code LinkList<T>::replace(int position, const T & x){
/* 
    Pre:
    Post: */
    if (position < 0 || position >= count)
        return range_error;
    set_position(position)->data_ = x;
    return success;
}


template<typename T>
void LinkList<T>::traverse(void (*visit)(T &)){
/* 
    Pre: 
    Post: visit all the entry in the list, and use a function on every node */
    Node<T> *cur_node = head;
    while (cur_node != NULL){
        (*visit)(cur_node->data_);
        cur_node = cur_node->next_;
    }
}


