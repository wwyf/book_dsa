#include "my_link_list_class.h"

Node<T> *set_position(int pos) const// 可以优化，使用一个变量保存之前访问过的对象
/* 
    Pre: 0 <= pos < count
    Post: Return a pointer to the Node in position */
{
    Node<T> *q = head;
    for (int i = 0; i < position; i++) q = q->next;
    return q;
}

void set_position(int position) const// after optimize
{
/* 
    Pre:
    Post: set current referrences the Node at position */
    if (position < current_position){
        current_position = 0;
        current = head;
    }
    for (; current_position != position; current_position++)
        current = current->next;
}

Error_code LinkList::insert(int position, const T & x){
/* 
    Pre: position: no limitation, maybe return Error_code
    Post: if position < 0 and position > count, return Error_code
          else insert a new Node before corresponding Node in the positionition
          position == count insert a new Node in the end */
    if (position < 0 || position > count){
        return range_error;
    }
    Node<T> *previous = NULL, *following = NULL, *new_node = NULL;
    if (position = 0){
        following = head;
    }
    else{
        previous = set_positionition(position-1);
        following = previous->next;
    }
    new_node = new Node<T>(x, following);
    if (position == 0)
        head = new_node;
    else
        previous->next = new_node;
    count++;
    return success;
}

