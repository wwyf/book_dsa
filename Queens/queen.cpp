#include<iostream>
using namespace std;

class Queens{
public:
    Queens(int n){
        full_size = n;
        for (int i = 0; i < 100; i++){
            for (int k = 0; k < 100; k++){
                map[i][k] = 0;
            }
        }
        count = 0;
    }

    bool is_solved() const{
        return (count == full_size);
    }

    void insert(int col) {
        map[count][col] = 1;
        count++;
    }

    void removed(int col){
        if (count == 0){
            return ;//  maybe throw an exception.
        }
        
        count--;
        map[count][col] = 0;
    }

    void print() const{
        for (int i = 0; i < full_size; i++){
            for(int k = 0; k < full_size; k++){
                cout << map[i][k] << " ";
            }
            cout << endl;
        }
        cout << "-------------------------------------" << endl;
    }

    bool unguarded(int col) const{
        bool ok = true;
        for (int i = 0; ok && i < count; i++){
            ok = !map[i][col];
        }
        for (int i = 1; ok && count-i >= 0 && col-i >= 0; i++){
            ok = !map[count-i][col-i];
        }
        for (int i = 1; ok && count-i >= 0 && col+i < full_size; i++){
            ok = !map[count-i][col+i];
        }
        return ok;
    }    
private:
    int map[100][100];
    int count;
    int full_size;
};

void solve(Queens &confri){
    if (confri.is_solved()){
        confri.print();
        return ;
    }
    else {
        for (int col = 0; col < 8; col++){
            if (confri.unguarded(col)){
                confri.insert(col);
                solve(confri);
                confri.removed(col);
            }
        }
        
    }
}


int main(){
    Queens test(8);
    solve(test);
    return 0;
}