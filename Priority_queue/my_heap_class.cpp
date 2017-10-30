#include <iostream>
#include <algorithm>
using namespace std;


// 大顶堆
const int MAXN = 1000;
template <typename T>
class Heap{
public:
    Heap();
    void buildHeap( int n ) ; //Floyd建堆算法，O(n)时间
    void push(const T & entry);
    void pop(T & entry);
    bool empty() const;
    bool full() const;
    void print() const;
    T top();
private:
    int getProperParent(int n, int cur_index);
    void percolateDown(int n, int cur_index);
    void percolateUp(int cur_index);
    T entry[MAXN];
    int count;
};

template <typename T>
Heap<T>::Heap(){
    count = 0;
}


template <typename T> 
void Heap<T>::buildHeap( int n ) { //Floyd建堆算法，O(n)时间
    for (int i = count-1; i >= 0; i--)
        percolateDown ( n, i ); //下滤各内部节点
}

template <typename T>
void Heap<T>::push(const T & new_entry){
/* Post: if heap is full, do nothing
        else : a new_entry will push into the heap, and modifly itself to meet the rule of heap, count++ */
    if (full()) return ;
    // put the new_entry to the end of the heap
    entry[count] = new_entry;
    count++;
    percolateUp(count-1);

    // // the new_entry meybe break the rule of heap. So solve this problems
    // int cur_index = count;// the index if new_entry
    // int parent_index = (cur_index-1)/2;
    // while(parent_index >= 0)// the loop ends only if new_entry is on the top of heap
    // // when cur_index equal to 0, parent_index will less then 0;
    // {
    //     if (entry[parent_index] < entry[cur_index]) // the top of heap is biggest.
    //         swap(entry[parent_index], entry[cur_index]);
    //     cur_index = parent_index;
    //     parent_index = (cur_index-1)/2;
    // }
}

template <typename T>
void Heap<T>::pop( T & old_entry){
    if (empty()) return ;

    old_entry = entry[0];
    entry[0] = entry[count-1];// move the last entry to the top of heap
    count--; // get and delete the max entry
    percolateDown(count, 0);

    // int cur_index = 0;
    // int chird_index = 2*cur_index + 1;
    // while (chird_index < count){
    //     if (chird_index < count-1 && entry[chird_index] < entry[chird_index+1] ) // if cur_index has right child ? the right child is bigger?
    //         chird_index++;
    //     if (entry[cur_index] >= entry[chird_index])
    //         break;
    //     else {
    //         swap(entry[cur_index], entry[chird_index]);
    //         cur_index = chird_index;
    //         chird_index = cur_index*2 + 1;
    //     }
    // }
}

// among the first n entry, find the biggest entry among cur_index and its children
template <typename T>
int Heap<T>::getProperParent(int n, int cur_index){
    int child_index = 2 * cur_index + 1;
    if (child_index >= n-1) return cur_index;

    if (child_index < n-1 && entry[child_index] < entry[child_index+1])// find the bigger child
        child_index++;
    if (entry[child_index] > entry[cur_index])
        return child_index;
    else
        return cur_index;
}

//对向量前n个词条中的第i个元素下滤
template <typename T>
void Heap<T>::percolateDown(int n, int cur_index){
    int biggest_index;
    while (  cur_index !=  (biggest_index = getProperParent(n, cur_index)) ){
        swap(entry[cur_index], entry[biggest_index]);
        cur_index = biggest_index;
    }
}
// 对第n个词条上滤
template <typename T>
void Heap<T>::percolateUp(int cur_index){
    int parent_index;
    while (   (parent_index = (cur_index-1)/2 ) >= 0 ){// if the parent of cur_index exist
        if (entry[parent_index] >= entry[cur_index])  
            break;
        swap(entry[parent_index], entry[cur_index]);
        cur_index = parent_index;
    }
}


template <typename T>
void Heap<T>::print() const {
    for (int i = 0; i < count; i++)
        cout << entry[i] << " ";
    cout << endl;
}

template <typename T>
T Heap<T>::top(){
    return entry[0];
}

template <typename T>
bool Heap<T>::empty() const {
    return count == 0;
}

template <typename T>
bool Heap<T>::full() const{
    return count >= MAXN;
}

// int main(){
//     Heap<int> test;
//     test.push(4);
//     test.push(3);
//     test.push(8);
//     test.push(0);
//     test.push(2);
//     test.print();
//     while (!test.empty()){
//         int temp;
//         test.pop(temp);
//         cout << temp << " < ";
//         test.print();
//     }

//     return 0;
// }