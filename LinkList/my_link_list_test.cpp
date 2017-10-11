#include <iostream>
#include "my_link_list_class.h"
using namespace std;

void print(int &a){
    cout << a << " ";
}


int main(){
    LinkList<int> test;
    for(int i = 0; i <10; i++){
        test.insert(0, i);
    }
    test.traverse(print);
    return 0;
}