#ifndef MY_LINK_LIST_CLASS_H
#define MY_LINK_LIST_CLASS_H

#include <iostream>
template <typename T>
struct Node{
// data member
    T data_;
    Node<T> *next_;
// constructor
    Node();
    Node(T data, Node<T> *next = NULL):data_(data), next_(next){}
};

enum Error_code{
    success,
    range_error
};

template <typename T>
class LinkList{
public:
    LinkList();
    ~LinkList();
    LinkList(const LinkList<T> & copy);
    void clear();
    bool empty() const;
    bool full() const;
    int size() const;
    Error_code insert(int pos, const T & x);
    Error_code remove(int position, T & x);
    Error_code retrieve(int position, T & x) const;
    Error_code replace(int position, const T & x);
    void traverse(void (*visit)(T &));
protected:
    int count;
    Node<T> *head;
    Node<T> *set_position(int pos) const;// 可以优化，使用一个变量保存之前访问过的对象
};

template class LinkList<int>;

#endif // MY_LINK_LIST_CLASS_H