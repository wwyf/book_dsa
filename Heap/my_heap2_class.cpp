#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
template <typename T>
class Heap{
public:
    Heap();
    void push(const T & entry);
    void pop(const T & entry);
    void print() const;
    T top();
private:
    T entry[MAXN];
    int count;
};

template <typename T>
Heap::Heap(){
    count = 0;
}

template <typename T>
void Heap<T>::push(const T & new_entry){
    entry[count] = new_entry;
    cur_index = count;
    count++;
    while(cur_index > 0)
    {
        int parent_index = (cur_index-1)/2;
        if (entry[parent_index] < entry[cur_index])
            swap(entry[parent_index], entry[index_entry]);
        cur_index = parent_index;
    }
}

template <typename T>
void Heap<T>::pop(const T & entry){
    
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
bool Heap::empty() const {
    return count == 0;
}

int main(){
    Heap<int> test;
    test.push(4);
    test.push(3);
    test.push(8);
    test.push(0);
    test.push(2);
    test.print();

    return 0;
}