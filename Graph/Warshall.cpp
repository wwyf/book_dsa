// Warshall.cpp
// transitive closure
#include <iostream>
using namespace std;
#define MAX 100

void input(int m[][MAX], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> m[i][j];
        }
    }
}

void print(int m[][MAX], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

void solve(int m[][MAX], int n){
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                m[i][j] = m[i][j] || (m[i][k] && m[k][j]);       
            }
        }
        cout << "now is " << k+1 << endl;
        print(m, n);
    }
}


int main(){
    const int n = 4;
    int m[MAX][MAX];
    input(m, n);
    solve(m, n);
    return 0;
}