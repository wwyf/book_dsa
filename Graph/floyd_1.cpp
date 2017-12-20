// floyd_1.cpp
#include <iostream>
using namespace std;
#define MAX 20
#define INF 99999



int main(){
    int adj[MAX][MAX];
    int path[MAX][MAX];
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            adj[i][j] = INF;
            path[i][j] = j;
        }
    }

    int d;
    int v, w, p;
    cin >> d;
    while (cin >> v >> w >> p){
        adj[v][w] = p;
    }


    for (int k = 0; k < d; k++){
        for (int i = 0; i < d; i++){
            for (int j = 0; j < d; j++){
                if (adj[i][k] + adj[k][j] < adj[i][j]){
                    adj[i][j] = adj[i][k] + adj[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            if (adj[i][j] < INF){
                cout << i << "-" << j << ":" << adj[i][j];
                cout << "path:" << i;
                int next = path[i][j];
                while (next != j){
                    cout << " " << next;
                    next = path[next][j];
                }
                cout << " " << j << endl;

            }
        }
    }

    return 0;
}