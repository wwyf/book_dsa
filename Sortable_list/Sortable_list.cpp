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