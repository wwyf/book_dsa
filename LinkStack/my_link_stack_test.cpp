#include<iostream>
using namespace std;
int main(){
    const int MAX = 25;
    int count = 0;
    int i = 1;
    for (;count < MAX; ){
        int a[i];
        a[i] = i;
        cout << sizeof(a) << "   ";
        cout << count << endl;
        i = i * 2;
        count++;
    }
    return 0;
}