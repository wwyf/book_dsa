// 从左往右找的第一个与target相等的数
// 如果找到，就返回左边第一个与target相等的数，如果找不到，就返回右边最靠近target的位置，方便插入
// |     < target     |                       |    >= target   |
//                 buttom                   top

#include <cstdio>

enum Error_code{
    not_present,
    success
};
// 递归版本
// Error_code recursive_binary_1(const Ordered_list & the_list, const Key & target, int bottom, int top, int &position){
//     Record data;
//     if (bottom < top){
//         int mid = (bottom + top)/2;
//         the_list.retrieve(mid, data);//取得mid对应位置的data
//         if (data < target){
//             return recursive_binary_1(the_list, target, mid+1, top, position);
//         }
//         else
//             return recursive_binary_1(the_list, target, bottom, mid, position);
//     }
//     else if (top < bottom)
//         return not_present;
//     else {
//         position = bottom;
//         the_list.retrieve(bottom, data);// 取得bottom对应的data
//         if (data == target) return success;
//         else return not_present;
//     }
// }


// 迭代版本
// Error_code binary_binary_1(const Ordered_list & the_list, const Key & target, int &position){
//     Record data;
//     int bottom = 0;
//     int top = the_lise.size()-1;
//     while (bottom < top){
//         int mid = (bottom + top)/2;
//         the_list.retrieve(mid, data);
//         if (data < target)
//             bottom = mid+1;
//         else   
//             top = mid;
//     }
//     if (top < bottom) return not_present;
//     else {
//         position = bottom;
//         the_list.retrieve(bottom, data);
//         if (data == target) return success;
//         else return not_present;
//     }
// }

// 数组版

Error_code binary_search_1(int * list, int length, const int & target, int &position){
    typedef int Record;
    Record data;
    int bottom = 0;
    int top = length-1;
    while (bottom < top){
        int mid = (bottom + top)/2;
        data = list[mid];
        if (data < target)
        // 关键：确定是找到左边第一个的关键，这条语句把左边确定比target小的全部删掉，在右边，大于等于target的还能留下来。
            bottom = mid+1;
        else   
            top = mid;
    }
    if (top < bottom) return not_present;
    else {
        position = bottom;
        data = list[bottom];
        if (data == target) return success;
        else return not_present;
    }
}

int main(){
    int a[9] = {1,2,3,4,5,6,7,8,9};
    int position = 0;
    bool flag = binary_search_1(a, 9, 10, position);
    printf("flag%s, in pos %d\n", flag?"success":"failed", position);
    return 0;
}