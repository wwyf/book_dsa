#include <iostream>

using namespace std;


template <typename K, typename V> struct Dectionary{
    virtual int size() const = 0;
    virtual bool put (K, V) = 0; // 如果禁止相同词条可能失败
    virtual V* get (K k) = 0;
    virtual bool remove (K k) = 0;
}












int main(){

    return 0;
}