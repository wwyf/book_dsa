#include <iostream>
using namespace std;

const int MAXN = 100;

template<typename Record>
class simpleList{
public:
    simpleList(){
        for (int i = 0; i < 10; i++){
            entry[10-i-1] = i;
        }
        count = 10;
    }
    void heap_sort();
    void insert_heap(const Record &current, int low, int high);
    void build_heap();
    void print();
private:
    int count;
    Record entry[MAXN]; 
};




template<class Record>
void simpleList<Record>::heap_sort(){
    Record current;
    int last_unsorted;
    build_heap();
    for (last_unsorted = count-1; last_unsorted > 0; last_unsorted--){
        current = entry[last_unsorted]; // store the last unsorted entry, to store the biggest entry in that position
        entry[last_unsorted] = entry[0]; // move the biggest entry to the end
        insert_heap(current, 0, last_unsorted-1);
    }
}

template <class Record>
void simpleList<Record>::insert_heap(const Record &current, int low, int high)
/* Pre:
    the entry in position low will be discarded
   Post:
    from a heap whose entries include position from low+1 to high(include high) and current */
{
    int large;
    large = 2 * low + 1;
    while (large <= high){
        if (large < high && entry[large] < entry[large+1])
        /* 1. if position low only has a child, ths condition can solve this situation
           2. if low has two childure, then find the biggest child */
            large++;
        if (current >= entry[large])
            break;
        else {
            entry[low] = entry[large];
            low = large;
            large = 2 * low + 1;
        }
    }
    entry[low] = current;
}

template <typename Record>
void simpleList<Record>::build_heap(){
    int low;
    for (low = count/2 - 1; low >= 0; low--){// 不用管叶子节点 // 还是有点奇怪
        Record current = entry[low];
        insert_heap(current, low, count-1);
    }
}

template <typename Record>
void simpleList<Record>::print(){
    for (int i = 0; i < count; i++){
        cout << entry[i] << " ";
    }
    cout << endl;
}

int main(){

    simpleList<int> test;
    test.print();
    test.heap_sort();
    test.print();
    return 0;
}