#include <iostream>
using namespace std;
// 感想：就是无论进行什么操作，都需要注意是否需要更新类内的数据成员，确保类的数据成员都得到更新
// 自己打的双向链表有一个缺点，有几个函数都是先用setPosition(0)找到头指针，然后开始迭代。其实这样子就不能很好的利用双向链表的特性。
// 参考答案，也写了一点注释，之后可能需要再打一次，巩固一下。
enum Error_code
{
    success,
    underflow,
    overflow
};

template <class List_entry>
struct Node
{
    List_entry entry;
    Node<List_entry> *back;
    Node<List_entry> *next;
    Node(){}
    Node(List_entry data, Node<List_entry> *link_back = NULL,
                    Node<List_entry> *link_next = NULL):
                    entry(data), next(link_next), back(link_back){}
};

template <class List_entry>
class MyList
{
  public:
    MyList();
    ~MyList();
    // 拷贝构造函数和赋值运算符重载，注意深拷贝与浅拷贝的差异
    MyList(const MyList<List_entry> &copy);
    void operator=(const MyList<List_entry> &copy); // 清空list
    void clear(); // 判断list是否为空
    bool empty() const; // 判断list是否已满
    bool full() const; // 获取list的元素数量
    int size() const; // 在第position个位置插入值为entry的元素，如果position为0则插入在链表头，依次类推
    // 若position < 0 或者 position > count，则返回underflow
    Error_code insert(int position, const List_entry &entry); // 删除第position个位置的元素，并将该元素的值保存在entry中
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code remove(int position, List_entry &entry); // 获取第position个位置的元素，保存在entry中
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code retrieve(int position, List_entry &entry) const; // 将第position个位置的元素替换为entry
    // 若position < 0 或者 position >= count，则返回underflow
    Error_code replace(int position, const List_entry &entry); // 用visit函数遍历list内所有的元素
    void traverse(void (*visit)(List_entry &));
  protected:
    int count; // 记录list内元素数量
    mutable int curPosition; // current指针的位置编号
    mutable Node<List_entry> *current; // current指针
    // 设置current指针的位置，指向第position个位置
    void setPosition(int position) const;
};


template<typename List_entry>
void MyList<List_entry>::setPosition(int position) const
/*  Pre: position is valid
    Post: the pointer current change    */
{
    if (curPosition <= position)
        for (; curPosition != position; curPosition++)
            current = current->next;
    else
        for (; curPosition != position; curPosition--)
            current = current->back;
    curPosition = position;
}

template<typename List_entry>
MyList<List_entry>::MyList(){
    current = NULL;
    curPosition = 0;
    count = 0;
}

template<typename List_entry>
MyList<List_entry>::~MyList(){
    clear();
}

template<typename List_entry>
void MyList<List_entry>::clear()
// 如果空的话直接返回，否则就逐个节点释放，然后使更新类内的三个数据成员
// 参考答案写法更好一些
{
    if (empty()) return ;
    setPosition(0);
    Node<List_entry> *cur_node = current;
    Node<List_entry> *del_node = NULL;
    while (cur_node){
        del_node = cur_node;
        cur_node = cur_node->next;
        delete del_node;
    } 
    count = 0;
    current = NULL;
    curPosition = 0;
}
    // Node<List_entry> *p, *q;
    // if (current == NULL) return;
    // for (p = current->back; p; p = q) {
    //     q = p->back;
    //     delete p;
    // }
    // for (p = current; p; p = q) {
    //     q = p->next;
    //     delete p;
    // }
    // count = 0;
    // current = NULL;
    // current_position = −1;
    // }

template<typename List_entry>
bool MyList<List_entry>::empty() const {
    if (count  == 0 && current == NULL)
        return true;
    return false;
}

template<typename List_entry>
bool MyList<List_entry>::full() const {
    // 链表不会满，除非内存不够
    // 正确写法 try{new} 如果 new 出来的指针为NULL，则内存不够
    return 0;
}

template<typename List_entry>
int MyList<List_entry>::size() const{
    return count;
}

template<typename List_entry>
Error_code MyList<List_entry>::insert(int position, const List_entry & x){
    Node <List_entry> *new_node = NULL, *following = NULL, *preceding = NULL;
    if (position < 0 || position > count)  return underflow;
    if (position == 0){
        if (count == 0){
            following = NULL;
        }
        else{
            setPosition(0);
            following = current;
        }
        preceding = NULL;
    }
    else {
        setPosition(position-1);
        preceding = current;
        following = preceding->next;
    }
    // 以上是调整前置节点以及后继节点的地址
    // 若存在，则为节点地址，若无，则为NULL

    // preceding   new_node   following 三个节点之间的连接
    new_node = new  Node<List_entry>(x, preceding, following);
    if(new_node == NULL)  return overflow;
    if (preceding != NULL) preceding->next = new_node;
    if (following != NULL) following->back = new_node;
    current = new_node;
    curPosition = position;
    count++;
    return success;
}

template<typename List_entry>
Error_code MyList<List_entry>::remove(int position, List_entry &entry){
    if (position < 0 || position >= count) return underflow;
    if (empty()) return underflow;
    Node<List_entry> * del_node = NULL, *following = NULL, * preceding = NULL;
    // 对 preceding del_node following 三个节点的处理，对部分特殊情况，通过给following或preceding赋值为NULL表示该节点不存在
    if (position == 0){
        setPosition(0);
        if (count == 1){
            preceding = NULL;
            following = NULL;
        }
        else {
            following = current->next;
            preceding = NULL;
        }
        del_node = current;
    }
    else {
        setPosition(position-1);
        preceding = current;
        del_node = current->next;
        following = del_node->next;
    }
    // 开始删除节点并且修改节点之间的连接
    entry = del_node->entry;
    delete del_node;
    if (preceding != NULL) preceding->next = following;
    if (following != NULL) following->back = preceding;

    // 更新三个数据成员，关键是current指针该指向哪一个
    if (preceding == NULL && following == NULL){
        count = 0;
        current = NULL;
        curPosition = 0;
        return success;
    }
    if (following != NULL){
        current = following;
        curPosition = position;
    }
    else {
        current = preceding;
        curPosition = position-1;
    }
    count--;
    return success;
}
// template <class List_entry>
// Error_code List<List_entry>::remove(int position, List_entry &x)
// /* Post: If 0  position < n; where n is the number of entries in the List, the function succeeds:
// The entry in position is removed from the List, and the entries in all later positions have
// their position numbers decreased by 1. The parameter x records a copy of the entry
// formerly in position. Otherwise the function fails with a diagnostic error code. */
// {
//     Node<List_entry> *old_node, *neighbor;
//     if (count == 0)
//         return fail;
//     if (position < 0 || position >= count)
//         return range_error;
//     set_position(position);  // 先找到需要删除的那一个节点 
//     old_node = current; 
//     if (neighbor = current->back) 
//     // neighbor 暂时存放current的前继，如果前继存在，就让前继连上需要删除的节点的后继
//         neighbor->next = current->next;
//     if (neighbor = current->next) 
//     // neighbor 暂时存放current的后继，如果后继存在，就让后继连上需要删除的节点的前继，并且让current指针指向后继，此时由于将要删除一个节点，current指针指向后继后，position不变。
//     {
//         neighbor->back = current->back;
//         current = neighbor;
//     }
//     else  // neighbor 没有后继，只能让current指向前继，并且让current 的position减1，此语句同样能够处理只剩下一个节点需要remove的情况
//     {
//         current = current->back;
//         current_position−−;
//     }
//     // 前面的语句已经处理好了current指针，以及其他数据成员，下面只管删除就好
//     x = old_node->entry;
//     delete old_node;
//     count−−;
//     return success;
// }

template<typename List_entry>
Error_code MyList<List_entry>::retrieve(int position, List_entry & entry) const{
    if (position < 0 || position >= count) return underflow;
    setPosition(position);
    entry = current->entry;
    return success;
}


template <typename List_entry>
Error_code MyList<List_entry>::replace(int position, const List_entry & entry){
    if (position < 0 || position >= count) return underflow;
    setPosition(position);
    current->entry = entry;
    return success;
}

template<typename List_entry>
void MyList<List_entry>::traverse(void (*visit)(List_entry &)){
    setPosition(0);
    Node<List_entry> *cur_node = current;
    while(cur_node){
        (*visit)(cur_node->entry);
        cur_node = cur_node->next;
    } 
}

template<typename List_entry>
void MyList<List_entry>::operator=(const MyList<List_entry> &copy)
{
    Node<List_entry> *old_head = NULL, *old_node = NULL;
    Node<List_entry> *new_head = NULL;
    Node<List_entry> *new_prec = NULL;
    if (copy.empty()){
        new_head = NULL;
    }
    else {
        copy.setPosition(0);
        old_head = copy.current;
        new_head = new Node<List_entry>(old_head->entry);
        new_prec = new_head;
        old_node = old_head->next;
        while (old_node){
            Node <List_entry> *new_node = new Node<List_entry>(old_node->entry);
            new_prec->next = new_node;
            new_node->back = new_prec;
            new_prec = new_node;
            old_node = old_node->next;
        }
    }
    clear();
    current = new_head;
    count = copy.size();
    curPosition = 0;
}
// 答案中的一种技巧
// template <class List_entry>
// void List<List_entry>::operator=(const List<List_entry> &copy)
// {
//     List new_copy(copy);
//     clear();
//     count = new_copy.count;
//     current_position = new_copy.current_position;
//     current = new_copy.current;
//     new_copy.count = 0;
//     new_copy.current_position = 0;
//     new_copy.current = NULL;
// }
// 还有颜彬提供的一种技巧，调用复制构造函数，然后swap

template<typename List_entry>
MyList<List_entry>::MyList(const MyList<List_entry> & copy){
    if (copy.empty()){
        count = 0;
        current = NULL;
        curPosition = 0;
        return ;
    }
    copy.setPosition(0);
    Node<List_entry> *old_node = copy.current;
    Node<List_entry> *new_head = new Node<List_entry>(old_node->entry);
    Node<List_entry> *new_prec = new_head;
    old_node = old_node->next;
    while (old_node){
        Node <List_entry> *new_node = new Node<List_entry>(old_node->entry);
        new_prec->next = new_node;
        new_node->back = new_prec;
        new_prec = new_node;
        old_node = old_node->next;
    }
    current = new_head;
    count = copy.size();
    curPosition = 0;
}
// template <class List_entry>
// List<List_entry>::List(const List<List_entry> &copy)
// {
//     count = copy.count;
//     current_position = copy.current_position;
//     Node<List_entry> *new_node, *old_node = copy.current;
//     if (old_node == NULL)
//         current = NULL;
//     else
//     {
//         new_node = current = new Node<List_entry>(old_node->entry);
//         while (old_node->next != NULL)
//         {
//             old_node = old_node->next;
//             new_node->next = new Node<List_entry>(old_node->entry, new_node);
//             new_node = new_node->next;
//         }
//         old_node = copy.current;
//         new_node = current;
//         while (old_node->back != NULL)
//         {
//             old_node = old_node->back;
//             new_node->back = new Node<List_entry>(old_node->entry, NULL, new_node);
//             new_node = new_node->back;
//         }
//     }
// }

void print(int & a){
    cout << a << " " ;
}

int main(){
    MyList<int> t;
    for (int i = 0; i < 10; i++){
        t.insert(0,i);
    }
    MyList<int> t2(t);
    t = t2;
    t.traverse(print);
    cout << endl;
    t2.traverse(print);
    cout << endl;
    int a;
    for (int i = 0; i < 10; i++){
        cout << t2.remove(0, a);
        cout << "e:" << a << " size:" << t2.size() << endl;
        t2.traverse(print);     
        cout << endl;
    }
    return 0;
}