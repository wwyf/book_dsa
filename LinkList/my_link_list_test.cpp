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
    int a;
    test.traverse(print);
    test.remove(0, a);
    cout << a << endl;
    test.traverse(print);
    test.remove(5, a);
    cout << a << endl;
    test.traverse(print);
    return 0;
}