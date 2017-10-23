#include <cstdlib>
#include <cstring>
#include <iostream>
#include "sort.h"
using namespace std;

// only for test the sort function
template<typename T>
void test(void (*sort)(T [], int), T num[], int length){
    T *t = new T[length];
    memcpy(t, num, length * sizeof(T));
    sort(t, length);
    for (int i = 0; i < length; i++){
        cout << t[i] << " ";
    }
    delete t;
    cout << endl ;
}


int main(){
    int num[16] = {23,23,23,23,434,34,22,3,5,2,3,35,63,2,323,12};
    test<int>(shell_sort, num, 16);
    return 0;
}