#include <iostream>


template<typename Record>
class Sortable_list{
public:
    

private:
    
}

template <typename Record>
]void Sortable_list<Record>::insertion_sort(){
    Node <Record> *first_unsorted,*last_sorted, *current, *trailing;
    if (head == NULL ) return ;
    last_sorted = head;
    while (last_sorted->next != NULL){// 每循环一次，就将一个first_unsort的节点插入到合适的位置，然后再更新last_sorted更新以备下一次循环
        first_unsorted = last_sorted->next;// ！！！
        /* 1. 如果比列表头小，那就插入头
           2. 如果比列表头大，那就插入到列表的有序部分的恰当位置
                先找到合适位置（需要两个指针，指向待插入位置前继以及待插入位置
               然后调整指针关系 */
        if (first_unsorted->entry < head->entry){
            last_sorted->next = first_unsorted->next;
            first_unsorted->next = head;
            head = first_unsorted;
        }
        else {
            trailing = head;
            current = trailing->next;
            while (first_unsorted->entry > current->entry){// 从头开始遍历，找到第一个大于first->unsorted->entry的节点，并保存它的前一个节点
                trail = current;
                current = trailing->next;
            }
            // 上面的循环中，没有等号，所以一旦循环到自己，就会退出。
            if(first_unsorted == current)
                last_sorted = first_unsorted;
            else {
                // 一个节点移动了，原来的位置需要调整关系，新插入的位置同样需要调整
                // 原来的位置
                last_sorted->next = first_unsorted->next;
                // 新插入的位置
                trailing->next = first_unsorted;
                first_unsorted->next = current;
            }
        }
    }
}


template<typename Record>
void Sortable_list<Record>::selection_sort(){
    if (head == NULL) return ;
    Node <Record> *current, *first_unsorted, *last_sorted;
    Node <Record> *min_node;
    Node <Record> *new_head = NULL;
    first_unsorted = head;
    current = head;
    while(first_unsorted){
        current = first_unsorted;
        min_node = first_unsorted;
        // first_unsorted 到 末尾的最小节点
        while (current){
            if (min_node->entry > current->entry)
                min_node = current;
            current = current->next;
        }
        
    }
}

template <typename Record>
void Sortable_list<Record>::swap(int low, int high){
    Record low_r, high_r;
    retrieve(low, low_r);
    retrieve(high, high_r);
    replave(low, high_r);
    replace(high, low_r);
}



template<typename Record>
void Sortable_list<Record>::merge_sort(){
    recursive_merge_sort(head);
}

template<typename Record>
void Sortable_list<Record>::recursive_merge_sort(Node<Record> * &sub_list){
    // 保证完成一次后，sub_list作为头指针指向的链表是有序的，由于头指针可能会变，所以就使用指针的引用，方便修改头指针
    if (sub_list != NULL && sub_list->next != NULL){// 保证至少有两个节点才有归并的意义
        Node<Record> *mid_list = divide_from_list(sub_list);
        recursive_merge_sort(sub_list);
        recursive_merge_sort(mid_list);
        sub_list = merge(sub_list, mid_list);// 合并之后，修改该子列的头指针
    }
}

template<typename Record>
void Sortable_list<Record>::divide_from(Node<Record> *sub_list){
    /* 
    1. 空表直接返回
    2. 只有一个元素，返回NULL
    3. 两个元素及以上，返回中间节点的指针
    4. 若奇数个元素，保证前半段链表元素数比后半段链表多1
    5. 确保切断之后，两个链表都是以NULL结尾 */
    if (sub_list == NULL) return;
    Node<Record> *first_end,// 前半段链表的末尾
                * second_begin,// 后半段链表的头
                * position; // 用来遍历的临时指针
    first_end = sub_list;
    position = sub_list->next;
    while (position){// 每一次循环，position前进两步，first_end前进一步
        position = position->next; // 先试探性的走一步
        if (position->next){
            position = position->next;
            first_end = first_end->next;
        }
    } 
    second_begin = first_end->next; // 得到后半段链表的开头
    first_end->next = NULL; // 切断第一段链表和第二段链表
    return second_begin;
}


template<typename Record>
void Sortable_list<Record>::merge(Node<Record> *first, Node<Record> *second){
    Node<Record> *last_sorted;
    Node<Record> combined;
    last_sorted = &combined; // 这个很奇怪诶 // 先创建一个节点，默认有头节点，避免各种情况的讨论
    while (first != NULL && second != NULL){
        if (first->entry <= second->entry){
            last_sorted->next = first;
            last_sorted = first;
            first = first->next;
        }
        else {
            last_sorted->next = second;
            last_sorted = second;
            second = second->next;
        }
    }
    if (first != NULL){
        last_sorted->next = first;
    }
    else {
        last_sorted->next = second;
    }
    return combined.next;
}

template <class Record>
void Sortable_list<Record>::partition(Node<Record> *sub_list,
                                      Node<Record> *&first_small, Node<Record> *&last_small,
                                      Node<Record> *&first_large, Node<Record> *&last_large)
{
    Record pivot = sub_list->entry;
    sub_list = sub_list->next;
    Node<Record> small, large;
    last_small = &small;
    last_large = &large;
    while (sub_list != NULL)
    {
        if (sub_list->entry > pivot)
            last_large = last_large->next = sub_list;
        else
            last_small = last_small->next = sub_list;
        sub_list = sub_list->next;
    }
    last_large->next = last_small->next = NULL;
    if ((first_small = small.next) == NULL)
        last_small = NULL;
    if ((first_large = large.next) == NULL)
        last_large = NULL;
}


template <class Record>
void Sortable_list<Record>::recursive_quick_sort(Node<Record> *&first_node,
                                                 Node<Record> *&last_node)// 效果
{
    if (first_node != NULL && first_node != last_node)// 至少有两个节点
    {
        // Otherwise, no sorting is needed.
        Node<Record> *first_small, *last_small, *first_large, *last_large;
        partition(first_node, first_small, last_small,
                  first_large, last_large);
        recursive_quick_sort(first_small, last_small);
        recursive_quick_sort(first_large, last_large);
        if (last_large != NULL)
            last_node = last_large;
        else
            last_node = first_node;
        first_node->next = first_large;
        if (first_small != NULL)
        {
            last_small->next = first_node;
            first_node = first_small;
        }
    }
}

template <class Record>
void Sortable_list<Record>::quick_sort()
/*
    Post: The entries of the Sortable_list have been rearranged so
    that their keys are sorted into nondecreasing order.
    Uses: The contiguous List implementation of ?list_ch?,
    recursive_quick_sort.
    */
{
    if (head == NULL || head->next == NULL)
        return;
    recursive_quick_sort(head, head->next);
}