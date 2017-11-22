// Problem#: 21109
// Submission#: 5207950
// The source code is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// URI: http://creativecommons.org/licenses/by-nc-sa/3.0/
// All Copyright reserved by Informatic Lab of Sun Yat-sen University
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
const int MAXN = 10010;

class Hash_table{
public:
    Hash_table(int length){
        num_room_ = length;
        all_search_length_ = 0;
        num_people_=0;
        for (int i = 0; i < num_room_; i++){
            room_table_[i] = string("NULL");
        }
    }
    
    void insert(const string & name){
        int index = hash(name);
        int find_num = 1;
        while (room_table_[index] != string("NULL") && find_num <= num_room_){
            index = (index + 1)%num_room_;
            find_num++;
        }
        if (find_num <= num_room_){
            room_table_[index] = name;
            num_people_++;      
            all_search_length_ += find_num;
        }
    
    }
    
    double asl() const{
        return double(all_search_length_)/num_people_;
    }
    
    void print() const{
        for (int i = 0; i < num_room_; i++){
            printf("%d:%s\n", i, room_table_[i].c_str());
            //printf("%d\n", hash(room_table_[i]));
        }
        //printf("%d\n", num_people_);
        //printf("%d\n", all_search_length_);
        printf("%.3f\n", asl());
    }

private:
    int hash(const string & name) const{
        int sum = 0;
        for (int i = 0; i < name.size(); i++){
            sum += name[i]-'a'+1;
        }
        return sum % num_room_;
    }   
    int num_room_;
    int num_people_;
    int all_search_length_;
    string room_table_[MAXN];
};



int main(){
    int n, m;
    char name[20];
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Hash_table t(m);
        for (int i = 0; i < n; i++){
            scanf("%s",name);
            t.insert(string(name));
        }
        t.print();
    }

    return 0;
}                                 