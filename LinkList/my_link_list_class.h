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

};

template <typename T>
class LinkList{
public:
    ~LinkList();
    // LinkList();
    LinkList(const LinkList<T> & copy);
    void append(T t);
    Error_code insert(int pos, const T & x);
protected:
    int count;
    Node<T> *head;
    Node<T> *set_position(int pos) const;// 可以优化，使用一个变量保存之前访问过的对象
};