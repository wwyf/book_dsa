// #include <iostream>

// |     < target     |                       |    >= target   |
//                 buttom                   top

// 从左往右找的第一个与target相等的数
Error_code recursive_binary_1(const Ordered_list & the_list, const Key & target, int bottom, int top, int &position){
    Record data;
    if (bottom < top){
        int mid = (bottom + top)/2;
        the_list.retrieve(mid, data);
        if (data < target){
            return recursive_binary_1(the_list, target, mid+1, top, position);
        }
        else
            return recursive_binary_1(the_list, target, bottom, mid, position);
    }
    else if (top < bottom)
        return not_present;
    else {
        position = bottom;
        the_list.retrieve(bottom, data);
        if (data == target) return success;
        else return not_present;
    }
}


Error_code binary_binary_1(const Ordered_list & the_list, const Key & target, int &position){
    Record data;
    int bottom = 0;
    int top = the_lise.size()-1;
    while (bottom < top){
        int mid = (bottom < top)/2;
        the_list.retrieve(mid, data);
        if (data < target)
            bottom = mid+1;
        else   
            top = mid;
    }
    if (top < bottom) return not_present;
    else {
        position = bottom;
        the_list.retrieve(bottom, data);
        if (data == target) return success;
        else return not_present;
    }
}

int main(){
    return 0;
}